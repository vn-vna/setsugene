#include <setsugen/logger.h>

namespace setsugen
{
Logger::Logger(const LoggerSettings& settings) : Logger(settings, "default")
{}

Logger::Logger(const LoggerSettings& settings, const String& tag) : m_tag(tag), m_settings(settings)
{}

Void
Logger::push_log(LogLevel level, const String& message, const FormatArgsStore& args, SourceLocation sloc)
{
  LogData data;

  data.level = level;

  auto message_fmt = Formatter(message);
  data.message     = message_fmt.format(args);
  data.tag         = this->m_tag;
  data.sloc        = sloc;

  for (const auto& appender: m_settings.appender_mapping)
  {
    appender->append(data);
  }
}

} // namespace setsugen
