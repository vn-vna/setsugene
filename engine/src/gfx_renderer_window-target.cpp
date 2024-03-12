#include "application_basic-app.h"
#include "gfx_renderer.h"

namespace setsugen
{

VulkanWindowRenderTarget::VulkanWindowRenderTarget(WeakPtr<Window> window)
    : m_window {window},
      m_vulkan_app {VulkanApplication::get_current()}
{
  m_window_handler = (GLFWwindow*) m_window.lock()->get_handler();

  create_surface();
  create_swapchain();
  create_image_views();
}

VulkanWindowRenderTarget::~VulkanWindowRenderTarget()
{
  auto vulkan_app = m_vulkan_app.lock();

  for (auto image_view : m_swapchain_image_views)
  {
    vkDestroyImageView(vulkan_app->get_logical_device(), image_view, nullptr);
  }

  vkDestroySwapchainKHR(vulkan_app->get_logical_device(), m_swapchain, nullptr);
  vkDestroySurfaceKHR(vulkan_app->get_instance(), m_surface, nullptr);
}

Void VulkanWindowRenderTarget::resize(Int32 width, Int32 height)
{}

Void VulkanWindowRenderTarget::present()
{}

Int32 VulkanWindowRenderTarget::width() const
{
  Int32 width;
  glfwGetFramebufferSize((GLFWwindow*) m_window.lock()->get_handler(), &width, nullptr);
  return width;
}

Int32 VulkanWindowRenderTarget::height() const
{
  Int32 height;
  glfwGetFramebufferSize((GLFWwindow*) m_window.lock()->get_handler(), nullptr, &height);
  return height;
}

RenderTargetType VulkanWindowRenderTarget::type() const
{
  return RenderTargetType::Window;
}

Void VulkanWindowRenderTarget::create_surface()
{
  auto instance       = m_vulkan_app.lock()->get_instance();
  auto window_handler = (GLFWwindow*) m_window.lock()->get_handler();

  VkSurfaceKHR surface;
  if (glfwCreateWindowSurface(instance, window_handler, nullptr, &surface) != VK_SUCCESS)
  {
    throw EngineException("Failed to create window surface");
  }

  m_surface = surface;
}

Void VulkanWindowRenderTarget::create_swapchain()
{
  auto vulkan_app      = m_vulkan_app.lock();
  auto physical_device = vulkan_app->get_physical_device();

  VkSurfaceCapabilitiesKHR surface_capabilities;
  vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physical_device, m_surface, &surface_capabilities);

  UInt32 format_count;
  vkGetPhysicalDeviceSurfaceFormatsKHR(physical_device, m_surface, &format_count, nullptr);
  if (format_count == 0)
  {
    throw EngineException("No surface formats found");
  }

  DArray<VkSurfaceFormatKHR> surface_formats(format_count);
  vkGetPhysicalDeviceSurfaceFormatsKHR(
      physical_device, m_surface, &format_count, surface_formats.data()
  );

  Optional<VkSurfaceFormatKHR> surface_format;
  for (const auto& format : surface_formats)
  {
    if (format.format == VK_FORMAT_B8G8R8A8_SRGB &&
        format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
    {
      surface_format = format;
      break;
    }
  }

  m_surface_format = surface_format.value_or(surface_formats[0]);

  UInt32 present_mode_count;
  vkGetPhysicalDeviceSurfacePresentModesKHR(
      physical_device, m_surface, &present_mode_count, nullptr
  );
  if (present_mode_count == 0)
  {
    throw EngineException("No present modes found");
  }

  DArray<VkPresentModeKHR> present_modes(present_mode_count);
  vkGetPhysicalDeviceSurfacePresentModesKHR(
      physical_device, m_surface, &present_mode_count, present_modes.data()
  );

  Optional<VkPresentModeKHR> present_mode;
  for (const auto& mode : present_modes)
  {
    if (mode == VK_PRESENT_MODE_MAILBOX_KHR)
    {
      present_mode = mode;
      break;
    }
  }

  m_present_mode = present_mode.value_or(VK_PRESENT_MODE_FIFO_KHR);

  VkExtent2D extent;
  if (surface_capabilities.currentExtent.width != std::numeric_limits<UInt32>::max())
  {
    extent = surface_capabilities.currentExtent;
  }
  else
  {
    auto size    = m_window.lock()->get_size();
    extent.width  = static_cast<UInt32>(size.width());
    extent.height = static_cast<UInt32>(size.height());
  }

  extent.width = std::clamp(
      extent.width, surface_capabilities.minImageExtent.width,
      surface_capabilities.maxImageExtent.width
  );
  extent.height = std::clamp(
      extent.height, surface_capabilities.minImageExtent.height,
      surface_capabilities.maxImageExtent.height
  );

  VkSwapchainCreateInfoKHR create_info {};
  create_info.sType            = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
  create_info.surface          = m_surface;
  create_info.minImageCount    = surface_capabilities.minImageCount + 1;
  create_info.imageFormat      = m_surface_format.format;
  create_info.imageColorSpace  = m_surface_format.colorSpace;
  create_info.imageExtent      = extent;
  create_info.imageArrayLayers = 1;
  create_info.imageUsage       = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

  auto   indices                = vulkan_app->get_queue_family_indices();
  UInt32 queue_family_indices[] = {indices.graphics_family.value(), indices.present_family.value()};
  if (indices.graphics_family != indices.present_family)
  {
    create_info.imageSharingMode      = VK_SHARING_MODE_CONCURRENT;
    create_info.queueFamilyIndexCount = 2;
    create_info.pQueueFamilyIndices   = queue_family_indices;
  }
  else
  {
    create_info.imageSharingMode      = VK_SHARING_MODE_EXCLUSIVE;
    create_info.queueFamilyIndexCount = 0;
    create_info.pQueueFamilyIndices   = nullptr;
  }

  create_info.preTransform   = surface_capabilities.currentTransform;
  create_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
  create_info.presentMode    = m_present_mode;
  create_info.clipped        = VK_TRUE;
  create_info.oldSwapchain   = VK_NULL_HANDLE;

  VkSwapchainKHR swapchain;
  if (vkCreateSwapchainKHR(vulkan_app->get_logical_device(), &create_info, nullptr, &swapchain) !=
      VK_SUCCESS)
  {
    throw EngineException("Failed to create swapchain");
  }

  m_swapchain = swapchain;

  UInt32 image_count;
  vkGetSwapchainImagesKHR(vulkan_app->get_logical_device(), m_swapchain, &image_count, nullptr);
  DArray<VkImage> images(image_count);
  vkGetSwapchainImagesKHR(
      vulkan_app->get_logical_device(), m_swapchain, &image_count, images.data()
  );

  m_swapchain_images = std::move(images);
}

Void VulkanWindowRenderTarget::create_image_views()
{
  DArray<VkImageView> image_views(m_swapchain_images.size());

  for (UInt32 i = 0; i < m_swapchain_images.size(); ++i)
  {
    VkImageViewCreateInfo create_info {};
    create_info.sType                           = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    create_info.image                           = m_swapchain_images[i];
    create_info.viewType                        = VK_IMAGE_VIEW_TYPE_2D;
    create_info.format                          = m_surface_format.format;
    create_info.components.r                    = VK_COMPONENT_SWIZZLE_IDENTITY;
    create_info.components.g                    = VK_COMPONENT_SWIZZLE_IDENTITY;
    create_info.components.b                    = VK_COMPONENT_SWIZZLE_IDENTITY;
    create_info.components.a                    = VK_COMPONENT_SWIZZLE_IDENTITY;
    create_info.subresourceRange.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT;
    create_info.subresourceRange.baseMipLevel   = 0;
    create_info.subresourceRange.levelCount     = 1;
    create_info.subresourceRange.baseArrayLayer = 0;
    create_info.subresourceRange.layerCount     = 1;

    VkImageView image_view;
    auto        physical_device = m_vulkan_app.lock()->get_logical_device();
    auto        result = vkCreateImageView(physical_device, &create_info, nullptr, &image_view);
    if (result != VK_SUCCESS)
    {
      throw EngineException("Failed to create image views");
    }

    image_views.push_back(image_view);
  }

  m_swapchain_image_views = std::move(image_views);
}

SharedPtr<RenderTarget> RenderTarget::create_window_target(WeakPtr<Window> window)
{
  return std::make_shared<VulkanWindowRenderTarget>(window);
}

}  // namespace setsugen