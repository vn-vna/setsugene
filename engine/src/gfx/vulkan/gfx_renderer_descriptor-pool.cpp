#include "gfx_renderer.h"

#include <vulkan/vk_enum_string_helper.h>
#include <vulkan/vulkan.h>

namespace setsugen
{

GfxDescriptorPool::
GfxDescriptorPool(size_t pool_size, size_t max_sets)
    : m_vulkan_app{GfxApplication::get_current()},
      m_logical_device{GfxApplication::get_current()->get_logical_device()}, m_descriptor_pool{nullptr}
{
  VkDescriptorPoolSize pool_size_desc{};
  pool_size_desc.type            = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
  pool_size_desc.descriptorCount = pool_size;

  VkDescriptorPoolCreateInfo pool_info{};
  pool_info.sType         = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
  pool_info.poolSizeCount = 1;
  pool_info.pPoolSizes    = &pool_size_desc;
  pool_info.maxSets       = max_sets;

  auto descriptor_pool_result = vkCreateDescriptorPool(m_logical_device, &pool_info, nullptr, &m_descriptor_pool);
  if (descriptor_pool_result != VK_SUCCESS)
  {
    throw EngineException("Failed to create descriptor pool");
  }
}

GfxDescriptorPool::~
GfxDescriptorPool()
{
  vkDestroyDescriptorPool(m_vulkan_app->get_logical_device(), m_descriptor_pool, nullptr);
}

VkDescriptorPool
GfxDescriptorPool::get_handler() const
{
  return m_descriptor_pool;
}

std::unique_ptr<GfxDescriptorPool>
GfxDescriptorPool::create(size_t pool_size, size_t max_sets)
{
  return std::make_unique<GfxDescriptorPool>(pool_size, max_sets);
}

std::unique_ptr<GfxDescriptorSet>
GfxDescriptorPool::allocate_descriptor_set(VkDescriptorSetLayout layout)
{
  return std::make_unique<GfxDescriptorSet>(this, layout);
}

GfxDescriptorSet::
GfxDescriptorSet(GfxDescriptorPool* pool, VkDescriptorSetLayout layout)
    : m_vulkan_app{GfxApplication::get_current()},
      m_logical_device{GfxApplication::get_current()->get_logical_device()}, m_descriptor_set{nullptr}
{
  VkDescriptorSetAllocateInfo alloc_info{};
  alloc_info.sType              = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
  alloc_info.descriptorPool     = pool->get_handler();
  alloc_info.descriptorSetCount = 1;
  alloc_info.pSetLayouts        = &layout;

  if (auto descriptor_set_result = vkAllocateDescriptorSets(m_logical_device, &alloc_info, &m_descriptor_set);
      descriptor_set_result != VK_SUCCESS)
  {
    throw EngineException("Failed to allocate descriptor set due to error: {}", string_VkResult(descriptor_set_result));
  }
}

GfxDescriptorSet::~
GfxDescriptorSet()
{}

VkDescriptorSet
GfxDescriptorSet::get_handler() const
{
  return m_descriptor_set;
}

void
GfxDescriptorSet::update_uniform_buffers(const std::vector<UniformBuffer*>& uniform_buffers)
{
  for (size_t i = 0; i < uniform_buffers.size(); ++i)
  {
    VkDescriptorBufferInfo buffer_info{};
    buffer_info.buffer = uniform_buffers[i]->get_handler();
    buffer_info.offset = 0;
    buffer_info.range  = VK_WHOLE_SIZE;

    VkWriteDescriptorSet descriptor_write{};
    descriptor_write.sType           = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    descriptor_write.dstSet          = m_descriptor_set;
    descriptor_write.dstBinding      = i;
    descriptor_write.dstArrayElement = 0;
    descriptor_write.descriptorType  = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    descriptor_write.descriptorCount = 1;
    descriptor_write.pBufferInfo     = &buffer_info;

    vkUpdateDescriptorSets(m_logical_device, 1, &descriptor_write, 0, nullptr);
  }
}

} // namespace setsugen
