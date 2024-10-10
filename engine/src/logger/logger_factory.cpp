#include <setsugen/logger.h>

namespace setsugen
{

LoggerFactory::
LoggerFactory()
    : m_settings{}
{}

LoggerFactory::~LoggerFactory() = default;

Owner<Logger>
LoggerFactory::get(const String& tag) const
{
  return Owner<Logger>(new Logger{m_settings, tag});
}

Void
LoggerFactory::add_appender(const Shared<LogAppender>& appender)
{
  m_settings.appender_mapping.add_appender(appender);
}

Void
LoggerFactory::remove_appender(const String& name)
{
  m_settings.appender_mapping.remove_appender(name);
}

LoggerFactory&
LoggerFactory::default_factory()
{
  static Owner<LoggerFactory> factory = []()
  {
    auto f = std::make_unique<LoggerFactory>();
    f->add_appender(LogAppender::create_console_appender("console"));
    return f;
  }();

  return *factory;
}

} // namespace setsugen
