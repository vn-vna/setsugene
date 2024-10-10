#pragma once

#include <setsugen/gfx.h>
#include <setsugen/logger.h>
#include <setsugen/wm.h>

namespace setsugen::gfx::vulkan
{

class VulkanRenderer;
class Surface;

class VulkanWindowPresentTarget : public PresentTarget
{
public:
  class Builder;

  friend class Builder;

  ~VulkanWindowPresentTarget() override;

  Void present() override;
  Bool is_validated() override;

private:
  VulkanWindowPresentTarget(VulkanRenderer& renderer, Window& window);

  VulkanRenderer& m_renderer;
  Window&         m_window;
  Owner<Surface>  m_surface;
};

class VulkanWindowPresentTarget::Builder
{
public:
  Builder(VulkanRenderer& renderer, Window& window);

  Owner<PresentTarget> build();

private:
  VulkanRenderer& m_renderer;
  Window&         m_window;
};

} // namespace setsugen::gfx::vulkan
