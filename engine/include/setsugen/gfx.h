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
  WeakPtr<RenderTarget>              render_target;
};

class RenderTarget
{
public:
  virtual ~RenderTarget() = default;

public:
  virtual Void resize(Int32 width, Int32 height) = 0;
  virtual Void present()                         = 0;

  virtual Int32 width() const  = 0;
  virtual Int32 height() const = 0;

  virtual RenderTargetType type() const = 0;

public:
  static SharedPtr<RenderTarget> create_window_target(WeakPtr<Window> window);
};

class RendererBuilder
{
public:
  RendererBuilder()  = default;
  ~RendererBuilder() = default;

public:
  RendererBuilder& with_vertex_shader(const String& vertex_shader);
  RendererBuilder& with_fragment_shader(const String& fragment_shader);
  RendererBuilder& with_render_target(WeakPtr<RenderTarget> render_target);
  RendererBuilder& with_topology(Topology topology);
  RendererBuilder& add_vertex_binding(UInt32 binding, UInt32 stride);
  RendererBuilder& add_vertex_attribute(UInt32 binding, UInt32 location, UInt32 offset, VertexFormat format, VertexType type);
  RendererBuilder& set_vertex_bindings(DArray<VertexBindingDescription> vertex_bindings);
  RendererBuilder& set_vertex_attributes(DArray<VertexAttributeDescription> vertex_attributes);
  RendererBuilder& add_viewport(Float x, Float y, Float width, Float height, Float min_depth, Float max_depth);
  RendererBuilder& add_scissor(Float x, Float y, Float width, Float height);
  RendererBuilder& set_viewports(DArray<ViewPort> viewports);
  RendererBuilder& set_scissors(DArray<Scissor> scissors);
  RendererBuilder& add_color_blend(Bool blend_enable, ColorFlag blend_component);
  RendererBuilder& set_color_blends(DArray<ColorBlend> color_blends);
  RendererBuilder& set_cull_mode(CullMode cull_mode);
  RendererBuilder& set_front_face(FrontFace front_face);
  RendererBuilder& set_polygon_mode(PolygonMode polygon_mode);

public:
  SharedPtr<Renderer> build();

private:
  RendererConfig m_config;
};

class Renderer
{
public:
  virtual ~Renderer() = default;

public:
  virtual Void render() = 0;
};

}  // namespace setsugen