#include "application_basic-app.h"

namespace setsugen
{
BasicApplication::BasicApplication(ApplicationDescription&& app_desc)
  : m_description(app_desc)
{
  m_logger_factory      = std::make_shared<LoggerFactory>();
  auto console_appender = LogAppender::create_console_appender(this->m_description.logger_config.log_template);
  console_appender->set_level(LogLevel::Trace);
  m_logger_factory->add_appender(console_appender);

  m_glfw_instance = GlfwInstance::create();
  m_vulkan_app    = VulkanApplication::create();

  const auto& [title, width, height] = this->m_description.window_config;
  m_window                           = Window::create(title, width, height);
}

BasicApplication::~BasicApplication() = default;

Void
BasicApplication::run()
{
  try
  {
    m_window->show_window();
    m_window->join();
  }
  catch (const SetsugenException& e)
  {
    std::cerr << e.what() << std::endl;
  }
  catch (...)
  {
    std::cerr << "An unknown error occurred" << std::endl;
  }
}

SharedPtr<Logger>
BasicApplication::create_logger(const String& name) const
{
  return m_logger_factory->get(name);
}

Observer<Window>
BasicApplication::get_window()
{
  return m_window.get();
}

Observer<Scene>
BasicApplication::get_current_scene()
{
  return m_scene.get();
}

Observer<VulkanApplication>
BasicApplication::get_vulkan_app()
{
  return m_vulkan_app.get();
}
} // namespace setsugen::impl__

