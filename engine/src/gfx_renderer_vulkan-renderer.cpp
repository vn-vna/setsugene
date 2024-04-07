#include "gfx_renderer.h"

#define MAX_FRAMES_IN_FLIGHT 3

namespace setsugen
{
VkPrimitiveTopology
convert_to_vulkan_topology(Topology topology)
{
  switch (topology)
  {
    case Topology::PointList: return VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
    case Topology::LineList: return VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
    case Topology::LineStrip: return VK_PRIMITIVE_TOPOLOGY_LINE_STRIP;
    case Topology::TriangleList: return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    case Topology::TriangleStrip: return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;
    default: throw InvalidArgumentException("Invalid topology");
  }
}

VkFormat
convert_to_vulkan_format(VertexFormat format, VertexType type, VertexSize size)
{
  using VkFormatMapping = std::unordered_map<std::tuple<VertexFormat, VertexSize, VertexType>, VkFormat,
                                             TupleHash<VertexFormat, VertexSize, VertexType>>;

  static VkFormatMapping format_map = {
      {{VertexFormat::R, VertexSize::Size8, VertexType::Int}, VK_FORMAT_R8_SINT},
      {{VertexFormat::R, VertexSize::Size8, VertexType::UInt}, VK_FORMAT_R8_UINT},
      {{VertexFormat::R, VertexSize::Size16, VertexType::Int}, VK_FORMAT_R16_SINT},
      {{VertexFormat::R, VertexSize::Size16, VertexType::UInt}, VK_FORMAT_R16_UINT},
      {{VertexFormat::R, VertexSize::Size16, VertexType::Float}, VK_FORMAT_R16_SFLOAT},
      {{VertexFormat::R, VertexSize::Size32, VertexType::Int}, VK_FORMAT_R32_SINT},
      {{VertexFormat::R, VertexSize::Size32, VertexType::UInt}, VK_FORMAT_R32_UINT},
      {{VertexFormat::R, VertexSize::Size32, VertexType::Float}, VK_FORMAT_R32_SFLOAT},
      {{VertexFormat::R, VertexSize::Size64, VertexType::Int}, VK_FORMAT_R64_SINT},
      {{VertexFormat::R, VertexSize::Size64, VertexType::UInt}, VK_FORMAT_R64_UINT},
      {{VertexFormat::R, VertexSize::Size64, VertexType::Float}, VK_FORMAT_R64_SFLOAT},

      {{VertexFormat::RG, VertexSize::Size8, VertexType::Int}, VK_FORMAT_R8G8_SINT},
      {{VertexFormat::RG, VertexSize::Size8, VertexType::UInt}, VK_FORMAT_R8G8_UINT},
      {{VertexFormat::RG, VertexSize::Size16, VertexType::Int}, VK_FORMAT_R16G16_SINT},
      {{VertexFormat::RG, VertexSize::Size16, VertexType::UInt}, VK_FORMAT_R16G16_UINT},
      {{VertexFormat::RG, VertexSize::Size16, VertexType::Float}, VK_FORMAT_R16G16_SFLOAT},
      {{VertexFormat::RG, VertexSize::Size32, VertexType::Int}, VK_FORMAT_R32G32_SINT},
      {{VertexFormat::RG, VertexSize::Size32, VertexType::UInt}, VK_FORMAT_R32G32_UINT},
      {{VertexFormat::RG, VertexSize::Size32, VertexType::Float}, VK_FORMAT_R32G32_SFLOAT},
      {{VertexFormat::RG, VertexSize::Size64, VertexType::Int}, VK_FORMAT_R64G64_SINT},
      {{VertexFormat::RG, VertexSize::Size64, VertexType::UInt}, VK_FORMAT_R64G64_UINT},
      {{VertexFormat::RG, VertexSize::Size64, VertexType::Float}, VK_FORMAT_R64G64_SFLOAT},

      {{VertexFormat::RGB, VertexSize::Size8, VertexType::Int}, VK_FORMAT_R8G8B8_SINT},
      {{VertexFormat::RGB, VertexSize::Size8, VertexType::UInt}, VK_FORMAT_R8G8B8_UINT},
      {{VertexFormat::RGB, VertexSize::Size16, VertexType::Int}, VK_FORMAT_R16G16B16_SINT},
      {{VertexFormat::RGB, VertexSize::Size16, VertexType::UInt}, VK_FORMAT_R16G16B16_UINT},
      {{VertexFormat::RGB, VertexSize::Size16, VertexType::Float}, VK_FORMAT_R16G16B16_SFLOAT},
      {{VertexFormat::RGB, VertexSize::Size32, VertexType::Int}, VK_FORMAT_R32G32B32_SINT},
      {{VertexFormat::RGB, VertexSize::Size32, VertexType::UInt}, VK_FORMAT_R32G32B32_UINT},
      {{VertexFormat::RGB, VertexSize::Size32, VertexType::Float}, VK_FORMAT_R32G32B32_SFLOAT},
      {{VertexFormat::RGB, VertexSize::Size64, VertexType::Int}, VK_FORMAT_R64G64B64_SINT},
      {{VertexFormat::RGB, VertexSize::Size64, VertexType::UInt}, VK_FORMAT_R64G64B64_UINT},
      {{VertexFormat::RGB, VertexSize::Size64, VertexType::Float}, VK_FORMAT_R64G64B64_SFLOAT},

      {{VertexFormat::RGBA, VertexSize::Size8, VertexType::Int}, VK_FORMAT_R8G8B8A8_SINT},
      {{VertexFormat::RGBA, VertexSize::Size16, VertexType::UInt}, VK_FORMAT_R8G8B8A8_UINT},
      {{VertexFormat::RGBA, VertexSize::Size16, VertexType::Int}, VK_FORMAT_R16G16B16A16_SINT},
      {{VertexFormat::RGBA, VertexSize::Size16, VertexType::UInt}, VK_FORMAT_R16G16B16A16_UINT},
      {{VertexFormat::RGBA, VertexSize::Size16, VertexType::Float}, VK_FORMAT_R16G16B16A16_SFLOAT},
      {{VertexFormat::RGBA, VertexSize::Size32, VertexType::Int}, VK_FORMAT_R32G32B32A32_SINT},
      {{VertexFormat::RGBA, VertexSize::Size32, VertexType::UInt}, VK_FORMAT_R32G32B32A32_UINT},
      {{VertexFormat::RGBA, VertexSize::Size32, VertexType::Float}, VK_FORMAT_R32G32B32A32_SFLOAT},
      {{VertexFormat::RGBA, VertexSize::Size64, VertexType::Int}, VK_FORMAT_R64G64B64A64_SINT},
      {{VertexFormat::RGBA, VertexSize::Size64, VertexType::UInt}, VK_FORMAT_R64G64B64A64_UINT},
      {{VertexFormat::RGBA, VertexSize::Size64, VertexType::Float}, VK_FORMAT_R64G64B64A64_SFLOAT},
  };

  const auto format_tuple = std::make_tuple(format, size, type);
  const auto format_iter  = format_map.find(format_tuple);
  if (format_iter == format_map.end())
  {
    throw InvalidArgumentException("Invalid format");
  }

  return format_iter->second;
}

VkCullModeFlags
convert_to_vulkan_cull_mode(CullMode cull_mode)
{
  switch (cull_mode)
  {
    case CullMode::None: return VK_CULL_MODE_NONE;
    case CullMode::Front: return VK_CULL_MODE_FRONT_BIT;
    case CullMode::Back: return VK_CULL_MODE_BACK_BIT;
    default: throw InvalidArgumentException("Invalid cull mode");
  }
}

VkFrontFace
convert_to_vulkan_front_face(FrontFace front_face)
{
  switch (front_face)
  {
    case FrontFace::Clockwise: return VK_FRONT_FACE_CLOCKWISE;
    case FrontFace::CounterClockwise: return VK_FRONT_FACE_COUNTER_CLOCKWISE;
    default: throw InvalidArgumentException("Invalid front face");
  }
}

VkPolygonMode
convert_to_vulkan_polygon_mode(PolygonMode polygon_mode)
{
  switch (polygon_mode)
  {
    case PolygonMode::Fill: return VK_POLYGON_MODE_FILL;
    case PolygonMode::Line: return VK_POLYGON_MODE_LINE;
    case PolygonMode::Point: return VK_POLYGON_MODE_POINT;
    default: throw InvalidArgumentException("Invalid polygon mode");
  }
}

VkColorComponentFlags
convert_to_vulkan_color_component_flags(const ColorBlend& color_blend)
{
  VkColorComponentFlags flags = 0;

  if (color_blend.blend_component.r())
  {
    flags |= VK_COLOR_COMPONENT_R_BIT;
  }

  if (color_blend.blend_component.g())
  {
    flags |= VK_COLOR_COMPONENT_G_BIT;
  }

  if (color_blend.blend_component.b())
  {
    flags |= VK_COLOR_COMPONENT_B_BIT;
  }

  if (color_blend.blend_component.a())
  {
    flags |= VK_COLOR_COMPONENT_A_BIT;
  }

  return flags;
}

VulkanWindowRenderer::VulkanWindowRenderer(const RendererConfig& config)
    : m_vulkan_app{VulkanApplication::get_current()},
      m_target{dynamic_cast<VulkanWindowRenderTarget*>(config.render_target)}, m_current_frame{0}
{
  m_logger = Application::current_app()->create_logger("setsugen::VulkanWindowRenderer");

  if (config.render_target->type() != RenderTargetType::Window)
  {
    throw InvalidArgumentException("Render target is not a window");
  }

  m_logical_device = m_vulkan_app->get_logical_device();

  create_graphics_pipeline(config);
  create_framebuffers(config);
  create_command_pool(config);
  create_command_buffers(config);
  create_synchronization_objects(config);
}

VulkanWindowRenderer::~VulkanWindowRenderer()
{
  for (unsigned int i = 0; i < m_framebuffers.size(); ++i)
  {
    vkDestroySemaphore(m_logical_device, m_image_available_semaphores[i], nullptr);
    vkDestroySemaphore(m_logical_device, m_render_finished_semaphores[i], nullptr);
    vkDestroyFence(m_logical_device, m_inflight_fences[i], nullptr);
  }

  vkDestroyCommandPool(m_logical_device, m_command_pool, nullptr);

  for (auto framebuffer: m_framebuffers)
  {
    vkDestroyFramebuffer(m_logical_device, framebuffer, nullptr);
  }

  vkDestroyPipeline(m_logical_device, m_pipeline, nullptr);
  vkDestroyPipelineLayout(m_logical_device, m_pipeline_layout, nullptr);
  vkDestroyRenderPass(m_logical_device, m_render_pass, nullptr);
}

void
VulkanWindowRenderer::render(Scene*)
{
  const auto   graphics_queue = m_vulkan_app->get_graphics_queue();
  const auto   swapchain      = m_target->m_swapchain;
  unsigned int image_index;

  // Build the vertex buffer
  {}

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

    submit_info.commandBufferCount = 1;
    submit_info.pCommandBuffers    = &m_command_buffers[image_index];

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

    const auto present_result = vkQueuePresentKHR(VulkanApplication::get_current()->get_present_queue(), &present_info);
    if (present_result != VK_SUCCESS)
    {
      throw EngineException("Failed to present swapchain image");
    }
  }

  m_current_frame = (m_current_frame + 1) % m_framebuffers.size();
}

void
VulkanWindowRenderer::cleanup()
{
  vkDeviceWaitIdle(m_logical_device);
}


void
VulkanWindowRenderer::create_graphics_pipeline(const RendererConfig& config)
{
  auto vertex_shader   = ShaderModule(config.vertex_shader.value_or(DEFAULT_VERTEX_SHADER));
  auto fragment_shader = ShaderModule(config.fragment_shader.value_or(DEFAULT_FRAGMENT_SHADER));

  // Create the vertex and fragment shader stage info
  VkPipelineShaderStageCreateInfo vert_shader_stage_info = {};
  vert_shader_stage_info.sType                           = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  vert_shader_stage_info.stage                           = VK_SHADER_STAGE_VERTEX_BIT;
  vert_shader_stage_info.module                          = vertex_shader.get_module();
  vert_shader_stage_info.pName                           = "main";

  VkPipelineShaderStageCreateInfo frag_shader_stage_info = {};
  frag_shader_stage_info.sType                           = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  frag_shader_stage_info.stage                           = VK_SHADER_STAGE_FRAGMENT_BIT;
  frag_shader_stage_info.module                          = fragment_shader.get_module();
  frag_shader_stage_info.pName                           = "main";

  // Create the shader stages
  VkPipelineShaderStageCreateInfo shader_stages[] = {vert_shader_stage_info, frag_shader_stage_info};

  // Create the vertex input info

  std::vector<VkVertexInputBindingDescription> vertex_binding_descriptions;
  for (auto vertex_binding: config.vertex_bindings)
  {
    vertex_binding_descriptions.push_back({vertex_binding.binding, vertex_binding.stride});
  }

  std::vector<VkVertexInputAttributeDescription> vertex_attribute_descriptions;
  for (const auto& [binding, location, offset, format, type, size]: config.vertex_attributes)
  {
    vertex_attribute_descriptions.push_back({binding, location, convert_to_vulkan_format(format, type, size), offset});
  }

  VkPipelineVertexInputStateCreateInfo vertex_input_info{};
  vertex_input_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

  // Create the input assembly
  VkPipelineInputAssemblyStateCreateInfo input_assembly{};
  input_assembly.sType                  = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
  input_assembly.topology               = convert_to_vulkan_topology(config.topology);
  input_assembly.primitiveRestartEnable = VK_FALSE;

  std::vector<VkViewport> viewports;
  for (const auto& [x, y, width, height, min_depth, max_depth]: config.viewports)
  {
    viewports.push_back({x, y, width, height, min_depth, max_depth});
  }

  if (viewports.empty())
  {
    m_logger->warn("No viewports specified");
  }

  std::vector<VkRect2D> scissors;
  for (const auto& [x, y, width, height]: config.scissors)
  {
    scissors.push_back({{static_cast<int>(x), static_cast<int>(y)},
                        {static_cast<unsigned int>(width), static_cast<unsigned int>(height)}});
  }

  if (scissors.empty())
  {
    m_logger->warn("No scissors specified");
  }

  VkPipelineViewportStateCreateInfo viewport_state{};
  viewport_state.sType         = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
  viewport_state.viewportCount = (unsigned int) viewports.size();
  viewport_state.pViewports    = viewports.data();
  viewport_state.scissorCount  = (unsigned int) scissors.size();
  viewport_state.pScissors     = scissors.data();

  VkPipelineRasterizationStateCreateInfo rasterizer{};
  rasterizer.sType                   = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
  rasterizer.depthClampEnable        = VK_FALSE;
  rasterizer.rasterizerDiscardEnable = VK_FALSE;
  rasterizer.polygonMode             = convert_to_vulkan_polygon_mode(config.polygon_mode);
  rasterizer.lineWidth               = 1.0f;
  rasterizer.cullMode                = convert_to_vulkan_cull_mode(config.cull_mode);
  rasterizer.frontFace               = convert_to_vulkan_front_face(config.front_face);
  rasterizer.depthBiasEnable         = VK_FALSE;

  VkPipelineMultisampleStateCreateInfo multisampling{};
  multisampling.sType                = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
  multisampling.sampleShadingEnable  = VK_FALSE;
  multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

  std::vector<VkPipelineColorBlendAttachmentState> color_blend_attachments;
  for (auto color_blend: config.color_blends)
  {
    VkPipelineColorBlendAttachmentState color_blend_attachment{};
    color_blend_attachment.colorWriteMask = convert_to_vulkan_color_component_flags(color_blend);
    color_blend_attachment.blendEnable    = color_blend.blend_enable;
    color_blend_attachments.push_back(color_blend_attachment);
  }

  VkPipelineColorBlendStateCreateInfo color_blending{};
  color_blending.sType           = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
  color_blending.logicOpEnable   = VK_FALSE;
  color_blending.logicOp         = VK_LOGIC_OP_COPY;
  color_blending.attachmentCount = (unsigned int) color_blend_attachments.size();
  color_blending.pAttachments    = color_blend_attachments.data();

  VkPipelineLayoutCreateInfo pipeline_layout_info = {};
  pipeline_layout_info.sType                      = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;

  auto pipeline_layout_result =
      vkCreatePipelineLayout(m_logical_device, &pipeline_layout_info, nullptr, &m_pipeline_layout);
  if (pipeline_layout_result != VK_SUCCESS)
  {
    throw EngineException("Failed to create pipeline layout");
  }

  VkAttachmentDescription color_attachment = {};
  color_attachment.format                  = m_target->m_surface_format.format;
  color_attachment.samples                 = VK_SAMPLE_COUNT_1_BIT;
  color_attachment.loadOp                  = VK_ATTACHMENT_LOAD_OP_CLEAR;
  color_attachment.storeOp                 = VK_ATTACHMENT_STORE_OP_STORE;
  color_attachment.stencilLoadOp           = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  color_attachment.stencilStoreOp          = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  color_attachment.initialLayout           = VK_IMAGE_LAYOUT_UNDEFINED;
  color_attachment.finalLayout             = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

  VkAttachmentReference color_attachment_ref = {};
  color_attachment_ref.attachment            = 0;
  color_attachment_ref.layout                = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

  VkSubpassDescription subpass = {};
  subpass.pipelineBindPoint    = VK_PIPELINE_BIND_POINT_GRAPHICS;
  subpass.colorAttachmentCount = 1;
  subpass.pColorAttachments    = &color_attachment_ref;

  // Create render pass
  VkRenderPassCreateInfo render_pass_info = {};
  render_pass_info.sType                  = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
  render_pass_info.attachmentCount        = 1;
  render_pass_info.pAttachments           = &color_attachment;
  render_pass_info.subpassCount           = 1;
  render_pass_info.pSubpasses             = &subpass;

  VkSubpassDependency dependency = {};
  dependency.srcSubpass          = VK_SUBPASS_EXTERNAL;
  dependency.dstSubpass          = 0;
  dependency.srcStageMask        = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
  dependency.srcAccessMask       = 0;
  dependency.dstStageMask        = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
  dependency.dstAccessMask       = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

  render_pass_info.dependencyCount = 1;
  render_pass_info.pDependencies   = &dependency;

  auto render_pass_result = vkCreateRenderPass(m_logical_device, &render_pass_info, nullptr, &m_render_pass);
  if (render_pass_result != VK_SUCCESS)
  {
    throw EngineException("Failed to create render pass");
  }

  VkGraphicsPipelineCreateInfo pipeline_info = {};
  pipeline_info.sType                        = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
  pipeline_info.stageCount                   = 2;
  pipeline_info.pStages                      = shader_stages;
  pipeline_info.pVertexInputState            = &vertex_input_info;
  pipeline_info.pInputAssemblyState          = &input_assembly;
  pipeline_info.pViewportState               = &viewport_state;
  pipeline_info.pRasterizationState          = &rasterizer;
  pipeline_info.pMultisampleState            = &multisampling;
  pipeline_info.pColorBlendState             = &color_blending;
  pipeline_info.layout                       = m_pipeline_layout;
  pipeline_info.renderPass                   = m_render_pass;
  pipeline_info.subpass                      = 0;
  pipeline_info.basePipelineHandle           = VK_NULL_HANDLE;

  auto pipeline_result =
      vkCreateGraphicsPipelines(m_logical_device, VK_NULL_HANDLE, 1, &pipeline_info, nullptr, &m_pipeline);
  if (pipeline_result != VK_SUCCESS)
  {
    throw EngineException("Failed to create graphics pipeline");
  }
}

void
VulkanWindowRenderer::create_framebuffers(const RendererConfig& config)
{
  const auto device           = m_vulkan_app->get_logical_device();
  const auto swapchain_images = m_target->m_swapchain_images;

  m_framebuffers.resize(swapchain_images.size());

  for (unsigned int i = 0; i < swapchain_images.size(); ++i)
  {
    const VkImageView attachments[] = {m_target->m_swapchain_image_views[i]};

    VkFramebufferCreateInfo framebuffer_info = {};
    framebuffer_info.sType                   = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    framebuffer_info.renderPass              = m_render_pass;
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
VulkanWindowRenderer::create_command_pool(const RendererConfig& config)
{
  const auto& [graphics_family, present_family] = m_vulkan_app->get_queue_family_indices();

  VkCommandPoolCreateInfo pool_info = {};
  pool_info.sType                   = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  pool_info.queueFamilyIndex        = graphics_family.value();
  pool_info.flags                   = 0;

  auto command_pool_result = vkCreateCommandPool(m_logical_device, &pool_info, nullptr, &m_command_pool);
  if (command_pool_result != VK_SUCCESS)
  {
    throw EngineException("Failed to create command pool");
  }
}

void
VulkanWindowRenderer::create_command_buffers(const RendererConfig& config)
{
  m_command_buffers.resize(m_framebuffers.size());

  VkCommandBufferAllocateInfo alloc_info = {};
  alloc_info.sType                       = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  alloc_info.commandPool                 = m_command_pool;
  alloc_info.level                       = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  alloc_info.commandBufferCount          = (unsigned int) m_command_buffers.size();

  auto command_buffer_result = vkAllocateCommandBuffers(m_logical_device, &alloc_info, m_command_buffers.data());
  if (command_buffer_result != VK_SUCCESS)
  {
    throw EngineException("Failed to allocate command buffers");
  }

  m_logger->trace("Allocated {} command buffers", m_command_buffers.size());

  for (unsigned int i = 0; i < m_command_buffers.size(); ++i)
  {
    VkCommandBufferBeginInfo begin_info = {};
    begin_info.sType                    = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    auto begin_result = vkBeginCommandBuffer(m_command_buffers[i], &begin_info);
    if (begin_result != VK_SUCCESS)
    {
      throw EngineException("Failed to begin recording command buffer");
    }

    VkRenderPassBeginInfo render_pass_info = {};
    render_pass_info.sType                 = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    render_pass_info.renderPass            = m_render_pass;
    render_pass_info.framebuffer           = m_framebuffers[i];
    render_pass_info.renderArea.offset     = {0, 0};
    render_pass_info.renderArea.extent     = {(unsigned int) m_target->width(), (unsigned int) m_target->height()};

    VkClearValue clear_color = {
        config.clear_color.r(), config.clear_color.g(), //
        config.clear_color.b(), config.clear_color.a()  //
    };
    render_pass_info.clearValueCount = 1;
    render_pass_info.pClearValues    = &clear_color;

    vkCmdBeginRenderPass(m_command_buffers[i], &render_pass_info, VK_SUBPASS_CONTENTS_INLINE);
    vkCmdBindPipeline(m_command_buffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, m_pipeline);
    vkCmdDraw(m_command_buffers[i], 3, 1, 0, 0);
    vkCmdEndRenderPass(m_command_buffers[i]);

    auto end_result = vkEndCommandBuffer(m_command_buffers[i]);
    if (end_result != VK_SUCCESS)
    {
      throw EngineException("Failed to record command buffer");
    }

    m_logger->trace("Command buffer {} created successfully", i);
  }
}

void
VulkanWindowRenderer::create_synchronization_objects(const RendererConfig& config)
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
} // namespace setsugen
