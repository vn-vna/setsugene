#include <setsugen/application.h>

// Setsugen headers
#include <setsugen/exception.h>

#include "application_basic-app.h"

// C++ standard libraries
#include <memory>

namespace setsugen
{
Optional<WeakPtr<Application> > Application::s_current_app{};

ApplicationBuilder::ApplicationBuilder()
  : m_description{}
{
  m_description.name                       = "Setsugen Application";
  m_description.version                    = Version{0, 1, 0};
  m_description.author                     = "Unknown";
  m_description.description                = "Setsugen Application";
  m_description.logger_config.log_template = "{time} [{level}] {tag}: {message}";
  m_description.window_config.width        = 800;
  m_description.window_config.height       = 600;
  m_description.window_config.title        = "Setsugen Application";
}

ApplicationBuilder&
ApplicationBuilder::set_name(const String& name)
{
  m_description.name = name;
  return *this;
}

ApplicationBuilder&
ApplicationBuilder::set_version(const Version& version)
{
  m_description.version = version;
  return *this;
}

ApplicationBuilder&
ApplicationBuilder::set_author(const String& author)
{
  m_description.author = author;
  return *this;
}

ApplicationBuilder&
ApplicationBuilder::set_description(const String& desc)
{
  m_description.description = desc;
  return *this;
}

ApplicationBuilder&
ApplicationBuilder::set_logger_format(const String& format)
{
  m_description.logger_config.log_template = format;
  return *this;
}

ApplicationBuilder&
ApplicationBuilder::set_window_config(Int32 width, Int32 height, const String& title)
{
  m_description.window_config.width  = width;
  m_description.window_config.height = height;
  m_description.window_config.title  = title;
  return *this;
}

SharedPtr<Application>
ApplicationBuilder::build()
{
  if (Application::s_current_app.has_value())
  {
    throw InvalidStateException("An application instance is already running");
  }
  auto app                   = std::make_shared<BasicApplication>(std::move(this->m_description));
  auto app_interface         = std::dynamic_pointer_cast<Application>(app);
  Application::s_current_app = app_interface;

  app->m_logger_factory = std::make_shared<LoggerFactory>();
  auto console_appender = LogAppender::create_console_appender(this->m_description.logger_config.log_template);
  console_appender->set_level(LogLevel::Trace);
  app->m_logger_factory->add_appender(console_appender);

  app->m_vulkan_app = VulkanApplication::create_instance();
  app->m_window     =
      Window::create(this->m_description.window_config.title, this->m_description.window_config.width,
                     this->m_description.window_config.height);

  return app_interface;
}
} // namespace setsugen
