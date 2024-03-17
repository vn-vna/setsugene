#pragma once

#include <setsugen/math.h>
#include <setsugen/pch.h>

namespace setsugen
{
class Window;
class Renderer;
class RenderTarget;

using ColorFlag = Vec<Bool, 4, 2>;

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
  UInt32 binding = 0;
  UInt32 stride  = 0;
};

struct VertexAttributeDescription
{
  UInt32       binding  = 0;
  UInt32       location = 0;
  UInt32       offset   = 0;
  VertexFormat format   = VertexFormat::RGBA;
  VertexType   type     = VertexType::Int;
  VertexSize   size     = VertexSize::Size32;
};

struct ViewPort
{
  Float x         = 0;
  Float y         = 0;
  Float width     = 0;
  Float height    = 0;
  Float min_depth = 0;
  Float max_depth = 0;
};

struct Scissor
{
  Float x      = 0;
  Float y      = 0;
  Float width  = 0;
  Float height = 0;
};

struct ColorBlend
{
  Bool      blend_enable    = false;
  ColorFlag blend_component = {true, true, true, true};
};

struct RendererConfig
{
  Optional<String>                   vertex_shader;
  Optional<String>                   fragment_shader;
  DArray<VertexBindingDescription>   vertex_bindings;
  DArray<VertexAttributeDescription> vertex_attributes;
  DArray<ViewPort>                   viewports;
  DArray<Scissor>                    scissors;
  DArray<ColorBlend>                 color_blends;
  CullMode                           cull_mode;
  FrontFace                          front_face;
  PolygonMode                        polygon_mode;
  Topology                           topology;
  Color4F                            clear_color;
  Observer<RenderTarget>             render_target;
};

class RenderTarget
{
public:
  virtual ~RenderTarget() = default;

public:
  virtual Void resize(Int32 width, Int32 height) = 0;
  virtual Void present() = 0;

  virtual Int32 width() const = 0;
  virtual Int32 height() const = 0;

  virtual RenderTargetType type() const = 0;

public:
  static SharedPtr<RenderTarget> create_window_target(Window* window);
};

class RendererBuilder
{
public:
  RendererBuilder()  = default;
  ~RendererBuilder() = default;

  static UniquePtr<RendererBuilder> create();

  Observer<RendererBuilder> with_vertex_shader(const String& vertex_shader);
  Observer<RendererBuilder> with_fragment_shader(const String& fragment_shader);
  Observer<RendererBuilder> with_render_target(Observer<RenderTarget> render_target);
  Observer<RendererBuilder> with_topology(Topology topology);
  Observer<RendererBuilder> add_vertex_binding(const VertexBindingDescription& vertex_binding);
  Observer<RendererBuilder> add_vertex_attribute(const VertexAttributeDescription& vertex_attribute);
  Observer<RendererBuilder> set_vertex_bindings(DArray<VertexBindingDescription> vertex_bindings);
  Observer<RendererBuilder> set_vertex_attributes(DArray<VertexAttributeDescription> vertex_attributes);
  Observer<RendererBuilder> add_viewport(const ViewPort& viewport);
  Observer<RendererBuilder> add_scissor(const Scissor& scissor);
  Observer<RendererBuilder> set_viewports(DArray<ViewPort> viewports);
  Observer<RendererBuilder> set_scissors(DArray<Scissor> scissors);
  Observer<RendererBuilder> add_color_blend(const ColorBlend& color_blend);
  Observer<RendererBuilder> set_color_blends(DArray<ColorBlend> color_blends);
  Observer<RendererBuilder> set_cull_mode(CullMode cull_mode);
  Observer<RendererBuilder> set_front_face(FrontFace front_face);
  Observer<RendererBuilder> set_polygon_mode(PolygonMode polygon_mode);
  Observer<RendererBuilder> with_clear_color(const Color4F& clear_color);

  SharedPtr<Renderer> build();

private:
  RendererConfig m_config;
};

class Renderer
{
public:
  virtual ~Renderer() = default;

  virtual Void render() = 0;
  virtual Void cleanup() = 0;
};
} // namespace setsugen
