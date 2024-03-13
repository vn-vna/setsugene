#include "application_basic-app.h"

namespace setsugen
{
BasicApplication::BasicApplication(ApplicationDescription&& app_desc)
  : m_description(app_desc)
{}

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

WeakPtr<Window>
BasicApplication::get_window() const
{
  return m_window;
}

WeakPtr<VulkanApplication>
BasicApplication::get_vulkan_app()
{
  return m_vulkan_app;
}
} // namespace setsugen::impl__

namespace setsugen
{
SharedPtr<Application>
Application::current_app()
{
  return s_current_app.value().lock();
}
} // namespace setsugen
