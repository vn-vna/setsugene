#include <setsugen/logger.h>
#include <volk.h>
#include <vulkan/vk_enum_string_helper.h>

namespace setsugen::gfx::vulkan
{

class Instance;

class DebugMessenger
{
public:
  class Builder;
  friend class Builder;

  ~DebugMessenger();

  VkDebugUtilsMessengerEXT handle();

private:
  DebugMessenger(Instance& instance, VkDebugUtilsMessengerEXT debug_messenger, Owner<Logger>&& logger);

  VkDebugUtilsMessengerEXT m_debug_messenger;
  Instance&                m_instance;
  Owner<Logger>            m_logger;
};

class DebugMessenger::Builder
{
public:
  Builder(Instance& instance);

  Owner<DebugMessenger> build();

private:
  static VKAPI_ATTR VkBool32 VKAPI_CALL debug_callback(VkDebugUtilsMessageSeverityFlagBitsEXT      message_severity,
                                                       VkDebugUtilsMessageTypeFlagsEXT             message_type,
                                                       const VkDebugUtilsMessengerCallbackDataEXT* callback_data,
                                                       void*                                       user_data);

  VkDebugUtilsMessengerCreateInfoEXT m_create_info;
  Instance&                          m_instance;
};

} // namespace setsugen::gfx::vulkan
