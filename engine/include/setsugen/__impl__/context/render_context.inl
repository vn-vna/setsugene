#pragma once

#include "context_fwd.inl"

#include "../application/app_fwd.inl"
#include "../gfx/gfx_fwd.inl"

namespace setsugen
{

class RenderContext
{
public:
  RenderContext(Application& application);
  ~RenderContext();

  Bool alive() const;

  Void signal_begin_frame();
  Void signal_end_frame();
  Void signal_renderer_ready();

  Void wait_render_begin();
  Void wait_render_complete();
  Void wait_renderer_ready();

  Void set_renderer(Owner<Renderer> renderer);
  Void set_present_target(Owner<PresentTarget> present_target);

  Observer<Renderer>      renderer() const;
  Observer<PresentTarget> present_target() const;

  static Observer<RenderContext> current();

private:
  static Atomic<Observer<RenderContext>> s_current;

  Bool                 m_alive;
  Application&         m_application;
  BinarySemaphore      m_render_begin_sem;
  BinarySemaphore      m_render_complete_sem;
  BinarySemaphore      m_renderer_ready_sem;
  Owner<Renderer>      m_renderer;
  Owner<PresentTarget> m_present_target;
};

} // namespace setsugen
