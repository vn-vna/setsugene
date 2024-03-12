#include <setsugen/logger.h>

namespace setsugen
{

LoggerFactory::LoggerFactory()
    : m_settings {}
{}

LoggerFactory::~LoggerFactory() = default;

SharedPtr<Logger> LoggerFactory::get(const String& tag)
{
  return SharedPtr<Logger>(new Logger(m_settings, tag));
}

Void LoggerFactory::add_appender(const SharedPtr<LogAppender>& appender)
{
  m_settings.appender_mapping.add_appender(appender);
}

Void LoggerFactory::remove_appender(const String& name)
{
  m_settings.appender_mapping.remove_appender(name);
}

}  // namespace setsugen