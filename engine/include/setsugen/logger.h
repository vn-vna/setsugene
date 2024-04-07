#pragma once

#include <setsugen/pch.h>

// Setsugen headers
#include <setsugen/format.h>

// C++ standard headers
#include <list>
#include <map>
#include <string>
#include <tuple>
#include <unordered_map>

namespace setsugen
{
enum class LogLevel;
struct LogData;
class LogAppender;
class LogAppenderMapping;
class Logger;
class LoggerFactory;
class ConsoleLogAppender;

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
  LogLevel    level;
  std::string message;
  std::string tag;
};

class  LogAppender
{
public:
  struct AppenderSettings
  {
    bool        enabled;
    std::string name;
    Formatter   formatter;
    LogLevel    min_level;
  };

public:
  LogAppender(const std::string& name, const std::string& format = DEFAULT_FORMAT);
  virtual ~LogAppender() = default;

public:
  const AppenderSettings& get_settings() const;

  void set_level(LogLevel level);
  void set_format(const std::string& format);
  void set_enabled(bool enabled);

public:
  virtual void append(const LogData& log_data) = 0;
  virtual void flush()                         = 0;

public:
  static std::shared_ptr<LogAppender> create_console_appender(const std::string& name,
                                                              const std::string& format = DEFAULT_FORMAT);

  static constexpr const char* DEFAULT_FORMAT = "[{level:w=6}] {tag:w=30} :: {message}";

protected:
  AppenderSettings m_settings;
};

class  LogAppenderMapping
{
public:
  using AppenderList        = std::list<std::shared_ptr<LogAppender>>;
  using AppenderLookupTable = std::unordered_map<std::string, AppenderList::iterator>;
  friend class Logger;
  friend class LoggerFactory;

private:
  LogAppenderMapping();

public:
  ~LogAppenderMapping();

public:
  void add_appender(const std::shared_ptr<LogAppender>& appender);
  void remove_appender(const std::string& name);

  inline auto begin()
  {
    return this->m_appender_order.begin();
  }

  inline auto end()
  {
    return this->m_appender_order.end();
  }

private:
  AppenderList        m_appender_order;
  AppenderLookupTable m_lookup_table;
};

class  Logger
{
public:
  struct LoggerSettings
  {
    LogAppenderMapping appender_mapping;
  };

  void stringify(const FormatContext& context) const;

  friend class LoggerFactory;

private:
  Logger(LoggerSettings& settings);
  Logger(LoggerSettings& settings, const std::string& tag);

public:
  template<typename... Args>
  inline void log(LogLevel level, const std::string& message, Args... args)
  {
    FormatArgsStore args_store;
    size_t          index = 0;
    (args_store.set(index++, std::forward<Args>(args)), ...);
    push_log(level, message, args_store);
  }

  template<typename... Args>
  inline void trace(const std::string& message, Args... args)
  {
    log(LogLevel::Trace, message, args...);
  }

  template<typename... Args>
  inline void debug(const std::string& message, Args... args)
  {
    log(LogLevel::Debug, message, args...);
  }

  template<typename... Args>
  inline void info(const std::string& message, Args... args)
  {
    log(LogLevel::Info, message, args...);
  }

  template<typename... Args>
  inline void warn(const std::string& message, Args... args)
  {
    log(LogLevel::Warn, message, args...);
  }

  template<typename... Args>
  inline void error(const std::string& message, Args... args)
  {
    log(LogLevel::Error, message, args...);
  }

  template<typename... Args>
  inline void fatal(const std::string& message, Args... args)
  {
    log(LogLevel::Fatal, message, args...);
  }

private:
  void push_log(LogLevel level, const std::string& message, const FormatArgsStore& args);

private:
  std::string     m_tag;
  LoggerSettings& m_settings;
};

class  LoggerFactory
{
public:
  LoggerFactory();
  ~LoggerFactory();

public:
  std::shared_ptr<Logger> get(const std::string& tag);

  void add_appender(const std::shared_ptr<LogAppender>& appender);
  void remove_appender(const std::string& name);

private:
  Logger::LoggerSettings m_settings;
};

class  ConsoleLogAppender : virtual public LogAppender
{
public:
  ConsoleLogAppender(const std::string& name, const std::string& format = LogAppender::DEFAULT_FORMAT);
  ~ConsoleLogAppender() override;

public:
  void append(const LogData& log_data) override;
  void flush() override;
};

template<>
class Stringify<LogLevel>
{
public:
  using ValueType = LogLevel;

  static void stringify(const FormatContext& context, const ValueType& value)
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
