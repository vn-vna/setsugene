#include <setsugen/gfx.h>
#include <utility>


#include "gfx_renderer.h"

namespace setsugen
{
std::unique_ptr<RendererBuilder>
RendererBuilder::create()
{
  return std::make_unique<RendererBuilder>();
}

RendererBuilder*
RendererBuilder::with_vertex_shader(const std::string& file_path)
{
  m_config.vertex_shader = file_path;
  return this;
}

RendererBuilder*
RendererBuilder::with_fragment_shader(const std::string& file_path)
{
  m_config.fragment_shader = file_path;
  return this;
}

RendererBuilder*
RendererBuilder::with_render_target(std::unique_ptr<RenderTarget>&& render_target)
{
  m_config.render_target = std::move(render_target);
  return this;
}

RendererBuilder*
RendererBuilder::with_topology(Topology topology)
{
  m_config.topology = topology;
  return this;
}

RendererBuilder*
RendererBuilder::add_viewport(const ViewPort& viewport)
{
  m_config.viewports.push_back(viewport);
  return this;
}

RendererBuilder*
RendererBuilder::set_viewports(std::vector<ViewPort>&& viewports)
{
  m_config.viewports = std::move(viewports);
  return this;
}

RendererBuilder*
RendererBuilder::add_scissor(const Scissor& scissor)
{
  m_config.scissors.push_back(scissor);
  return this;
}

RendererBuilder*
RendererBuilder::set_scissors(std::vector<Scissor>&& scissors)
{
  m_config.scissors = std::move(scissors);
  return this;
}

RendererBuilder*
RendererBuilder::add_color_blend(const ColorBlend& color_blend)
{
  m_config.color_blends.push_back(color_blend);
  return this;
}

RendererBuilder*
RendererBuilder::set_color_blends(std::vector<ColorBlend>&& color_blends)
{
  m_config.color_blends = std::move(color_blends);
  return this;
}

RendererBuilder*
RendererBuilder::set_cull_mode(CullMode cull_mode)
{
  m_config.cull_mode = cull_mode;
  return this;
}

RendererBuilder*
RendererBuilder::set_front_face(FrontFace front_face)
{
  m_config.front_face = front_face;
  return this;
}

RendererBuilder*
RendererBuilder::set_polygon_mode(PolygonMode polygon_mode)
{
  m_config.polygon_mode = polygon_mode;
  return this;
}

RendererBuilder*
RendererBuilder::with_clear_color(const Color4F& clear_color)
{
  m_config.clear_color = clear_color;
  return this;
}

std::unique_ptr<Renderer>
RendererBuilder::build()
{
  switch (m_config.render_target->type())
  {
    case RenderTargetType::Window:
    {
      return std::unique_ptr<Renderer>(dynamic_cast<Renderer*>(new GfxVulkanRenderer(std::move(m_config))));
    }
    default:
    {
      throw EngineException("Unsupported render target type");
    }
  }
}

RendererBuilder*
RendererBuilder::add_vertex_buffer_layout(const VertexBufferLayout& layout)
{
  m_config.vertex_buffer_layouts.push_back(layout);
  return this;
}

RendererBuilder*
RendererBuilder::set_vertex_buffer_layouts(std::vector<VertexBufferLayout>&& layouts)
{
  m_config.vertex_buffer_layouts = std::move(layouts);
  return this;
}

RendererBuilder*
RendererBuilder::add_uniform_buffer_layout(const UniformBufferLayout& layout)
{
  m_config.uniform_buffer_layouts.push_back(layout);
  return this;
}

RendererBuilder*
RendererBuilder::set_uniform_buffer_layouts(std::vector<UniformBufferLayout>&& layouts)
{
  m_config.uniform_buffer_layouts = std::move(layouts);
  return this;
}

} // namespace setsugen
