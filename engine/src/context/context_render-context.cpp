#include <setsugen/application.h>
#include <setsugen/context.h>
#include <setsugen/gfx.h>

namespace setsugen
{

Atomic<Observer<RenderContext>> RenderContext::s_current = nullptr;

RenderContext::RenderContext(Application& app)
    : m_alive(true), m_application(app), m_render_begin_sem(0), m_render_complete_sem(0), m_renderer_ready_sem(0)
{
  if (s_current)
  {
    throw InvalidStateException("RenderContext already exists");
  }

  s_current = this;
}

RenderContext::~RenderContext()
{
  s_current = nullptr;
}

Bool
RenderContext::alive() const
{
  return m_alive;
}

Void
RenderContext::signal_begin_frame()
{
  m_render_begin_sem.release();
}

Void
RenderContext::signal_end_frame()
{
  m_render_complete_sem.release();
}

Void
RenderContext::signal_renderer_ready()
{
  m_renderer_ready_sem.release();
}

Void
RenderContext::wait_render_begin()
{
  m_render_begin_sem.acquire();
}

Void
RenderContext::wait_render_complete()
{
  m_render_complete_sem.acquire();
}

Void
RenderContext::wait_renderer_ready()
{
  m_renderer_ready_sem.acquire();
}

Void
RenderContext::set_renderer(Owner<Renderer> renderer)
{
  m_renderer = std::move(renderer);
}

Void
RenderContext::set_present_target(Owner<PresentTarget> present_target)
{
  m_present_target = std::move(present_target);
}

Observer<Renderer>
RenderContext::renderer() const
{
  return m_renderer.get();
}

Observer<PresentTarget>
RenderContext::present_target() const
{
  return m_present_target.get();
}

Observer<RenderContext>
RenderContext::current()
{
  return s_current;
}

} // namespace setsugen
