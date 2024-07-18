#include <memory>

#include "../../application/application_basic-app.h"
#include "gfx_renderer.h"

namespace setsugen
{
GfxWindowRenderTarget::GfxWindowRenderTarget(Window* window)
    : m_window{window}, m_vulkan_app{GfxApplication::get_current()}
{
  m_logical_device = m_vulkan_app->get_logical_device();

  create_surface();
  create_swapchain();
  create_image_views();
}

GfxWindowRenderTarget::~GfxWindowRenderTarget()
{
  for (const auto image_view: m_swapchain_image_views)
  {
    vkDestroyImageView(m_logical_device, image_view, nullptr);
  }

  vkDestroySwapchainKHR(m_logical_device, m_swapchain, nullptr);
  vkDestroySurfaceKHR(m_vulkan_app->get_instance(), m_surface, nullptr);
}

void
GfxWindowRenderTarget::resize(int width, int height)
{}

void
GfxWindowRenderTarget::present()
{}

int
GfxWindowRenderTarget::width() const
{
  int width;
  glfwGetFramebufferSize(static_cast<GLFWwindow*>(m_window->get_handler()), &width, nullptr);
  return width;
}

int
GfxWindowRenderTarget::height() const
{
  int height;
  glfwGetFramebufferSize(static_cast<GLFWwindow*>(m_window->get_handler()), nullptr, &height);
  return height;
}

RenderTargetType
GfxWindowRenderTarget::type() const
{
  return RenderTargetType::Window;
}

void
GfxWindowRenderTarget::create_surface()
{
  const auto instance       = m_vulkan_app->get_instance();
  const auto window_handler = static_cast<GLFWwindow*>(m_window->get_handler());

  VkSurfaceKHR surface;
  if (glfwCreateWindowSurface(instance, window_handler, nullptr, &surface) != VK_SUCCESS)
  {
    throw EngineException("Failed to create window surface");
  }

  m_surface = surface;
}

void
GfxWindowRenderTarget::create_swapchain()
{
  auto physical_device = m_vulkan_app->get_physical_device();

  VkSurfaceCapabilitiesKHR surface_capabilities;
  vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physical_device, m_surface, &surface_capabilities);

  unsigned int format_count;
  vkGetPhysicalDeviceSurfaceFormatsKHR(physical_device, m_surface, &format_count, nullptr);
  if (format_count == 0)
  {
    throw EngineException("No surface formats found");
  }

  std::vector<VkSurfaceFormatKHR> surface_formats(format_count);
  vkGetPhysicalDeviceSurfaceFormatsKHR(physical_device, m_surface, &format_count, surface_formats.data());

  std::optional<VkSurfaceFormatKHR> surface_format;
  for (const auto& format: surface_formats)
  {
    if (format.format == VK_FORMAT_B8G8R8A8_SRGB && format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
    {
      surface_format = format;
      break;
    }
  }

  m_surface_format = surface_format.value_or(surface_formats[0]);

  unsigned int present_mode_count;
  vkGetPhysicalDeviceSurfacePresentModesKHR(physical_device, m_surface, &present_mode_count, nullptr);
  if (present_mode_count == 0)
  {
    throw EngineException("No present modes found");
  }

  std::vector<VkPresentModeKHR> present_modes(present_mode_count);
  vkGetPhysicalDeviceSurfacePresentModesKHR(physical_device, m_surface, &present_mode_count, present_modes.data());

  std::optional<VkPresentModeKHR> present_mode;
  for (const auto& mode: present_modes)
  {
    if (mode == VK_PRESENT_MODE_MAILBOX_KHR)
    {
      present_mode = mode;
      break;
    }
  }

  m_present_mode = present_mode.value_or(VK_PRESENT_MODE_FIFO_KHR);

  VkExtent2D extent;
  if (surface_capabilities.currentExtent.width != std::numeric_limits<unsigned int>::max())
  {
    extent = surface_capabilities.currentExtent;
  }
  else
  {
    auto size     = m_window->get_size();
    extent.width  = static_cast<unsigned int>(size.width());
    extent.height = static_cast<unsigned int>(size.height());
  }

  extent.width =
      std::clamp(extent.width, surface_capabilities.minImageExtent.width, surface_capabilities.maxImageExtent.width);
  extent.height =
      std::clamp(extent.height, surface_capabilities.minImageExtent.height, surface_capabilities.maxImageExtent.height);

  m_swapchain_extent = extent;

  VkSwapchainCreateInfoKHR create_info{};
  create_info.sType            = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
  create_info.surface          = m_surface;
  create_info.minImageCount    = surface_capabilities.minImageCount + 1;
  create_info.imageFormat      = m_surface_format.format;
  create_info.imageColorSpace  = m_surface_format.colorSpace;
  create_info.imageExtent      = extent;
  create_info.imageArrayLayers = 1;
  create_info.imageUsage       = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

  auto         indices                = m_vulkan_app->get_queue_family_indices();
  unsigned int queue_family_indices[] = {indices.graphics_family.value(), indices.present_family.value()};
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
  if (vkCreateSwapchainKHR(m_vulkan_app->get_logical_device(), &create_info, nullptr, &swapchain) != VK_SUCCESS)
  {
    throw EngineException("Failed to create swapchain");
  }

  m_swapchain = swapchain;

  unsigned int image_count;
  vkGetSwapchainImagesKHR(m_vulkan_app->get_logical_device(), m_swapchain, &image_count, nullptr);
  std::vector<VkImage> images(image_count);
  vkGetSwapchainImagesKHR(m_vulkan_app->get_logical_device(), m_swapchain, &image_count, images.data());

  m_swapchain_images = std::move(images);
}

void
GfxWindowRenderTarget::create_image_views()
{
  std::vector<VkImageView> image_views(m_swapchain_images.size());

  for (unsigned int i = 0; i < m_swapchain_images.size(); ++i)
  {
    VkImageViewCreateInfo create_info{};
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

    const auto result = vkCreateImageView(m_logical_device, &create_info, nullptr, &image_views[i]);
    if (result != VK_SUCCESS)
    {
      throw EngineException("Failed to create image views");
    }
  }

  m_swapchain_image_views = std::move(image_views);
}

VkSurfaceKHR
GfxWindowRenderTarget::get_surface() const
{
  return m_surface;
}

VkSwapchainKHR
GfxWindowRenderTarget::get_swapchain() const
{
  return m_swapchain;
}

VkExtent2D
GfxWindowRenderTarget::get_swapchain_extent() const
{
  return m_swapchain_extent;
}

VkFormat
GfxWindowRenderTarget::get_surface_format() const
{
  return m_surface_format.format;
}

VkImage
GfxWindowRenderTarget::get_next_image()
{
  unsigned int image_index;
  vkAcquireNextImageKHR(m_logical_device, m_swapchain, std::numeric_limits<unsigned long>::max(), VK_NULL_HANDLE,
                        VK_NULL_HANDLE, &image_index);

  return m_swapchain_images[image_index];
}

std::unique_ptr<RenderTarget>
RenderTarget::create_window_target(Window* window)
{
  return std::make_unique<GfxWindowRenderTarget>(window);
}

} // namespace setsugen
