#include <setsugen/logger.h>

// Dependency headers
#include <fmt/format.h>

namespace setsugen
{

Logger::Logger(LoggerSettings& settings)
    : Logger(settings, "default")
{}

Logger::Logger(LoggerSettings& settings, const String& tag)
    : m_tag(tag),
      m_settings(settings)
{}

Void Logger::push_log(LogLevel level, const String& message, const FormatArgsStore& args)
{
  LogData data;

  data.level   = level;
  data.message = Formatter(message).format(args);
  data.tag     = this->m_tag;

  for (auto& appender : m_settings.appender_mapping)
  {
    appender->append(data);
  }
}

String Logger::to_string() const
{
  return Formatter::format("Logger[tag='{}']", m_tag);
}

}  // namespace setsugen