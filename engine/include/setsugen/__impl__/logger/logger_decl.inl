#pragma once

#include "logger_fwd.inl"

namespace setsugen
{

enum class LogLevel
{
  Trace,
  Debug,
  Info,
  Warn,
  Error,
  Fatal,
};

struct LogData
{
  LogLevel       level;
  String         message;
  String         tag;
  SourceLocation sloc;
};

class LogAppender
{
public:
  struct AppenderSettings
  {
    Bool      enabled;
    String    name;
    Formatter formatter;
    LogLevel  min_level;
  };

  LogAppender(const String& name, const String& format = DEFAULT_FORMAT);
  virtual ~LogAppender() = default;

  const AppenderSettings& get_settings() const;

  Void set_level(LogLevel level);
  Void set_format(const String& format);
  Void set_enabled(Bool enabled);

  virtual Void append(const LogData& log_data) = 0;
  virtual Void flush()                         = 0;

  static Shared<LogAppender> create_console_appender(const String& name, const String& format = DEFAULT_FORMAT);

  static constexpr const char* DEFAULT_FORMAT = "[{level:w=6}] [Thread: {thread.id}] {tag:w=40} ->> {message}";

protected:
  AppenderSettings m_settings;
};

class LogAppenderMapping
{
public:
  using AppenderList        = List<Shared<LogAppender>>;
  using AppenderLookupTable = UnorderedMap<String, AppenderList::iterator>;
  using AppenderListIter    = AppenderList::const_iterator;
  friend class Logger;
  friend class LoggerFactory;

private:
  LogAppenderMapping();

public:
  ~LogAppenderMapping();

  Void add_appender(const Shared<LogAppender>& appender);
  Void remove_appender(const String& name);

  AppenderListIter begin() const;
  AppenderListIter end() const;

private:
  AppenderList        m_appender_order;
  AppenderLookupTable m_lookup_table;
};

class Logger
{
public:
  struct LoggerSettings
  {
    LogAppenderMapping appender_mapping;
  };

  Void stringify(const FormatContext& context) const;

  friend class LoggerFactory;

private:
  Logger(const LoggerSettings& settings);
  Logger(const LoggerSettings& settings, const String& tag);

public:
  inline Void log(LogLevel level, const String& message, Initializer<ArgDescription> args = {},
                  SourceLocation sloc = SourceLocation::current())
  {
    FormatArgsStore args_store(args);
    push_log(level, message, args_store, sloc);
  }

  inline Void trace(const String& message, Initializer<ArgDescription> args = {},
                    SourceLocation sloc = SourceLocation::current())
  {
    log(LogLevel::Trace, message, args, sloc);
  }

  inline Void debug(const String& message, Initializer<ArgDescription> args = {},
                    SourceLocation sloc = SourceLocation::current())
  {
    log(LogLevel::Debug, message, args, sloc);
  }

  inline Void info(const String& message, Initializer<ArgDescription> args = {},
                   SourceLocation sloc = SourceLocation::current())
  {
    log(LogLevel::Info, message, args, sloc);
  }

  inline Void warn(const String& message, Initializer<ArgDescription> args = {},
                   SourceLocation sloc = SourceLocation::current())
  {
    log(LogLevel::Warn, message, args, sloc);
  }

  inline Void error(const String& message, Initializer<ArgDescription> args = {},
                    SourceLocation sloc = SourceLocation::current())
  {
    log(LogLevel::Error, message, args, sloc);
  }

  inline Void fatal(const String& message, Initializer<ArgDescription> args = {},
                    SourceLocation sloc = SourceLocation::current())
  {
    log(LogLevel::Fatal, message, args, sloc);
  }

private:
  Void push_log(LogLevel level, const String& message, const FormatArgsStore& args, SourceLocation sloc);

private:
  String                m_tag;
  const LoggerSettings& m_settings;
};

class LoggerFactory
{
public:
  LoggerFactory();
  ~LoggerFactory();

  Owner<Logger> get(const String& tag) const;

  Void add_appender(const Shared<LogAppender>& appender);
  Void remove_appender(const String& name);

  static LoggerFactory& default_factory();

private:
  Logger::LoggerSettings m_settings;
};

class ConsoleLogAppender : virtual public LogAppender
{
public:
  ConsoleLogAppender(const String& name, const String& format = LogAppender::DEFAULT_FORMAT);
  ~ConsoleLogAppender() override;

public:
  Void append(const LogData& log_data) override;
  Void flush() override;
};

template<>
class Stringify<LogLevel>
{
public:
  using ValueType = LogLevel;

  static Void stringify(const FormatContext& context, const ValueType& value)
  {
    switch (value)
    {
      case LogLevel::Trace: context.result << "TRACE"; break;
      case LogLevel::Debug: context.result << "DEBUG"; break;
      case LogLevel::Info: context.result << "INFO"; break;
      case LogLevel::Warn: context.result << "WARN"; break;
      case LogLevel::Error: context.result << "ERROR"; break;
      case LogLevel::Fatal: context.result << "FATAL"; break;
    }
  }
};

} // namespace setsugen
