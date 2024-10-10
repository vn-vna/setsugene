#include <setsugen/logger.h>

// C++ standard headers
#include <iostream>

namespace setsugen
{
ConsoleLogAppender::ConsoleLogAppender(const String& name, const String& format) : LogAppender(name, format)
{}

ConsoleLogAppender::~ConsoleLogAppender() = default;

Void
ConsoleLogAppender::append(const LogData& log_data)
{
  if (this->get_settings().enabled && (log_data.level >= this->get_settings().min_level))
  {
    FormatArgsStore store{
        {"level", log_data.level},
        {"tag", log_data.tag},
        {"message", log_data.message},
        {"src.file", log_data.sloc.file_name()},
        {"src.line", log_data.sloc.line()},
        {"src.function", log_data.sloc.function_name()},
        {"thread.id", std::this_thread::get_id()},
    };

    std::cout << this->m_settings.formatter.format(store) << std::endl;
  }
}

Void
ConsoleLogAppender::flush()
{
  std::cout.flush();
}

Shared<LogAppender>
LogAppender::create_console_appender(const String& name, const String& format)
{
  return std::make_shared<ConsoleLogAppender>(name, format);
}
} // namespace setsugen
