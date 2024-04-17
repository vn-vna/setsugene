#include "application_basic-app.h"

namespace setsugen
{
BasicApplication::BasicApplication(ApplicationDescription&& app_desc) : m_description(app_desc)
{
  m_logger_factory      = std::make_unique<LoggerFactory>();
  auto console_appender = LogAppender::create_console_appender(this->m_description.logger_config.log_template);
  console_appender->set_level(LogLevel::Trace);
  m_logger_factory->add_appender(console_appender);

  m_glfw_instance = GlfwInstance::create();
  m_vulkan_app    = GfxApplication::create();
  m_scene_manager = std::make_unique<SceneManager>();

  const auto& [title, width, height] = this->m_description.window_config;
  m_window                           = Window::create(title, width, height);
}

BasicApplication::~BasicApplication() = default;

Application*
BasicApplication::run()
{
  try
  {
    m_window->show_window();
    m_window->loop();
  }
  catch (const SetsugenException& e)
  {
    std::cerr << e.what() << std::endl;
  }
  catch (...)
  {
    std::cerr << "An unknown error occurred" << std::endl;
  }

  return this;
}

Application*
BasicApplication::join()
{
  m_window->join();
  return this;
}

std::shared_ptr<Logger>
BasicApplication::create_logger(const std::string& name) const
{
  return m_logger_factory->get(name);
}

Window*
BasicApplication::get_window()
{
  return m_window.get();
}

GfxApplication*
BasicApplication::get_vulkan_app()
{
  return m_vulkan_app.get();
}

SceneManager*
BasicApplication::get_scene_manager()
{
  return m_scene_manager.get();
}
} // namespace setsugen
