#pragma once

#include <setsugen/gfx.h>
#include <setsugen/logger.h>

#include "../wrapper/vulkan_debug.h"
#include "../wrapper/vulkan_device.h"
#include "../wrapper/vulkan_instance.h"
#include "../wrapper/vulkan_physical_device.h"


namespace setsugen::gfx::vulkan
{

class VulkanRenderer : public Renderer
{
public:
  VulkanRenderer(Configuration& conf);

  virtual ~VulkanRenderer();

  Owner<RenderTarget>  create_render_target() override;
  Owner<PresentTarget> create_present_target() override;

  Instance& instance() noexcept;
  Device&   device() noexcept;


private:
  Owner<Instance>       m_instance;
  Owner<Logger>         m_logger;
  Owner<DebugMessenger> m_debug_messenger;
  Owner<Device>         m_device;
};

} // namespace setsugen::gfx::vulkan
