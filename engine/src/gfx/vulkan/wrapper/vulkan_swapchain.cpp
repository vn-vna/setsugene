#include "vulkan_swapchain.h"
#include "vulkan_device.h"

namespace setsugen::gfx::vulkan
{

Swapchain::Swapchain(VkSwapchainKHR swapchain, Device& device) : m_swapchain(swapchain), m_device(device)
{}

Swapchain::~Swapchain()
{
  vkDestroySwapchainKHR(m_device.handle(), m_swapchain, nullptr);
}

} // namespace setsugen::gfx::vulkan
