#pragma once

#include "gfx_fwd.inl"

#include "../conf/conf_decl.inl"

namespace setsugen
{

class Renderer
{
public:
  Renderer(Configuration& configuration);
  virtual ~Renderer();

  Configuration& configuration() noexcept;

  static Observer<Renderer> current_renderer();

  static Owner<Renderer> create(Configuration& configuration, RendererType type);

  virtual Owner<RenderTarget>  create_render_target()  = 0;
  virtual Owner<PresentTarget> create_present_target() = 0;

private:
  static Atomic<Observer<Renderer>> s_current_renderer;

  Configuration& m_configuration;
};

} // namespace setsugen
