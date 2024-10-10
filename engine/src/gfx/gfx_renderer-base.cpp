#include <setsugen/gfx.h>

#include "vulkan/core/renderer_vulkan.h"

namespace setsugen
{

Atomic<Observer<Renderer>> Renderer::s_current_renderer = nullptr;

Renderer::Renderer(Configuration& configuration) : m_configuration(configuration)
{
  if (s_current_renderer)
  {
    throw InvalidArgumentException("Renderer already exists");
  }

  s_current_renderer = this;
}

Renderer::~Renderer()
{
  s_current_renderer = nullptr;
}

Configuration&
Renderer::configuration() noexcept
{
  return m_configuration;
}

Observer<Renderer>
Renderer::current_renderer()
{
  return s_current_renderer;
}

Owner<Renderer>
Renderer::create(Configuration& configuration, RendererType type)
{
  switch (type)
  {
    case RendererType::Vulkan: return std::make_unique<gfx::vulkan::VulkanRenderer>(configuration);
    default: throw InvalidArgumentException("Invalid RendererType");
  }
}

} // namespace setsugen
