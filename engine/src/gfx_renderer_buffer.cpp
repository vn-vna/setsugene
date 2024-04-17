#include <memory>
#include <setsugen/application.h>
#include <setsugen/exception.h>

#include "gfx_renderer.h"
#include "setsugen/gfx.h"

namespace setsugen
{

VulkanBuffer::VulkanBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties)
    : m_vulkan_app(GfxApplication::get_current())
{
  m_logger         = Application::current_app()->create_logger("setsugen::VulkanBuffer");
  m_logical_device = m_vulkan_app->get_logical_device();

  VkBufferCreateInfo buffer_info = {};
  buffer_info.sType              = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
  buffer_info.size               = size;
  buffer_info.usage              = usage;
  buffer_info.sharingMode        = VK_SHARING_MODE_EXCLUSIVE;

  if (vkCreateBuffer(m_logical_device, &buffer_info, nullptr, &m_buffer) != VK_SUCCESS)
  {
    throw InvalidStateException("Failed to create buffer");
  }

  VkMemoryRequirements mem_requirements;
  vkGetBufferMemoryRequirements(m_logical_device, m_buffer, &mem_requirements);

  VkMemoryAllocateInfo alloc_info = {};
  alloc_info.sType                = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  alloc_info.allocationSize       = mem_requirements.size;
  alloc_info.memoryTypeIndex      = m_vulkan_app->find_memory_type(mem_requirements.memoryTypeBits, properties);

  if (vkAllocateMemory(m_logical_device, &alloc_info, nullptr, &m_buffer_memory) != VK_SUCCESS)
  {
    throw InvalidStateException("Failed to allocate buffer memory");
  }

  vkBindBufferMemory(m_logical_device, m_buffer, m_buffer_memory, 0);
}

VulkanBuffer::~VulkanBuffer()
{
  vkDestroyBuffer(m_logical_device, m_buffer, nullptr);
  vkFreeMemory(m_logical_device, m_buffer_memory, nullptr);
}

void
VulkanBuffer::copy_data(const void* data, VkDeviceSize size)
{
  void*        mapped_data;
  VkDeviceSize buffer_size = size;

  vkMapMemory(m_logical_device, m_buffer_memory, 0, buffer_size, 0, &mapped_data);
  memcpy(mapped_data, data, static_cast<size_t>(buffer_size));
  vkUnmapMemory(m_logical_device, m_buffer_memory);
}

VkBuffer
VulkanBuffer::get_handler() const
{
  return m_buffer;
}

VkDeviceMemory
VulkanBuffer::get_memory_handler() const
{
  return m_buffer_memory;
}

void
VulkanBuffer::copy_buffer(GfxCommandPool* command_pool, VulkanBuffer* src_buffer, VkDeviceSize size)
{
  auto command_buffer = command_pool->allocate_command_buffer();
  command_buffer->begin();
  command_buffer->record_copy_buffer_command(src_buffer, this, size);
  command_buffer->end();
  m_vulkan_app->execute_one_time_commands(m_vulkan_app->get_graphics_queue(), {command_buffer.get()});
}

VertexBuffer::VertexBuffer(size_t size)
    : VulkanBuffer(size, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
                   VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
{}

VertexBuffer::~VertexBuffer() = default;

std::unique_ptr<VertexBuffer>
VertexBuffer::from_meshdata(GfxVulkanRenderer* renderer, MeshData* data, const VertexBufferLayout& layout)
{
  auto positions = data->get_positions();
  auto normals   = data->get_normals();

  auto vsize = positions->size();

  std::vector<float> vertex_data;

  for (size_t i = 0; i < vsize; i++)
  {
    for (auto element: layout)
    {
      switch (element)
      {
        case VertexElement::Position:
          vertex_data.push_back(positions->at(i).x());
          vertex_data.push_back(positions->at(i).y());
          vertex_data.push_back(positions->at(i).z());
          break;
        case VertexElement::Normal:
          vertex_data.push_back(normals->at(i).x());
          vertex_data.push_back(normals->at(i).y());
          vertex_data.push_back(normals->at(i).z());
          break;
        default: break;
      }
    }
  }

  auto buffer          = std::make_unique<VertexBuffer>(vertex_data.size() * sizeof(float));
  auto stagging_buffer = StaggingBuffer::create(vertex_data.size() * sizeof(float));

  stagging_buffer->copy_data(vertex_data.data(), vertex_data.size() * sizeof(float));
  buffer->copy_buffer(renderer->get_command_pool(), stagging_buffer.get(), vertex_data.size() * sizeof(float));

  return buffer;
}

IndexBuffer::IndexBuffer(size_t indicies_count)
    : VulkanBuffer(indicies_count * sizeof(unsigned int),
                   VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
                   VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
{}

IndexBuffer::~IndexBuffer() = default;

std::unique_ptr<IndexBuffer>
IndexBuffer::from_meshdata(GfxVulkanRenderer* renderer, MeshData* data)
{
  auto indices = data->get_indices();
  auto buffer  = std::make_unique<IndexBuffer>(indices->size());

  auto stagging_buffer = StaggingBuffer::create(indices->size() * sizeof(unsigned int));
  stagging_buffer->copy_data(indices->data(), indices->size() * sizeof(unsigned int));

  buffer->copy_buffer(renderer->get_command_pool(), stagging_buffer.get(), indices->size() * sizeof(unsigned int));

  return buffer;
}

std::unique_ptr<UniformBuffer>
UniformBuffer::create(size_t size)
{
  return std::make_unique<UniformBuffer>(size);
}

UniformBuffer::UniformBuffer(size_t size)
    : VulkanBuffer(size, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                   VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)
{}

UniformBuffer::~UniformBuffer() = default;

StaggingBuffer::StaggingBuffer(VkDeviceSize size)
    : VulkanBuffer(size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                   VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)
{}

StaggingBuffer::~StaggingBuffer()
{}

std::unique_ptr<StaggingBuffer>
StaggingBuffer::create(VkDeviceSize size)
{
  return std::make_unique<StaggingBuffer>(size);
}


} // namespace setsugen
