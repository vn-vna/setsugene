#include "gfx_renderer.h"

#include <setsugen/exception.h>
#include <setsugen/mesh.h>
#include <setsugen/transform.h>

#define MAX_FRAMES_IN_FLIGHT 3

namespace setsugen
{
GfxVulkanRenderer::GfxVulkanRenderer(RendererConfig&& config)
    : m_vulkan_app{GfxApplication::get_current()},
      m_config{std::move(config)},
      m_logical_device{nullptr},
      m_command_pool{nullptr},
      m_framebuffers{},
      m_image_available_semaphores{},
      m_current_scene{nullptr},
      m_next_scene{nullptr},
      m_current_frame{0}
{
  m_logger = Application::current_app()->create_logger("setsugen::GfxVulkanRenderer");
  m_target = dynamic_cast<GfxWindowRenderTarget*>(m_config.render_target.get());

  if (m_target->type() != RenderTargetType::Window)
  {
    throw InvalidArgumentException("Render target is not a window");
  }

  m_logical_device = m_vulkan_app->get_logical_device();

  create_graphics_pipeline();
  create_framebuffers();
  create_synchronization_objects();
}

GfxVulkanRenderer::~GfxVulkanRenderer()
{
  for (unsigned int i = 0; i < m_framebuffers.size(); ++i)
  {
    vkDestroySemaphore(m_logical_device, m_image_available_semaphores[i], nullptr);
    vkDestroySemaphore(m_logical_device, m_render_finished_semaphores[i], nullptr);
    vkDestroyFence(m_logical_device, m_inflight_fences[i], nullptr);
  }

  for (auto framebuffer: m_framebuffers)
  {
    vkDestroyFramebuffer(m_logical_device, framebuffer, nullptr);
  }
}

void
GfxVulkanRenderer::render()
{
  const auto   graphics_queue = m_vulkan_app->get_graphics_queue();
  const auto   swapchain      = m_target->m_swapchain;
  unsigned int image_index;

  // Prepare scene
  {
    m_next_scene = Application::current_app()->get_scene_manager()->get_current_scene();

    if (m_next_scene && m_current_scene != m_next_scene && m_next_scene->is_loaded())
    {
      prepare_scene(m_next_scene);
      unload_scene(m_current_scene);
      m_current_scene = m_next_scene;
    }
    else
    {
      prepare_scene(m_current_scene);
    }
  }

  if (!m_current_scene)
  {
    return;
  }

  // Update scene
  {
    update_scene(m_current_frame);
  }

  // Wait for the previous frame to be finished
  {
    vkWaitForFences(m_logical_device, 1, &m_inflight_fences[m_current_frame], VK_TRUE, UINT64_MAX);
    vkResetFences(m_logical_device, 1, &m_inflight_fences[m_current_frame]);
  }

  // Acquire the next image
  {
    auto acquire_result =
        vkAcquireNextImageKHR(m_logical_device, swapchain, UINT64_MAX, m_image_available_semaphores[m_current_frame],
                              VK_NULL_HANDLE, &image_index);

    if (acquire_result != VK_SUCCESS)
    {
      throw EngineException("Failed to acquire swapchain image");
    }
  }

  // Submit the command buffer
  {
    VkSubmitInfo submit_info = {};
    submit_info.sType        = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore          wait_semaphores[] = {m_image_available_semaphores[m_current_frame]};
    VkPipelineStageFlags wait_stages[]     = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};

    submit_info.waitSemaphoreCount = 1;
    submit_info.pWaitSemaphores    = wait_semaphores;
    submit_info.pWaitDstStageMask  = wait_stages;

    VkCommandBuffer command_buffers[] = {m_draw_command->command_buffers[m_current_frame]->get_handler()};

    submit_info.commandBufferCount = 1;
    submit_info.pCommandBuffers    = command_buffers;

    VkSemaphore signal_semaphores[]  = {m_render_finished_semaphores[m_current_frame]};
    submit_info.signalSemaphoreCount = 1;
    submit_info.pSignalSemaphores    = signal_semaphores;

    auto submit_result = vkQueueSubmit(graphics_queue, 1, &submit_info, m_inflight_fences[m_current_frame]);
    if (submit_result != VK_SUCCESS)
    {
      throw EngineException("Failed to submit draw command buffer");
    }
  }

  // Present the image
  {
    VkSwapchainKHR swapchains[] = {swapchain};

    VkPresentInfoKHR present_info = {};
    present_info.sType            = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

    present_info.waitSemaphoreCount = 1;
    present_info.pWaitSemaphores    = &m_render_finished_semaphores[m_current_frame];

    present_info.swapchainCount = 1;
    present_info.pSwapchains    = swapchains;
    present_info.pImageIndices  = &image_index;

    const auto present_result = vkQueuePresentKHR(GfxApplication::get_current()->get_present_queue(), &present_info);
    if (present_result != VK_SUCCESS)
    {
      throw EngineException("Failed to present swapchain image");
    }
  }

  m_current_frame = (m_current_frame + 1) % m_framebuffers.size();
}

void
GfxVulkanRenderer::cleanup()
{
  unload_scene(m_current_scene);
}


void
GfxVulkanRenderer::create_graphics_pipeline()
{
  m_graphics_pipeline = VulkanGraphicsPipeline::create(m_target, m_config);
}

void
GfxVulkanRenderer::create_framebuffers()
{
  const auto device           = m_vulkan_app->get_logical_device();
  const auto swapchain_images = m_target->m_swapchain_images;

  m_framebuffers.resize(swapchain_images.size());

  for (unsigned int i = 0; i < swapchain_images.size(); ++i)
  {
    const VkImageView attachments[] = {m_target->m_swapchain_image_views[i]};

    VkFramebufferCreateInfo framebuffer_info = {};
    framebuffer_info.sType                   = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    framebuffer_info.renderPass              = m_graphics_pipeline->get_render_pass();
    framebuffer_info.attachmentCount         = 1;
    framebuffer_info.pAttachments            = attachments;
    framebuffer_info.width                   = m_target->m_swapchain_extent.width;
    framebuffer_info.height                  = m_target->m_swapchain_extent.height;
    framebuffer_info.layers                  = 1;

    auto framebuffer_result = vkCreateFramebuffer(device, &framebuffer_info, nullptr, &m_framebuffers[i]);
    if (framebuffer_result != VK_SUCCESS)
    {
      throw EngineException("Failed to create framebuffer");
    }
  }
}

void
GfxVulkanRenderer::create_command_pool()
{
  if (m_command_pool)
  {
    return;
  }

  m_command_pool = GfxCommandPool::create(VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT);
}

void
GfxVulkanRenderer::create_command_buffers(Scene* scene)
{
  if (!m_draw_command)
  {
    m_draw_command = std::make_unique<MeshDrawCommand>();

    // Create command buffers
    m_draw_command->command_buffers.resize(m_framebuffers.size());
    for (int i = 0; i < m_framebuffers.size(); ++i)
    {
      m_draw_command->command_buffers[i] = m_command_pool->allocate_command_buffer();
    }
  }

  // Record command buffers
  for (int i = 0; i < m_framebuffers.size(); ++i)
  {
    auto& cmd = m_draw_command->command_buffers[i];
    cmd->begin();
    cmd->begin_render_pass(m_graphics_pipeline.get(), m_target, m_framebuffers[i]);

    for (auto& [mesh, drawinfo]: m_mesh_drawinfo)
    {
      auto                       meshdata = mesh->get_meshdata();
      std::vector<VertexBuffer*> vertex_buffers;
      for (auto& buffer: m_meshdata_buffers[meshdata].vertex_buffers)
      {
        vertex_buffers.push_back(buffer.get());
      }

      auto index_buffer = m_meshdata_buffers[meshdata].index_buffer.get();

      std::vector<GfxDescriptorSet*> descriptor_sets;
      descriptor_sets.push_back(drawinfo.descriptor_sets[i].get());

      cmd->draw(m_graphics_pipeline.get(), vertex_buffers, index_buffer, descriptor_sets,
                meshdata->get_indices()->size());
    }

    cmd->end_render_pass();
    cmd->end();
  }

  // Update scene uniform buffer
  Mat4F camera_matrices[] = {scene->get_main_camera()->get_view_matrix(),
                             scene->get_main_camera()->get_projection_matrix()};
  m_scene_uniform_buffer[m_current_frame]->copy_data(camera_matrices, sizeof(Mat4F) * 2);
}

void
GfxVulkanRenderer::create_synchronization_objects()
{
  m_image_available_semaphores.resize(m_framebuffers.size());
  m_render_finished_semaphores.resize(m_framebuffers.size());
  m_inflight_fences.resize(m_framebuffers.size());

  VkSemaphoreCreateInfo semaphore_info = {};
  semaphore_info.sType                 = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

  VkFenceCreateInfo fence_info = {};
  fence_info.sType             = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
  fence_info.flags             = VK_FENCE_CREATE_SIGNALED_BIT;

  for (unsigned int i = 0; i < m_framebuffers.size(); ++i)
  {
    auto semaphore_result =
        vkCreateSemaphore(m_logical_device, &semaphore_info, nullptr, &m_image_available_semaphores[i]);
    if (semaphore_result != VK_SUCCESS)
    {
      throw EngineException("Failed to create semaphores");
    }

    semaphore_result = vkCreateSemaphore(m_logical_device, &semaphore_info, nullptr, &m_render_finished_semaphores[i]);
    if (semaphore_result != VK_SUCCESS)
    {
      throw EngineException("Failed to create semaphores");
    }

    auto fence_result = vkCreateFence(m_logical_device, &fence_info, nullptr, &m_inflight_fences[i]);
    if (fence_result != VK_SUCCESS)
    {
      throw EngineException("Failed to create fences");
    }
  }

  m_logger->trace("Synchronization objects created successfully");
}

void
GfxVulkanRenderer::prepare_scene(Scene* scene)
{
  if (!scene)
  {
    return;
  }

  create_command_pool();

  for (auto& data: scene->get_all_meshdata())
  {
    if (m_meshdata_buffers.find(data) != m_meshdata_buffers.end())
    {
      continue;
    }

    create_vertex_buffer(data);
    create_index_buffer(data);
  }

  create_uniform_buffers(scene);
  create_command_buffers(scene);
}

void
GfxVulkanRenderer::unload_scene(Scene* scene)
{
  if (!scene)
  {
    return;
  }

  vkDeviceWaitIdle(m_logical_device);

  m_scene_uniform_buffer.clear();
  m_command_pool.reset();

  for (auto& [mesh, buffers]: m_meshdata_buffers)
  {
    buffers.vertex_buffers.clear();
    buffers.index_buffer.reset();
  }

  m_meshdata_buffers.clear();
  m_draw_command.reset();

  vkDeviceWaitIdle(m_logical_device);
}

void
GfxVulkanRenderer::update_scene(int frame_index)
{
  if (!m_current_scene)
  {
    return;
  }

  for (auto& entt: m_current_scene->get_entities())
  {
    Mesh*      mesh;
    Transform* transform;

    try
    {
      mesh      = entt->get_component<Mesh>();
      transform = entt->get_component<Transform>();
    }
    catch (const SetsugenException& e)
    {
      continue;
    }

    auto& drawinfo = m_mesh_drawinfo[mesh];
    auto  model_matrix = transform->get_model_matrix();

    drawinfo.uniform_buffers[frame_index]->copy_data(&model_matrix, sizeof(Mat4F));
  }

}

void
GfxVulkanRenderer::create_vertex_buffer(MeshData* meshdata)
{
  for (auto& layout: m_config.vertex_buffer_layouts)
  {
    m_meshdata_buffers[meshdata].vertex_buffers.push_back(VertexBuffer::from_meshdata(this, meshdata, layout));
  }
}

void
GfxVulkanRenderer::create_index_buffer(MeshData* meshdata)
{
  m_meshdata_buffers[meshdata].index_buffer = IndexBuffer::from_meshdata(this, meshdata);
}
void
GfxVulkanRenderer::create_uniform_buffers(Scene* scene)
{
  // Global scene uniform buffer
  constexpr VkDeviceSize buffer_size = sizeof(Mat4F) * 2;

  if (m_scene_uniform_buffer.empty())
  {
    for (int i = 0; i < m_framebuffers.size(); ++i)
    {
      m_scene_uniform_buffer.push_back(UniformBuffer::create(buffer_size));
    }
  }

  Mat4F camera_matrices[] = {scene->get_main_camera()->get_view_matrix(),
                             scene->get_main_camera()->get_projection_matrix()};

  for (int i = 0; i < m_framebuffers.size(); ++i)
  {
    m_scene_uniform_buffer[i]->copy_data(camera_matrices, buffer_size);
  }

  // Mesh uniform buffer
  for (auto& entt: scene->get_entities())
  {
    Mesh*      mesh;
    Transform* transform;

    try
    {
      mesh      = entt->get_component<Mesh>();
      transform = entt->get_component<Transform>();
    }
    catch (const SetsugenException& e)
    {
      continue;
    }

    // Create mesh uniform buffer
    if (m_mesh_drawinfo.find(mesh) == m_mesh_drawinfo.end())
    {
      m_mesh_drawinfo[mesh] = {};
      auto& drawinfo        = m_mesh_drawinfo[mesh];
      drawinfo.descriptor_pool = GfxDescriptorPool::create(m_framebuffers.size() * 2, m_framebuffers.size() * 2);
      auto descriptor_pool     = drawinfo.descriptor_pool.get();

      auto model_matrix     = transform->get_model_matrix();

      drawinfo.uniform_buffers.resize(m_framebuffers.size());
      for (int i = 0; i < m_framebuffers.size(); ++i)
      {
        drawinfo.uniform_buffers[i] = UniformBuffer::create(sizeof(Mat4F));
        drawinfo.uniform_buffers[i]->copy_data(&model_matrix, sizeof(Mat4F));
      }

      drawinfo.descriptor_sets.resize(m_framebuffers.size());

      for (int i = 0; i < m_framebuffers.size(); ++i)
      {
        auto layout                 = m_graphics_pipeline->get_descriptor_set_layout();
        drawinfo.descriptor_sets[i] = descriptor_pool->allocate_descriptor_set(layout);

        std::vector<UniformBuffer*> uniform_buffers;
        uniform_buffers.push_back(m_scene_uniform_buffer[i].get());
        uniform_buffers.push_back(drawinfo.uniform_buffers[i].get());
        drawinfo.descriptor_sets[i]->update_uniform_buffers(uniform_buffers);
      }
    }

  }
}

GfxCommandPool*
GfxVulkanRenderer::get_command_pool()
{
  return m_command_pool.get();
}

} // namespace setsugen
