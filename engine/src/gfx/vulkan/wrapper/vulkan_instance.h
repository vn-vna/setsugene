#pragma once

#ifdef SETSUGENE_WINDOWS
#define VK_USE_PLATFORM_WIN32_KHR
#endif

#include <volk.h>

#include "setsugen/version.h"

namespace setsugen::gfx::vulkan
{

class PhysicalDevice;

class Instance
{
public:
  class Builder;

  friend class Builder;

  ~Instance();

  VkInstance                     handle();
  Bool                           enable_validation();
  DArray<Owner<PhysicalDevice>>& physical_devices();

private:
  Instance(VkInstance instance, Bool enable_validation);

  VkInstance                    m_instance;
  Bool                          m_enable_validation;
  DArray<Owner<PhysicalDevice>> m_physical_devices;
};

class Instance::Builder
{
public:
  Builder();

  Owner<Instance> build();

  Builder& with_app_name(const String& app_name);
  Builder& with_app_version(const Version& version);
  Builder& with_extension(const String& extension);
  Builder& with_layer(const String& layer);
  Builder& enable_validation(Bool enable);

private:
  void enable_required_layers();
  void enable_validation_layers();
  void check_instance_layers();

  void enable_required_extensions();
  void enable_validation_extensions();
  void check_instance_extensions();

  String               m_app_name;
  Version              m_app_version;
  VkInstanceCreateInfo m_create_info;
  VkApplicationInfo    m_app_info;
  DArray<String>       m_instance_extensions;
  DArray<String>       m_instance_layers;
  Bool                 m_enable_validation;
};

} // namespace setsugen::gfx::vulkan
