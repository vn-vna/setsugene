#include <setsugen/application.h>
#include <setsugen/conf.h>
#include <setsugen/context.h>
#include <setsugen/gfx.h>
#include <setsugen/logger.h>
#include <setsugen/states.h>
#include <setsugen/wm.h>

namespace setsugen
{

std::atomic<Application*> Application::s_current_app = nullptr;

Application::Application()
{
  s_current_app = this;

  // Load configurations
  ConfigurationLoader loader;
  loader // Configure the configuration loader
      .add_source<FileConfigurationSource>("assets/config/config.json", FileConfigurationSource::Format::Json)
      .set_default("renderer.app_name", "Setsugen Application")
      .set_default("renderer.app_version", "1.0.0");

  m_config = std::make_unique<Configuration>(loader.load());

  // Create context
  m_context       = std::make_unique<AppContext>(*this);
  m_state_machine = std::make_unique<ApplicationState>(*m_context);
  m_main_loop     = std::make_unique<StateLoop<ApplicationState>>(*m_state_machine);

  // Create state machine for renderer
  m_renderer_context = std::make_unique<RenderContext>(*this);
  m_renderer_state   = std::make_unique<RendererState>(*m_renderer_context);
  m_renderer_loop    = std::make_unique<StateLoop<RendererState>>(*m_renderer_state);
}

Application::~Application()
{
  s_current_app = nullptr;
}

Observer<StateLoop<ApplicationState>>
Application::main_loop() const
{
  return m_main_loop.get();
}

Observer<StateLoop<RendererState>>
Application::render_loop() const
{
  return m_renderer_loop.get();
}

Observer<Configuration>
Application::config() const
{
  return m_config.get();
}

Observer<AppContext>
Application::context() const
{
  return m_context.get();
}

Observer<RenderContext>
Application::renderer_context() const
{
  return m_renderer_context.get();
}

Observer<WindowManager>
Application::window_manager() const
{
  return m_window_manager.get();
}

Observer<Window>
Application::main_window() const
{
  return m_main_window.get();
}

Void
Application::set_main_window(Owner<Window> window)
{
  m_main_window = std::move(window);
}

Void
Application::set_renderer(Owner<Renderer> renderer)
{
  m_renderer_context->set_renderer(std::move(renderer));
}

Void
Application::set_window_manager(Owner<WindowManager> window_manager)
{
  m_window_manager = std::move(window_manager);
}

Void
Application::set_config(Owner<Configuration> config)
{
  m_config = std::move(config);
}

Application*
Application::current_app()
{
  return s_current_app;
}

String
Application::get_assets_path()
{
  return "";
}

String
Application::get_root_path()
{
  return "";
}

} // namespace setsugen
