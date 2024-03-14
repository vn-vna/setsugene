#include <utility>

#include "gfx_renderer.h"

namespace setsugen
{

RendererBuilder& RendererBuilder::with_vertex_shader(const String& file_path)
{
  m_config.vertex_shader = file_path;
  return *this;
}

RendererBuilder& RendererBuilder::with_fragment_shader(const String& file_path)
{
  m_config.fragment_shader = file_path;
  return *this;
}

RendererBuilder& RendererBuilder::with_render_target(WeakPtr<RenderTarget> render_target)
{
  m_config.render_target = std::move(render_target);
  return *this;
}

RendererBuilder& RendererBuilder::with_topology(Topology topology)
{
  m_config.topology = topology;
  return *this;
}

RendererBuilder& RendererBuilder::add_vertex_binding(UInt32 binding, UInt32 stride)
{
  m_config.vertex_bindings.push_back({binding, stride});
  return *this;
}

RendererBuilder& RendererBuilder::add_vertex_attribute(UInt32 binding, UInt32 location, UInt32 offset, VertexFormat format, VertexType type)
{
  m_config.vertex_attributes.push_back({binding, location, offset, format, type});
  return *this;
}

RendererBuilder& RendererBuilder::set_vertex_bindings(DArray<VertexBindingDescription> vertex_bindings)
{
  m_config.vertex_bindings = std::move(vertex_bindings);
  return *this;
}

RendererBuilder& RendererBuilder::set_vertex_attributes(DArray<VertexAttributeDescription> vertex_attributes)
{
  m_config.vertex_attributes = std::move(vertex_attributes);
  return *this;
}

RendererBuilder& RendererBuilder::add_viewport(Float x, Float y, Float width, Float height, Float min_depth, Float max_depth)
{
  m_config.viewports.push_back({x, y, width, height, min_depth, max_depth});
  return *this;
}

RendererBuilder& RendererBuilder::add_scissor(Float x, Float y, Float width, Float height)
{
  m_config.scissors.push_back({x, y, width, height});
  return *this;
}

RendererBuilder& RendererBuilder::set_viewports(DArray<ViewPort> viewports)
{
  m_config.viewports = std::move(viewports);
  return *this;
}

RendererBuilder& RendererBuilder::set_scissors(DArray<Scissor> scissors)
{
  m_config.scissors = std::move(scissors);
  return *this;
}

RendererBuilder& RendererBuilder::add_color_blend(Bool blend_enable, ColorFlag blend_component)
{
  m_config.color_blends.push_back({blend_enable, blend_component});
  return *this;
}

RendererBuilder& RendererBuilder::set_color_blends(DArray<ColorBlend> color_blends)
{
  m_config.color_blends = std::move(color_blends);
  return *this;
}

RendererBuilder& RendererBuilder::set_cull_mode(CullMode cull_mode)
{
  m_config.cull_mode = cull_mode;
  return *this;
}

RendererBuilder& RendererBuilder::set_front_face(FrontFace front_face)
{
  m_config.front_face = front_face;
  return *this;
}

RendererBuilder& RendererBuilder::set_polygon_mode(PolygonMode polygon_mode)
{
  m_config.polygon_mode = polygon_mode;
  return *this;
}

RendererBuilder& RendererBuilder::with_clear_color(const Color4F& clear_color)
{
  m_config.clear_color = clear_color;
  return *this;
}

RendererBuilder& RendererBuilder::with_clear_color(Float r, Float g, Float b, Float a)
{
  m_config.clear_color = {r, g, b, a};
  return *this;
}

SharedPtr<Renderer> RendererBuilder::build()
{
  switch (m_config.render_target.lock()->type())
  {
  case RenderTargetType::Window:
    return std::dynamic_pointer_cast<Renderer>(std::make_shared<VulkanWindowRenderer>(m_config));
  default:
    throw EngineException("Unsupported render target type");
  }
}

}  // namespace setsugen