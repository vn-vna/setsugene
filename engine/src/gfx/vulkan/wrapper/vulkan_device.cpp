#include "vulkan_device.h"
#include "vulkan_instance.h"
#include "vulkan_physical_device.h"

namespace setsugen::gfx::vulkan
{

Device::Device(VkDevice device, PhysicalDevice& physical_device, VkQueue graphics_queue, VkQueue compute_queue,
               VkQueue transfer_queue)
    : m_device(device), m_physical_device(physical_device), m_instance(physical_device.instance()),
      m_graphics_queue(graphics_queue), m_compute_queue(compute_queue), m_transfer_queue(transfer_queue)
{}

Device::~Device()
{
  vkDestroyDevice(m_device, nullptr);
}

Device::Builder::Builder(PhysicalDevice& physical_device) : m_create_info{}, m_physical_device(physical_device)
{}

Owner<Device>
Device::Builder::build()
{
  DArray<String> enabled_features;
  DArray<String> enabled_layers;
  DArray<String> enabled_extensions;

  if (m_physical_device.instance().enable_validation())
  {
    enabled_layers.push_back("VK_LAYER_KHRONOS_validation");
  }

  Optional<UInt32> graphics_family_index;
  Optional<UInt32> compute_family_index;
  Optional<UInt32> transfer_family_index;

  auto& queue_families = m_physical_device.queue_families();

  for (UInt32 i = 0; i < m_physical_device.queue_families().size(); ++i)
  {
    auto& family = m_physical_device.queue_families()[i];
    if (!graphics_family_index.has_value() && family.graphics())
    {
      graphics_family_index = i;
    }

    if (!compute_family_index.has_value() && family.compute())
    {
      compute_family_index = i;
    }

    if (!transfer_family_index.has_value() && family.transfer())
    {
      transfer_family_index = i;
    }
  }

  if (!graphics_family_index.has_value())
  {
    throw InvalidOperationException("No graphics queue family found");
  }

  if (!compute_family_index.has_value())
  {
    throw InvalidOperationException("No compute queue family found");
  }

  if (!transfer_family_index.has_value())
  {
    throw InvalidOperationException("No transfer queue family found");
  }

  Float32 queue_priorities[1024];

  UnorderedMap<UInt32, UInt32> queue_counts;
  queue_counts[graphics_family_index.value()]++;
  queue_counts[compute_family_index.value()]++;
  queue_counts[transfer_family_index.value()]++;

  DArray<VkDeviceQueueCreateInfo> queue_create_infos;
  for (const auto& [family_index, count]: queue_counts)
  {
    for (UInt32 i = 0; i < count; ++i)
    {
      queue_priorities[i] = 1.0f;
    }

    VkDeviceQueueCreateInfo info{};
    info.sType            = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    info.queueFamilyIndex = family_index;
    info.queueCount       = count;
    info.pQueuePriorities = queue_priorities;

    queue_create_infos.push_back(info);
  }

  const char* enabled_extensions_cstr[1024];
  for (UInt32 i = 0; i < enabled_extensions.size(); ++i)
  {
    enabled_extensions_cstr[i] = enabled_extensions[i].c_str();
  }

  const char* enabled_layers_cstr[1024];
  for (UInt32 i = 0; i < enabled_layers.size(); ++i)
  {
    enabled_layers_cstr[i] = enabled_layers[i].c_str();
  }

  m_create_info.sType                   = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  m_create_info.pNext                   = nullptr;
  m_create_info.flags                   = 0;
  m_create_info.queueCreateInfoCount    = static_cast<UInt32>(queue_create_infos.size());
  m_create_info.pQueueCreateInfos       = queue_create_infos.data();
  m_create_info.enabledLayerCount       = static_cast<UInt32>(enabled_layers.size());
  m_create_info.ppEnabledLayerNames     = enabled_layers_cstr;
  m_create_info.enabledExtensionCount   = static_cast<UInt32>(enabled_extensions.size());
  m_create_info.ppEnabledExtensionNames = enabled_extensions_cstr;
  m_create_info.pEnabledFeatures        = nullptr;

  VkDevice device = VK_NULL_HANDLE;
  VkResult result = vkCreateDevice(m_physical_device.handle(), &m_create_info, nullptr, &device);

  if (result != VK_SUCCESS)
  {
    throw InvalidOperationException("Cannot create Vulkan device");
  }

  UnorderedMap<UInt32, UInt32> iteration_counts;

  VkQueue graphics_queue = VK_NULL_HANDLE;
  vkGetDeviceQueue(device, graphics_family_index.value(), iteration_counts[graphics_family_index.value()]++,
                   &graphics_queue);

  VkQueue compute_queue = VK_NULL_HANDLE;
  vkGetDeviceQueue(device, compute_family_index.value(), iteration_counts[compute_family_index.value()]++,
                   &compute_queue);

  VkQueue transfer_queue = VK_NULL_HANDLE;
  vkGetDeviceQueue(device, transfer_family_index.value(), iteration_counts[transfer_family_index.value()]++,
                   &transfer_queue);

  return Owner<Device>{new Device{device, m_physical_device, graphics_queue, compute_queue, transfer_queue}};
}

VkDevice
Device::handle() const
{
  return m_device;
}

PhysicalDevice&
Device::physical_device()
{
  return m_physical_device;
}

Instance&
Device::instance()
{
  return m_instance;
}

DeviceQueue&
Device::graphics_queue()
{
  return m_graphics_queue;
}

DeviceQueue&
Device::compute_queue()
{
  return m_compute_queue;
}

DeviceQueue&
Device::transfer_queue()
{
  return m_transfer_queue;
}

DeviceQueue::DeviceQueue(VkQueue queue) : m_queue(queue)
{}

VkQueue
DeviceQueue::handle() const
{
  return m_queue;
}

} // namespace setsugen::gfx::vulkan
