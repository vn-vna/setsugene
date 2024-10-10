#include <setsugen/exception.h>

#include "vulkan_debug.h"
#include "vulkan_instance.h"

namespace setsugen::gfx::vulkan
{

DebugMessenger::DebugMessenger(Instance& instance, VkDebugUtilsMessengerEXT debug_messenger, Owner<Logger>&& logger)
    : m_debug_messenger(debug_messenger), m_instance(instance), m_logger(std::move(logger))
{}

DebugMessenger::~DebugMessenger()
{
  vkDestroyDebugUtilsMessengerEXT(m_instance.handle(), m_debug_messenger, nullptr);
}

VkDebugUtilsMessengerEXT
DebugMessenger::handle()
{
  return m_debug_messenger;
}

DebugMessenger::Builder::Builder(Instance& instance) : m_instance(instance), m_create_info()
{}

Owner<DebugMessenger>
DebugMessenger::Builder::build()
{
  Owner<Logger> logger = LoggerFactory::default_factory().get("VulkanValidation");

  m_create_info       = {};
  m_create_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;

  m_create_info.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | //
                                  VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;    //

  m_create_info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |    //
                              VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | //
                              VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT; //

  m_create_info.pfnUserCallback = debug_callback;
  m_create_info.pUserData       = logger.get();

  VkDebugUtilsMessengerEXT debug_messenger;
  VkResult                 result;
  result = vkCreateDebugUtilsMessengerEXT(m_instance.handle(), &m_create_info, nullptr, &debug_messenger);

  if (result != VK_SUCCESS)
  {
    throw InvalidOperationException("Cannot create Vulkan debug messenger due to error {}", {string_VkResult(result)});
  }

  return Owner<DebugMessenger>{new DebugMessenger{m_instance, debug_messenger, std::move(logger)}};
}

VKAPI_ATTR VkBool32 VKAPI_CALL
DebugMessenger::Builder::debug_callback(VkDebugUtilsMessageSeverityFlagBitsEXT      message_severity,
                                        VkDebugUtilsMessageTypeFlagsEXT             message_type,
                                        const VkDebugUtilsMessengerCallbackDataEXT* callback_data, void* user_data)
{
  auto logger = static_cast<Logger*>(user_data);

  switch (message_severity)
  {
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
    {
      logger->warn("Vulkan Validation >> {}", {callback_data->pMessage});
    }
    break;
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
    default:
    {
      logger->error("Vulkan Validation >> {}", {callback_data->pMessage});
    }
    break;
  }

  return VK_FALSE;
}

} // namespace setsugen::gfx::vulkan
