#pragma once

#include <setsugen/pch.h>

#include "../conf/conf_decl.inl"
#include "../context/app_context.inl"
#include "../gfx/gfx_fwd.inl"
#include "../states/state_app-state.inl"
#include "../states/state_loop.inl"
#include "../states/state_renderer.inl"
#include "../wm/wm_fwd.inl"

namespace setsugen
{

class Application
{
public:
  Application();

  virtual ~Application();

  Observer<StateLoop<ApplicationState>> main_loop() const;
  Observer<StateLoop<RendererState>>    render_loop() const;
  Observer<Configuration>               config() const;
  Observer<AppContext>                  context() const;
  Observer<RenderContext>               renderer_context() const;
  Observer<WindowManager>               window_manager() const;
  Observer<Window>                      main_window() const;

  Void set_main_window(Owner<Window> window);
  Void set_renderer(Owner<Renderer> renderer);
  Void set_window_manager(Owner<WindowManager> window_manager);
  Void set_config(Owner<Configuration> config);

  static Observer<Application> current_app();
  static String                get_assets_path();
  static String                get_root_path();

private:
  static Atomic<Observer<Application>> s_current_app;

  friend class ApplicationState;
  friend class ApplicationState::Initialize;
  friend class ApplicationState::Start;
  friend class ApplicationState::Ready;
  friend class ApplicationState::Resume;
  friend class ApplicationState::FrameBegin;
  friend class ApplicationState::WaitRenderer;
  friend class ApplicationState::FrameEnd;
  friend class ApplicationState::SignalHandle;
  friend class ApplicationState::Pause;
  friend class ApplicationState::Stop;
  friend class ApplicationState::Destroy;

  Owner<Configuration>               m_config;
  Owner<AppContext>                  m_context;
  Owner<ApplicationState>            m_state_machine;
  Owner<StateLoop<ApplicationState>> m_main_loop;
  Owner<RenderContext>               m_renderer_context;
  Owner<RendererState>               m_renderer_state;
  Owner<StateLoop<RendererState>>    m_renderer_loop;
  Owner<WindowManager>               m_window_manager;
  Owner<Window>                      m_main_window;
  Owner<Thread>                      m_renderer_thread;
};

} // namespace setsugen
