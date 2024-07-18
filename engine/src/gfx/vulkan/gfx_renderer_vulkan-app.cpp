#include "gfx_renderer.h"

namespace setsugen
{
#ifndef NDEBUG
static constexpr bool enable_validation_layers = false;
#else
static constexpr bool enable_validation_layers = false;
#endif

std::atomic<GfxApplication*> GfxApplication::s_current_app;

static const std::vector<const char*> s_validation_layers = {
    "VK_LAYER_KHRONOS_validation",
};

static const std::vector<const char*> s_device_extensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME,
};

static VKAPI_ATTR VkBool32 VKAPI_CALL
vulkan_debug_callback(VkDebugUtilsMessageSeverityFlagBitsEXT severity, VkDebugUtilsMessageTypeFlagsEXT type,
                      const VkDebugUtilsMessengerCallbackDataEXT* callback, void* p_userdata)
{
  std::cout << "[Vulkan] >> " << callback->pMessage << std::endl;
  return VK_FALSE;
}

VkResult
CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
                             const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger)
{
  auto func_addr = vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
  auto func      = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(func_addr);

  if (func != nullptr)
  {
    return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
  }
  else
  {
    return VK_ERROR_EXTENSION_NOT_PRESENT;
  }
}

void
DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger,
                              const VkAllocationCallbacks* pAllocator)
{
  auto func_addr = vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
  auto func      = (PFN_vkDestroyDebugUtilsMessengerEXT) func_addr;
  if (func != nullptr)
  {
    func(instance, debugMessenger, pAllocator);
  }
}

GfxApplication::GfxApplication() : m_instance{nullptr}, m_debug_messenger{nullptr}, m_physical_device_index{-1}
{
  if (s_current_app)
  {
    throw EngineException("A Vulkan application is created");
  }

  s_current_app = this;

  initialize_instance();
  setup_debug_messenger();
  query_physical_devices();
  create_logical_device();
}

GfxApplication::~GfxApplication()
{
  vkDestroyDevice(m_logical_device, nullptr);

  if (enable_validation_layers)
  {
    DestroyDebugUtilsMessengerEXT(m_instance, m_debug_messenger, nullptr);
  }

  vkDestroyInstance(m_instance, nullptr);

  s_current_app = nullptr;
}

VkInstance
GfxApplication::get_instance() const
{
  return m_instance;
}

GfxApplication::QueueFamilyIndices
GfxApplication::get_queue_family_indices() const
{
  return m_queue_family_indices;
}

VkQueue
GfxApplication::get_graphics_queue() const
{
  return m_graphics_queue;
}

VkQueue
GfxApplication::get_present_queue() const
{
  return m_present_queue;
}

VkDevice
GfxApplication::get_logical_device() const
{
  return m_logical_device;
}

void
GfxApplication::initialize_instance()
{
  VkApplicationInfo app_info{};
  app_info.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  app_info.pApplicationName   = "SetsugenE Application";
  app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
  app_info.pEngineName        = "SetsugenE";
  app_info.engineVersion      = VK_MAKE_VERSION(1, 0, 0);
  app_info.apiVersion         = VK_API_VERSION_1_0;

  VkInstanceCreateInfo create_info{};
  create_info.sType            = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  create_info.pApplicationInfo = &app_info;

  auto extensions                     = get_instance_extensions();
  create_info.enabledExtensionCount   = static_cast<unsigned int>(extensions.size());
  create_info.ppEnabledExtensionNames = extensions.data();

  auto layers                     = get_instance_layers();
  create_info.enabledLayerCount   = static_cast<unsigned int>(layers.size());
  create_info.ppEnabledLayerNames = layers.data();

  auto result = vkCreateInstance(&create_info, nullptr, &m_instance);
  if (result != VK_SUCCESS)
  {
    throw EngineException("Failed to create Vulkan instance");
  }
}

std::vector<const char*>
GfxApplication::get_instance_layers()
{
  std::vector<const char*> layers;

  if constexpr (enable_validation_layers)
  {
    layers.insert(layers.end(), s_validation_layers.begin(), s_validation_layers.end());
  }

  if (!check_layers_support(layers))
  {
    throw EngineException("Vulkan required layers is not available");
  }

  return layers;
}

bool
GfxApplication::check_layers_support(const std::vector<const char*>& layers)
{
  unsigned int available_layer_count;
  vkEnumerateInstanceLayerProperties(&available_layer_count, nullptr);
  std::vector<VkLayerProperties> available_layers(available_layer_count);
  vkEnumerateInstanceLayerProperties(&available_layer_count, available_layers.data());

  for (const char* layerName: layers)
  {
    bool layer_found = false;

    for (const auto& properties: available_layers)
    {
      if (strcmp(layerName, properties.layerName) == 0)
      {
        layer_found = true;
        break;
      }
    }

    if (!layer_found)
    {
      return false;
    }
  }

  return true;
}

std::vector<const char*>
GfxApplication::get_instance_extensions()
{
  std::vector<const char*> extensions;

#ifdef SETSUGENE_WINDOWS
  extensions.push_back(VK_KHR_SURFACE_EXTENSION_NAME);
  extensions.push_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
#endif

  if constexpr (enable_validation_layers)
  {
    extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
  }

  if (!check_extensions_support(extensions))
  {
    throw EngineException("Vulkan required extensions is not available");
  }

  return extensions;
}

bool
GfxApplication::check_extensions_support(const std::vector<const char*>& extensions)
{
  unsigned int extensionCount;
  vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
  std::vector<VkExtensionProperties> availableExtensions(extensionCount);
  vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, availableExtensions.data());

  for (const char* extensionName: extensions)
  {
    bool extensionFound = false;

    for (const auto& extension: availableExtensions)
    {
      if (strcmp(extensionName, extension.extensionName) == 0)
      {
        std::cout << "Found extension: " << extension.extensionName << "\n";
        extensionFound = true;
        break;
      }
    }

    if (!extensionFound)
    {
      return false;
    }
  }

  return true;
}

void
GfxApplication::setup_debug_messenger()
{
  if (!enable_validation_layers)
  {
    return;
  }

  VkDebugUtilsMessengerCreateInfoEXT create_info{};
  create_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;

  create_info.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT   // Enable all warnings
                                | VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT // Enable all verbose messages
                                | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;  // Enable all error messages

  create_info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT        // Enable all general messages
                            | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT   // Enable all validation messages
                            | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT; // Enable all performance messages

  create_info.pfnUserCallback = vulkan_debug_callback;

  auto result = CreateDebugUtilsMessengerEXT(m_instance, &create_info, nullptr, &m_debug_messenger);

  if (result != VK_SUCCESS)
  {
    throw EngineException("Failed to set up debug messenger");
  }
}

void
GfxApplication::query_physical_devices()
{
  unsigned int device_count = 0;
  vkEnumeratePhysicalDevices(m_instance, &device_count, nullptr);

  if (device_count == 0)
  {
    throw EngineException("Failed to find GPUs with Vulkan support");
  }

  m_physical_devices.resize(device_count);
  vkEnumeratePhysicalDevices(m_instance, &device_count, m_physical_devices.data());

  if (m_physical_device_index < 0)
  {
    m_physical_device_index = auto_select_physical_device();
  }

  if (m_physical_device_index < 0)
  {
    throw EngineException("Failed to find a suitable GPU");
  }

  m_queue_family_indices = find_queue_families(m_physical_devices[m_physical_device_index]);
}

bool
GfxApplication::check_physical_device_extensions(VkPhysicalDevice device)
{
  unsigned int extension_count;
  vkEnumerateDeviceExtensionProperties(device, nullptr, &extension_count, nullptr);
  std::vector<VkExtensionProperties> available_extensions(extension_count);
  vkEnumerateDeviceExtensionProperties(device, nullptr, &extension_count, available_extensions.data());

  std::set<const char*> required_extensions(s_device_extensions.begin(), s_device_extensions.end());

  for (const auto& extension: available_extensions)
  {
    required_extensions.erase(extension.extensionName);
  }

  return required_extensions.empty();
}

int
GfxApplication::auto_select_physical_device()
{
  for (unsigned int i = 0; i < m_physical_devices.size(); ++i)
  {
    VkPhysicalDeviceProperties properties;
    vkGetPhysicalDeviceProperties(m_physical_devices[i], &properties);

    if (properties.deviceType != VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
    {
      continue;
    }

    auto queue_family_indices = find_queue_families(m_physical_devices[i]);

    if (!queue_family_indices.is_complete())
    {
      continue;
    }

    if (!check_physical_device_extensions(m_physical_devices[i]))
    {
      continue;
    }

    return i;
  }

  return 0;
}

VkPhysicalDevice
GfxApplication::get_physical_device() const
{
  if (m_physical_device_index < 0)
  {
    throw EngineException("No physical device selected");
  }

  return m_physical_devices[m_physical_device_index];
}

GfxApplication::QueueFamilyIndices
GfxApplication::find_queue_families(VkPhysicalDevice device) const
{
  QueueFamilyIndices indices;

  unsigned int queue_family_count = 0;
  vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, nullptr);
  std::vector<VkQueueFamilyProperties> queue_families(queue_family_count);
  vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, queue_families.data());

  // Create dummy GLFW window to get the surface
  auto         dummy_window = GlfwInstance::get_instance()->create_default_window();
  VkSurfaceKHR dummy_surface;
  glfwCreateWindowSurface(m_instance, dummy_window, nullptr, &dummy_surface);

  for (unsigned int i = 0; i < queue_family_count; ++i)
  {
    if (queue_families[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
    {
      indices.graphics_family = i;
    }

    VkBool32 present_support = false;
    vkGetPhysicalDeviceSurfaceSupportKHR(device, i, dummy_surface, &present_support);

    if (present_support)
    {
      indices.present_family = i;
    }

    if (indices.is_complete())
    {
      break;
    }
  }

  vkDestroySurfaceKHR(m_instance, dummy_surface, nullptr);
  glfwDestroyWindow(dummy_window);

  return indices;
}

void
GfxApplication::create_logical_device()
{
  std::vector<VkDeviceQueueCreateInfo> queue_create_infos;
  std::set<unsigned int>               unique_queue_families = {m_queue_family_indices.graphics_family.value(),
                                                                m_queue_family_indices.present_family.value()};

  float queue_priority = 1.0f;
  for (unsigned int queue_family: unique_queue_families)
  {
    VkDeviceQueueCreateInfo queue_create_info{};
    queue_create_info.sType            = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queue_create_info.queueFamilyIndex = queue_family;
    queue_create_info.queueCount       = 1;
    queue_create_info.pQueuePriorities = &queue_priority;
    queue_create_infos.push_back(queue_create_info);
  }

  VkPhysicalDeviceFeatures device_features{};

  VkDeviceCreateInfo create_info{};
  create_info.sType                = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  create_info.queueCreateInfoCount = static_cast<unsigned int>(queue_create_infos.size());
  create_info.pQueueCreateInfos    = queue_create_infos.data();
  create_info.pEnabledFeatures     = &device_features;

  std::vector<const char*> device_extensions(s_device_extensions.begin(), s_device_extensions.end());
  create_info.enabledExtensionCount   = static_cast<unsigned int>(device_extensions.size());
  create_info.ppEnabledExtensionNames = device_extensions.data();

  if constexpr (enable_validation_layers)
  {
    create_info.enabledLayerCount   = static_cast<unsigned int>(s_validation_layers.size());
    create_info.ppEnabledLayerNames = s_validation_layers.data();
  }
  else
  {
    create_info.enabledLayerCount = 0;
  }

  auto selected_device = m_physical_devices[m_physical_device_index];
  auto result          = vkCreateDevice(selected_device, &create_info, nullptr, &m_logical_device);

  if (result != VK_SUCCESS)
  {
    throw EngineException("Failed to create logical device");
  }

  auto graphics_queue_index = m_queue_family_indices.graphics_family.value();
  vkGetDeviceQueue(m_logical_device, graphics_queue_index, 0, &m_graphics_queue);

  if (unique_queue_families.size() > 1)
  {
    auto present_queue_index = m_queue_family_indices.present_family.value();
    vkGetDeviceQueue(m_logical_device, present_queue_index, 0, &m_present_queue);
  }
  else
  {
    m_present_queue = m_graphics_queue;
  }
}

GfxApplication*
GfxApplication::get_current()
{
  return s_current_app;
}

std::unique_ptr<GfxApplication>
GfxApplication::create()
{
  return std::make_unique<GfxApplication>();
}

unsigned int
GfxApplication::find_memory_type(unsigned int type_filter, VkMemoryPropertyFlags properties) const
{
  VkPhysicalDeviceMemoryProperties memory_properties;
  vkGetPhysicalDeviceMemoryProperties(get_physical_device(), &memory_properties);

  for (unsigned int i = 0; i < memory_properties.memoryTypeCount; ++i)
  {
    if ((type_filter & (1 << i)) && (memory_properties.memoryTypes[i].propertyFlags & properties) == properties)
    {
      return i;
    }
  }

  throw EngineException("Failed to find suitable memory type");
}

void
GfxApplication::execute_one_time_commands(VkQueue queue, const std::vector<GfxCommandBuffer*>& commands)
{
  std::vector<VkCommandBuffer> command_buffers;
  for (const auto& command: commands)
  {
    command_buffers.push_back(command->get_handler());
  }

  VkSubmitInfo submit_info{};
  submit_info.sType              = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  submit_info.commandBufferCount = static_cast<unsigned int>(command_buffers.size());
  submit_info.pCommandBuffers    = command_buffers.data();

  vkQueueSubmit(queue, 1, &submit_info, VK_NULL_HANDLE);
  vkQueueWaitIdle(queue);
}

} // namespace setsugen
