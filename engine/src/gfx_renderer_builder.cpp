#include <utility>

#include "gfx_renderer.h"

namespace setsugen
{
UniquePtr<RendererBuilder>
RendererBuilder::create()
{
  return std::make_unique<RendererBuilder>();
}

Observer<RendererBuilder>
RendererBuilder::with_vertex_shader(const String& file_path)
{
  m_config.vertex_shader = file_path;
  return this;
}

Observer<RendererBuilder>
RendererBuilder::with_fragment_shader(const String& file_path)
{
  m_config.fragment_shader = file_path;
  return this;
}

Observer<RendererBuilder>
RendererBuilder::with_render_target(Observer<RenderTarget> render_target)
{
  m_config.render_target = std::move(render_target);
  return this;
}

Observer<RendererBuilder>
RendererBuilder::with_topology(Topology topology)
{
  m_config.topology = topology;
  return this;
}

Observer<RendererBuilder>
RendererBuilder::add_vertex_binding(const VertexBindingDescription& vertex_binding)
{
  m_config.vertex_bindings.push_back(vertex_binding);
  return this;
}

Observer<RendererBuilder>
RendererBuilder::add_vertex_attribute(const VertexAttributeDescription& vertex_attribute)
{
  m_config.vertex_attributes.push_back(vertex_attribute);
  return this;
}

Observer<RendererBuilder>
RendererBuilder::set_vertex_bindings(DArray<VertexBindingDescription> vertex_bindings)
{
  m_config.vertex_bindings = std::move(vertex_bindings);
  return this;
}

Observer<RendererBuilder>
RendererBuilder::set_vertex_attributes(DArray<VertexAttributeDescription> vertex_attributes)
{
  m_config.vertex_attributes = std::move(vertex_attributes);
  return this;
}

Observer<RendererBuilder>
RendererBuilder::add_viewport(const ViewPort& viewport)
{
  m_config.viewports.push_back(viewport);
  return this;
}

Observer<RendererBuilder>
RendererBuilder::add_scissor(const Scissor& scissor)
{
  m_config.scissors.push_back(scissor);
  return this;
}

Observer<RendererBuilder>
RendererBuilder::set_viewports(DArray<ViewPort> viewports)
{
  m_config.viewports = std::move(viewports);
  return this;
}

Observer<RendererBuilder>
RendererBuilder::set_scissors(DArray<Scissor> scissors)
{
  m_config.scissors = std::move(scissors);
  return this;
}

Observer<RendererBuilder>
RendererBuilder::add_color_blend(const ColorBlend& color_blend)
{
  m_config.color_blends.push_back(color_blend);
  return this;
}

Observer<RendererBuilder>
RendererBuilder::set_color_blends(DArray<ColorBlend> color_blends)
{
  m_config.color_blends = std::move(color_blends);
  return this;
}

Observer<RendererBuilder>
RendererBuilder::set_cull_mode(CullMode cull_mode)
{
  m_config.cull_mode = cull_mode;
  return this;
}

Observer<RendererBuilder>
RendererBuilder::set_front_face(FrontFace front_face)
{
  m_config.front_face = front_face;
  return this;
}

Observer<RendererBuilder>
RendererBuilder::set_polygon_mode(PolygonMode polygon_mode)
{
  m_config.polygon_mode = polygon_mode;
  return this;
}

Observer<RendererBuilder>
RendererBuilder::with_clear_color(const Color4F& clear_color)
{
  m_config.clear_color = clear_color;
  return this;
}

SharedPtr<Renderer>
RendererBuilder::build()
{
  switch (m_config.render_target->type())
  {
    case RenderTargetType::Window:
    {
      return std::dynamic_pointer_cast<Renderer>(std::make_shared<VulkanWindowRenderer>(m_config));
    }
    default:
    {
      throw EngineException("Unsupported render target type");
    }
  }
}
} // namespace setsugen
