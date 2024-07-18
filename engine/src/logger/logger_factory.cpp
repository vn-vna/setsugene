#include <setsugen/logger.h>

namespace setsugen
{

LoggerFactory::LoggerFactory() : m_settings{}
{}

LoggerFactory::~LoggerFactory() = default;

std::shared_ptr<Logger>
LoggerFactory::get(const std::string& tag)
{
  return std::shared_ptr<Logger>(new Logger(m_settings, tag));
}

void
LoggerFactory::add_appender(const std::shared_ptr<LogAppender>& appender)
{
  m_settings.appender_mapping.add_appender(appender);
}

void
LoggerFactory::remove_appender(const std::string& name)
{
  m_settings.appender_mapping.remove_appender(name);
}

} // namespace setsugen
