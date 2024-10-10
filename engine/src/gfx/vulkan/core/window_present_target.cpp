#include "window_present_target.h"
#include "renderer_vulkan.h"

#include "../wrapper/vulkan_surface.h"

namespace setsugen::gfx::vulkan
{

VulkanWindowPresentTarget::VulkanWindowPresentTarget(VulkanRenderer& renderer, Window& window)
    : m_renderer(renderer), m_window(window)
{
  m_surface = Surface::Builder(m_renderer.instance(), m_window).build();
}

VulkanWindowPresentTarget::~VulkanWindowPresentTarget()
{}

Void 
VulkanWindowPresentTarget::present()
{
}

Bool
VulkanWindowPresentTarget::is_validated()
{
  return true;
}

VulkanWindowPresentTarget::Builder::Builder(VulkanRenderer& renderer, Window& window)
    : m_renderer(dynamic_cast<VulkanRenderer&>(renderer)), m_window(window)
{}

Owner<PresentTarget>
VulkanWindowPresentTarget::Builder::build()
{
  return Owner<PresentTarget>{new VulkanWindowPresentTarget{m_renderer, m_window}};
}

} // namespace setsugen::gfx::vulkan
