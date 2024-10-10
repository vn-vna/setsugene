#include "renderer_vulkan.h"
#include "window_present_target.h"

#include <setsugen/application.h>
#include <setsugen/gfx.h>
#include <setsugen/logger.h>
#include <volk.h>

namespace setsugen::gfx::vulkan
{

VulkanRenderer::VulkanRenderer(Configuration& conf) : Renderer(conf)
{
  volkInitialize();
  m_logger = LoggerFactory::default_factory().get("VulkanRenderer");
  m_logger->info("Creating Vulkan Instance");
  m_instance = Instance::Builder().build();
  m_logger->info("Vulkan instance created");

  if (m_instance->enable_validation())
  {
    m_logger->info("Creating Vulkan Debug Messenger");
    m_debug_messenger = DebugMessenger::Builder(*m_instance).build();
    m_logger->info("Vulkan Debug Messenger created");
  }

  m_logger->info("Vulkan Renderer created");

  auto& physical_devices = m_instance->physical_devices();
  for (auto& device: physical_devices)
  {
    m_logger->info("Physical Device: {}", {device->name()});
  }

  PhysicalDevice* selected_physical_device = nullptr;

  for (auto& pdevice: physical_devices)
  {
    if (pdevice->type() == PhysicalDeviceType::DiscreteGPU)
    {
      selected_physical_device = pdevice.get();
      break;
    }
  }

  if (selected_physical_device == nullptr)
  {
    throw InvalidOperationException("No discrete GPU found");
  }

  m_logger->info("Selected Physical Device: {}", {selected_physical_device->name()});

  m_logger->info("Creating Vulkan Device");
  m_device = Device::Builder(*selected_physical_device).build();
  m_logger->info("Vulkan Device created");
}

VulkanRenderer::~VulkanRenderer()
{
  m_device.reset();
  m_debug_messenger.reset();
  m_instance.reset();
  volkFinalize();
}

Owner<RenderTarget>
VulkanRenderer::create_render_target()
{
  return Owner<RenderTarget>{nullptr};
}

Owner<PresentTarget>
VulkanRenderer::create_present_target()
{
  auto app    = Application::current_app();
  auto window = app->main_window();

  return VulkanWindowPresentTarget::Builder(*this, *window).build();
}

Instance&
VulkanRenderer::instance() noexcept
{
  return *m_instance;
}

Device&
VulkanRenderer::device() noexcept
{
  return *m_device;
}

} // namespace setsugen::gfx::vulkan
