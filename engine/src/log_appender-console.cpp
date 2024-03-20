#include <setsugen/logger.h>

// C++ standard headers
#include <iostream>

namespace setsugen
{
ConsoleLogAppender::ConsoleLogAppender(const String& name, const String& format)
  : LogAppender(name, format)
{}

ConsoleLogAppender::~ConsoleLogAppender() = default;

Void
ConsoleLogAppender::append(const LogData& log_data)
{
  if (this->get_settings().enabled && (log_data.level >= this->get_settings().min_level))
  {
    FormatArgsStore store;
    store.set("level", log_data.level);
    store.set("message", log_data.message);
    store.set("tag", log_data.tag);

    std::cout << this->m_settings.formatter.format(store) << std::endl;
  }
}

Void
ConsoleLogAppender::flush()
{
  std::cout.flush();
}

SharedPtr<LogAppender>
LogAppender::create_console_appender(
  const String& name, const String& format
)
{
  return std::make_shared<ConsoleLogAppender>(name, format);
}
} // namespace setsugen
