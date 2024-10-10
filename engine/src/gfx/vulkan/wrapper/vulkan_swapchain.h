#pragma once

#include <volk.h>

namespace setsugen::gfx::vulkan
{

class Device;

class Swapchain
{
public:
  class Builder;

  friend class Builder;

  ~Swapchain();

  VkSwapchainKHR handle() const noexcept;

private:
  Swapchain(VkSwapchainKHR swapchain, Device& device);

  Device&        m_device;
  VkSwapchainKHR m_swapchain;
};

class Swapchain::Builder
{
public:
  Builder();

  Owner<Swapchain> build();

  Builder& with_surface(VkSurfaceKHR surface);
  Builder& with_image_count(UInt32 image_count);
  Builder& with_image_format(VkFormat image_format);
  Builder& with_image_color_space(VkColorSpaceKHR image_color_space);
  Builder& with_image_extent(VkExtent2D image_extent);
  Builder& with_image_usage_flags(VkImageUsageFlags image_usage_flags);
  Builder& with_image_sharing_mode(VkSharingMode image_sharing_mode);
  Builder& with_queue_family_indices(DArray<UInt32> queue_family_indices);
  Builder& with_pre_transform(VkSurfaceTransformFlagBitsKHR pre_transform);
  Builder& with_composite_alpha(VkCompositeAlphaFlagBitsKHR composite_alpha);
  Builder& with_present_mode(VkPresentModeKHR present_mode);
  Builder& with_clipped(Bool clipped);

private:
  VkSwapchainCreateInfoKHR m_create_info;

  Optional<VkSurfaceKHR>                  m_surface;
  Optional<UInt32>                        m_image_count;
  Optional<VkFormat>                      m_image_format;
  Optional<VkColorSpaceKHR>               m_image_color_space;
  Optional<VkExtent2D>                    m_image_extent;
  Optional<VkImageUsageFlags>             m_image_usage_flags;
  Optional<VkSharingMode>                 m_image_sharing_mode;
  Optional<DArray<UInt32>>                m_queue_family_indices;
  Optional<VkSurfaceTransformFlagBitsKHR> m_pre_transform;
  Optional<VkCompositeAlphaFlagBitsKHR>   m_composite_alpha;
  Optional<VkPresentModeKHR>              m_present_mode;
  Optional<Bool>                          m_clipped;
};

} // namespace setsugen::gfx::vulkan
