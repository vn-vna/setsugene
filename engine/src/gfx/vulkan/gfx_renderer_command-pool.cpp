#include "gfx_renderer.h"

namespace setsugen
{

GfxCommandPool::GfxCommandPool(VkCommandPoolCreateFlags flags) : m_vulkan_app{GfxApplication::get_current()}
{
  m_logical_device                              = m_vulkan_app->get_logical_device();
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

GfxCommandPool::~GfxCommandPool()
{
  vkDestroyCommandPool(m_logical_device, m_command_pool, nullptr);
}

std::unique_ptr<GfxCommandBuffer>
GfxCommandPool::allocate_command_buffer(VkCommandBufferLevel level)
{
  return std::make_unique<GfxCommandBuffer>(this, level);
}

VkCommandPool
GfxCommandPool::get_command_pool() const
{
  return m_command_pool;
}

std::unique_ptr<GfxCommandPool>
GfxCommandPool::create(VkCommandPoolCreateFlags flags)
{
  return std::make_unique<GfxCommandPool>(flags);
}


GfxCommandBuffer::GfxCommandBuffer(GfxCommandPool* cmd_pool, VkCommandBufferLevel level)
{
  m_logical_device = GfxApplication::get_current()->get_logical_device();
  m_command_pool   = cmd_pool->get_command_pool();

  VkCommandBufferAllocateInfo alloc_info = {};
  alloc_info.sType                       = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  alloc_info.level                       = level;
  alloc_info.commandPool                 = m_command_pool;
  alloc_info.commandBufferCount          = 1;

  auto command_buffer_result = vkAllocateCommandBuffers(m_logical_device, &alloc_info, &m_command_buffer);
  if (command_buffer_result != VK_SUCCESS)
  {
    throw EngineException("Failed to allocate command buffer");
  }
}

GfxCommandBuffer::~GfxCommandBuffer()
{}

VkCommandBuffer
GfxCommandBuffer::get_handler() const
{
  return m_command_buffer;
}

void
GfxCommandBuffer::begin()
{
  VkCommandBufferBeginInfo begin_info = {};
  begin_info.sType                    = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  begin_info.flags                    = 0;
  begin_info.pInheritanceInfo         = nullptr;

  vkResetCommandBuffer(m_command_buffer, 0);
  auto begin_result = vkBeginCommandBuffer(m_command_buffer, &begin_info);
  if (begin_result != VK_SUCCESS)
  {
    throw EngineException("Failed to begin recording command buffer");
  }
}

void
GfxCommandBuffer::end()
{
  auto end_result = vkEndCommandBuffer(m_command_buffer);
  if (end_result != VK_SUCCESS)
  {
    throw EngineException("Failed to end recording command buffer");
  }
}

void
GfxCommandBuffer::begin_render_pass(VulkanGraphicsPipeline* pipeline, GfxVulkanRenderTarget* target,
                                    VkFramebuffer framebuffer)
{

  VkRenderPassBeginInfo render_pass_info = {};
  render_pass_info.sType                 = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
  render_pass_info.renderPass            = pipeline->get_render_pass();
  render_pass_info.framebuffer           = framebuffer;
  render_pass_info.renderArea.offset     = {0, 0};
  render_pass_info.renderArea.extent     = {(unsigned int) target->width(), (unsigned int) target->height()};

  auto         color = pipeline->get_config().clear_color;
  VkClearValue clear_color;
  clear_color.color = {{color.r(), color.g(), color.b(), color.a()}};

  render_pass_info.clearValueCount = 1;
  render_pass_info.pClearValues    = &clear_color;
  vkCmdBeginRenderPass(m_command_buffer, &render_pass_info, VK_SUBPASS_CONTENTS_INLINE);
  vkCmdBindPipeline(m_command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline->get_handler());
}

void
GfxCommandBuffer::end_render_pass()
{
  vkCmdEndRenderPass(m_command_buffer);
}

void
GfxCommandBuffer::record_copy_buffer_command(VulkanBuffer* src_buffer, VulkanBuffer* dst_buffer, VkDeviceSize size)
{
  VkBufferCopy copy_region = {};
  copy_region.size         = size;

  vkCmdCopyBuffer(m_command_buffer, src_buffer->get_handler(), dst_buffer->get_handler(), 1, &copy_region);
}


void
GfxCommandBuffer::bind_vertex_buffers(const std::vector<VertexBuffer*>& vertex_buffers)
{
  std::vector<VkBuffer>     buffers;
  std::vector<VkDeviceSize> offsets;

  for (const auto& vertex_buffer: vertex_buffers)
  {
    buffers.push_back(vertex_buffer->get_handler());
    offsets.push_back(0);
  }

  vkCmdBindVertexBuffers(m_command_buffer, 0, static_cast<uint32_t>(buffers.size()), buffers.data(), offsets.data());
}

void
GfxCommandBuffer::bind_index_buffer(IndexBuffer* index_buffer)
{
  vkCmdBindIndexBuffer(m_command_buffer, index_buffer->get_handler(), 0, VK_INDEX_TYPE_UINT32);
}

void
GfxCommandBuffer::bind_descriptor_set(const std::vector<GfxDescriptorSet*>& descriptor_sets,
                                      VulkanGraphicsPipeline*               pipeline)
{
  std::vector<VkDescriptorSet> descriptor_set_handlers;
  for (const auto& set: descriptor_sets)
  {
    descriptor_set_handlers.push_back(set->get_handler());
  }

  vkCmdBindDescriptorSets(m_command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline->get_layout_handler(), 0,
                          descriptor_set_handlers.size(), descriptor_set_handlers.data(), 0, nullptr);
}

void
GfxCommandBuffer::draw(VulkanGraphicsPipeline* pipeline, std::vector<VertexBuffer*>& vertex_buffers,
                       IndexBuffer* index_buffer, std::vector<GfxDescriptorSet*>& descriptor_sets, uint32_t index_count)
{
  // Bind vertex buffers
  bind_vertex_buffers(vertex_buffers);
  bind_index_buffer(index_buffer);
  bind_descriptor_set(descriptor_sets, pipeline);

  // Draw
  vkCmdDrawIndexed(m_command_buffer, index_count, 1, 0, 0, 0);
}


} // namespace setsugen
