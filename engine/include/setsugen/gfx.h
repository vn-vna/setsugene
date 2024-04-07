#pragma once

#include <setsugen/math.h>
#include <setsugen/pch.h>

namespace setsugen
{
struct RenderContext;
class Window;
class Renderer;
class RenderTarget;
class Scene;

using ColorFlag = Vec<bool, 4, VectorUsage::Color>;

enum class RenderTargetType
{
  Window,
  Offscreen,
};

enum class Topology
{
  PointList,
  LineList,
  LineStrip,
  TriangleList,
  TriangleStrip,
};

enum class CullMode
{
  None,
  Front,
  Back,
};

enum class FrontFace
{
  Clockwise,
  CounterClockwise,
};

enum class PolygonMode
{
  Fill,
  Line,
  Point,
};

enum class VertexFormat
{
  R,
  RG,
  RGB,
  RGBA,
};

enum class VertexType
{
  Float,
  Int,
  UInt,
};

enum class VertexSize
{
  Size8,
  Size16,
  Size32,
  Size64,
};

struct VertexBindingDescription
{
  unsigned int binding = 0;
  unsigned int stride  = 0;
};

struct VertexAttributeDescription
{
  unsigned int binding  = 0;
  unsigned int location = 0;
  unsigned int offset   = 0;
  VertexFormat format   = VertexFormat::RGBA;
  VertexType   type     = VertexType::Int;
  VertexSize   size     = VertexSize::Size32;
};

struct ViewPort
{
  float x         = 0;
  float y         = 0;
  float width     = 0;
  float height    = 0;
  float min_depth = 0;
  float max_depth = 0;
};

struct Scissor
{
  float x      = 0;
  float y      = 0;
  float width  = 0;
  float height = 0;
};

struct ColorBlend
{
  bool      blend_enable    = false;
  ColorFlag blend_component = {true, true, true, true};
};

struct RendererConfig
{
  std::optional<std::string>              vertex_shader;
  std::optional<std::string>              fragment_shader;
  std::vector<VertexBindingDescription>   vertex_bindings;
  std::vector<VertexAttributeDescription> vertex_attributes;
  std::vector<ViewPort>                   viewports;
  std::vector<Scissor>                    scissors;
  std::vector<ColorBlend>                 color_blends;
  CullMode                                cull_mode;
  FrontFace                               front_face;
  PolygonMode                             polygon_mode;
  Topology                                topology;
  Color4F                                 clear_color;
  RenderTarget*                           render_target;
};

struct RenderContext
{
  Renderer* renderer;
};


class RenderTarget
{
public:
  virtual ~RenderTarget() = default;

public:
  virtual void resize(int width, int height) = 0;
  virtual void present()                     = 0;

  virtual int width() const  = 0;
  virtual int height() const = 0;

  virtual RenderTargetType type() const = 0;

public:
  static  std::shared_ptr<RenderTarget> create_window_target(Window* window);
};

class  RendererBuilder
{
public:
  RendererBuilder()  = default;
  ~RendererBuilder() = default;

  static std::unique_ptr<RendererBuilder> create();

  RendererBuilder* with_vertex_shader(const std::string& vertex_shader);
  RendererBuilder* with_fragment_shader(const std::string& fragment_shader);
  RendererBuilder* with_render_target(RenderTarget* render_target);
  RendererBuilder* with_topology(Topology topology);
  RendererBuilder* add_vertex_binding(const VertexBindingDescription& vertex_binding);
  RendererBuilder* add_vertex_attribute(const VertexAttributeDescription& vertex_attribute);
  RendererBuilder* set_vertex_bindings(std::vector<VertexBindingDescription> vertex_bindings);
  RendererBuilder* set_vertex_attributes(std::vector<VertexAttributeDescription> vertex_attributes);
  RendererBuilder* add_viewport(const ViewPort& viewport);
  RendererBuilder* add_scissor(const Scissor& scissor);
  RendererBuilder* set_viewports(std::vector<ViewPort> viewports);
  RendererBuilder* set_scissors(std::vector<Scissor> scissors);
  RendererBuilder* add_color_blend(const ColorBlend& color_blend);
  RendererBuilder* set_color_blends(std::vector<ColorBlend> color_blends);
  RendererBuilder* set_cull_mode(CullMode cull_mode);
  RendererBuilder* set_front_face(FrontFace front_face);
  RendererBuilder* set_polygon_mode(PolygonMode polygon_mode);
  RendererBuilder* with_clear_color(const Color4F& clear_color);

  std::shared_ptr<Renderer> build();

private:
  RendererConfig m_config;
};

class Renderer
{
public:
  virtual ~Renderer() = default;

  virtual void render(Scene*) = 0;
  virtual void cleanup()      = 0;
};
} // namespace setsugen
