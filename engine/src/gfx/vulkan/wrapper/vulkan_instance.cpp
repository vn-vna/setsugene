#include "vulkan_instance.h"

#include "setsugen/exception.h"
#include "vulkan_physical_device.h"


namespace setsugen::gfx::vulkan
{

Instance::Instance(VkInstance instance, Bool enable_validation)
    : m_instance(instance), m_enable_validation(enable_validation)
{
  volkLoadInstance(m_instance);

  UInt32 pdevice_count = 0;
  vkEnumeratePhysicalDevices(m_instance, &pdevice_count, nullptr);

  if (pdevice_count == 0)
  {
    throw InvalidOperationException("No physical devices found");
  }

  DArray<VkPhysicalDevice> pdevices(pdevice_count);
  vkEnumeratePhysicalDevices(m_instance, &pdevice_count, pdevices.data());

  for (const auto& pdevice: pdevices)
  {
    m_physical_devices.push_back(Owner<PhysicalDevice>{new PhysicalDevice{*this, pdevice}});
  }
}

Instance::~Instance()
{
  vkDestroyInstance(m_instance, nullptr);
}

VkInstance
Instance::handle()
{
  return m_instance;
}

Bool
Instance::enable_validation()
{
  return m_enable_validation;
}

DArray<Owner<PhysicalDevice>>&
Instance::physical_devices()
{
  return m_physical_devices;
}

Instance::Builder::Builder() : m_app_name("Setsugen Application"), m_app_version(1, 0, 0), m_enable_validation(true)
{}

Instance::Builder&
Instance::Builder::with_app_name(const String& app_name)
{
  m_app_name = app_name;
  return *this;
}

Instance::Builder&
Instance::Builder::with_app_version(const Version& version)
{
  m_app_version = version;
  return *this;
}

Instance::Builder&
Instance::Builder::with_extension(const String& extension)
{
  m_instance_extensions.push_back(extension);
  return *this;
}

Instance::Builder&
Instance::Builder::with_layer(const String& layer)
{
  m_instance_layers.push_back(layer);
  return *this;
}

Void
Instance::Builder::enable_required_layers()
{}

Instance::Builder&
Instance::Builder::enable_validation(Bool enable)
{
  m_enable_validation = enable;
  return *this;
}

Void
Instance::Builder::enable_validation_layers()
{
  if (!m_enable_validation)
  {
    return;
  }

  m_instance_layers.push_back("VK_LAYER_KHRONOS_validation");
}

Void
Instance::Builder::enable_required_extensions()
{
  m_instance_extensions.push_back(VK_KHR_SURFACE_EXTENSION_NAME);

#ifdef SETSUGENE_WINDOWS
  m_instance_extensions.push_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
  m_instance_extensions.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
#endif
}

Void
Instance::Builder::enable_validation_extensions()
{
  if (!m_enable_validation)
  {
    return;
  }

  m_instance_extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
}

Void
Instance::Builder::check_instance_layers()
{
  UInt32 count = 0;
  vkEnumerateInstanceLayerProperties(&count, nullptr);

  DArray<VkLayerProperties> layers(count);
  vkEnumerateInstanceLayerProperties(&count, layers.data());

  UnorderedSet<String> layer_names(count);
  for (const auto& layer: layers)
  {
    layer_names.insert(layer.layerName);
  }

  for (const auto& enabled_layer: m_instance_layers)
  {
    if (!layer_names.contains(enabled_layer))
    {
      throw InvalidStateException("Layer {} is not supported by host machine", {enabled_layer});
    }
  }
}

Void
Instance::Builder::check_instance_extensions()
{
  UInt32 count = 0;
  vkEnumerateInstanceExtensionProperties(nullptr, &count, nullptr);

  DArray<VkExtensionProperties> extensions(count);
  vkEnumerateInstanceExtensionProperties(nullptr, &count, extensions.data());

  UnorderedSet<String> extension_names(count);
  for (const auto& extension: extensions)
  {
    extension_names.insert(extension.extensionName);
  }

  for (const auto& enabled_extension: m_instance_extensions)
  {
    if (!extension_names.contains(enabled_extension))
    {
      throw InvalidStateException("Extension {} is not supported by host machine", {enabled_extension});
    }
  }
}

Owner<Instance>
Instance::Builder::build()
{
  enable_validation_layers();
  check_instance_layers();
  enable_validation_extensions();
  check_instance_extensions();

  UInt32      ext_count = m_instance_extensions.size();
  const char* exts[1024];
  for (UInt32 i = 0; i < ext_count; ++i)
  {
    exts[i] = m_instance_extensions[i].c_str();
  }

  UInt32      layer_count = m_instance_layers.size();
  const char* layers[1024];
  for (UInt32 i = 0; i < layer_count; ++i)
  {
    layers[i] = m_instance_layers[i].c_str();
  }

  m_create_info.flags                   = 0;
  m_create_info.sType                   = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  m_create_info.pNext                   = nullptr;
  m_create_info.pApplicationInfo        = &m_app_info;
  m_create_info.enabledExtensionCount   = ext_count;
  m_create_info.ppEnabledExtensionNames = exts;
  m_create_info.enabledLayerCount       = layer_count;
  m_create_info.ppEnabledLayerNames     = layers;

  m_app_info.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  m_app_info.pNext              = nullptr;
  m_app_info.apiVersion         = VK_API_VERSION_1_0;
  m_app_info.engineVersion      = VK_MAKE_VERSION(1, 0, 0);
  m_app_info.pEngineName        = "vn.vna.setsugen";
  m_app_info.pApplicationName   = "setsugene";
  m_app_info.applicationVersion = m_app_version.data();

  VkResult result;

  VkInstance instance = VK_NULL_HANDLE;
  result              = vkCreateInstance(&m_create_info, nullptr, &instance);

  if (result != VK_SUCCESS)
  {
    throw InvalidOperationException("Cannot create Vulkan instance");
  }

  return Owner<Instance>{new Instance{instance, m_enable_validation}};
}

} // namespace setsugen::gfx::vulkan
