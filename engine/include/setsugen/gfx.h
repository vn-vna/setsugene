#pragma once

#include <setsugen/math.h>
#include <setsugen/pch.h>

namespace setsugen
{
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

enum class VertexElement
{
  Position,
  Normal,
  Uv,
};

enum class UniformElement
{
  Model,
  View,
  Projection,
};

enum class UniformStage
{
  Vertex,
  Fragment,
};

using VertexBufferLayout = std::vector<VertexElement>;

struct UniformBufferLayout
{
  UniformStage                stage    = UniformStage::Vertex;
  std::vector<UniformElement> elements = {};
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
  /**
   * @brief The vertex shader filename that will be used by the renderer.
   * (The vertex shader file path is relative to the assets folder `assets/shaders`)
   */
  std::optional<std::string> vertex_shader = {};

  /**
   * @brief The fragment shader filename that will be used by the renderer.
   * (The vertex fragment file path is relative to the assets folder `assets/shaders`)
   */
  std::optional<std::string> fragment_shader = {};

  /**
   * @brief The vertex buffer layouts that will be used by the renderer.
   * A renderer can have multiple vertex buffer layouts, each layout can have different vertex elements.
   * Remember each vertex buffer element can only appear once a layout.
   */
  std::vector<VertexBufferLayout> vertex_buffer_layouts = {};

  /**
   * @brief The uniform buffer layouts that will be used by the renderer.
   * A renderer can have multiple uniform buffer layouts, each layout can have different uniform elements.
   */
  std::vector<UniformBufferLayout> uniform_buffer_layouts = {};

  /**
   * @brief The viewports that will be used by the renderer.
   */
  std::vector<ViewPort> viewports = {};

  /**
   * @brief The scissors that will be used by the renderer.
   */
  std::vector<Scissor> scissors = {};

  /**
   * @brief The color blends that will be used by the renderer.
   */
  std::vector<ColorBlend> color_blends = {};

  /**
   * @brief The cull mode that will be used by the renderer.
   */
  CullMode cull_mode = CullMode::Front;

  /**
   * @brief The front face that will be used by the renderer.
   * The front face is the face of the triangle that is being drawn that is considered the front face.
   */
  FrontFace front_face = FrontFace::CounterClockwise;

  /**
   * @brief The polygon mode that will be used by the renderer.
   * The polygon mode determines how the rasterizer will fill the polygons.
   */
  PolygonMode polygon_mode = PolygonMode::Fill;

  /**
   * @brief The topology that will be used by the renderer.
   * The topology determines how the vertices will be interpreted by the renderer.
   */
  Topology topology = Topology::TriangleList;

  /**
   * @brief The clear color that will be used by the renderer.
   */
  Color4F clear_color = {0.0f, 0.0f, 0.0f, 1.0f};

  /**
   * @brief The render target that will be used by the renderer.
   */
  std::unique_ptr<RenderTarget> render_target = nullptr;
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
  static std::unique_ptr<RenderTarget> create_window_target(Window* window);
};

class RendererBuilder
{
public:
   RendererBuilder() = default;
  ~RendererBuilder() = default;

  static std::unique_ptr<RendererBuilder> create();

  RendererBuilder* with_vertex_shader(const std::string& vertex_shader);
  RendererBuilder* with_fragment_shader(const std::string& fragment_shader);
  RendererBuilder* with_render_target(std::unique_ptr<RenderTarget>&& render_target);
  RendererBuilder* with_topology(Topology topology);
  RendererBuilder* add_vertex_buffer_layout(const VertexBufferLayout& layout);
  RendererBuilder* set_vertex_buffer_layouts(std::vector<VertexBufferLayout>&& layouts);
  RendererBuilder* add_uniform_buffer_layout(const UniformBufferLayout& layout);
  RendererBuilder* set_uniform_buffer_layouts(std::vector<UniformBufferLayout>&& layouts);
  RendererBuilder* add_viewport(const ViewPort& viewport);
  RendererBuilder* set_viewports(std::vector<ViewPort>&& viewports);
  RendererBuilder* add_scissor(const Scissor& scissor);
  RendererBuilder* set_scissors(std::vector<Scissor>&& scissors);
  RendererBuilder* add_color_blend(const ColorBlend& color_blend);
  RendererBuilder* set_color_blends(std::vector<ColorBlend>&& color_blends);
  RendererBuilder* set_cull_mode(CullMode cull_mode);
  RendererBuilder* set_front_face(FrontFace front_face);
  RendererBuilder* set_polygon_mode(PolygonMode polygon_mode);
  RendererBuilder* with_clear_color(const Color4F& clear_color);

  std::unique_ptr<Renderer> build();

private:
  RendererConfig m_config;
};

class Renderer
{
public:
  virtual ~Renderer() = default;

  virtual void render()  = 0;
  virtual void cleanup() = 0;
};

} // namespace setsugen
