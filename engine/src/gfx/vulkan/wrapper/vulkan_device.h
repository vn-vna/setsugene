#pragma once

#include <setsugen/exception.h>
#include <setsugen/logger.h>
#include <volk.h>


namespace setsugen::gfx::vulkan
{

class Instance;
class PhysicalDevice;
class PhysicalDeviceQueueFamily;

class DeviceQueue
{
public:
  friend class Device;

  DeviceQueue(VkQueue queue);

  VkQueue handle() const;

private:
  VkQueue m_queue;
};

class Device
{
public:
  class Builder;

  friend class Builder;

  ~Device();

  VkDevice handle() const;

  PhysicalDevice& physical_device();
  Instance&       instance();
  DeviceQueue&    graphics_queue();
  DeviceQueue&    compute_queue();
  DeviceQueue&    transfer_queue();

private:
  Device(VkDevice device, PhysicalDevice& physical_device, VkQueue graphics_queue, VkQueue compute_queue,
         VkQueue transfer_queue);

  VkDevice        m_device;
  PhysicalDevice& m_physical_device;
  Instance&       m_instance;
  DeviceQueue     m_graphics_queue;
  DeviceQueue     m_compute_queue;
  DeviceQueue     m_transfer_queue;
};

class Device::Builder
{
public:
  Builder(PhysicalDevice& physical_device);

  Owner<Device> build();

private:
  VkDeviceCreateInfo m_create_info;
  PhysicalDevice&    m_physical_device;
};

} // namespace setsugen::gfx::vulkan
