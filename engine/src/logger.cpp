#include <setsugen/logger.h>

namespace setsugen
{
Logger::Logger(LoggerSettings& settings) : Logger(settings, "default")
{}

Logger::Logger(LoggerSettings& settings, const std::string& tag) : m_tag(tag), m_settings(settings)
{}

void
Logger::push_log(LogLevel level, const std::string& message, const FormatArgsStore& args)
{
  LogData data;

  data.level = level;

  auto message_fmt = Formatter(message);
  data.message     = message_fmt.format(args);
  data.tag         = this->m_tag;

  for (auto& appender: m_settings.appender_mapping)
  {
    appender->append(data);
  }
}

void
Logger::stringify(const FormatContext& context) const
{}
} // namespace setsugen
