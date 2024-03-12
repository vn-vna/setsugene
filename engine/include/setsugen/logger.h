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
class LoggerFactoryBuilder;
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
  LogLevel level;
  String   message;
  String   tag;
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

public:
  LogAppender(const String& name, const String& format = DEFAULT_FORMAT);
  virtual ~LogAppender() = default;

public:
  const AppenderSettings& get_settings() const;

  Void set_level(LogLevel level);
  Void set_format(const String& format);
  Void set_enabled(Bool enabled);

public:
  virtual Void append(const LogData& log_data) = 0;
  virtual Void flush()                         = 0;

public:
  static SharedPtr<LogAppender> create_console_appender(
      const String& name, const String& format = LogAppender::DEFAULT_FORMAT
  );

  static constexpr const Char* DEFAULT_FORMAT = "[{level}] {{{tag}}}: {message}";

protected:
  AppenderSettings m_settings;
};

class LogAppenderMapping
{
public:
  using AppenderList        = List<SharedPtr<LogAppender>>;
  using AppenderLookupTable = UnorderedMap<String, AppenderList::iterator>;
  friend class Logger;
  friend class LoggerFactory;

private:
  LogAppenderMapping();

public:
  ~LogAppenderMapping();

public:
  Void add_appender(const SharedPtr<LogAppender>& appender);
  Void remove_appender(const String& name);

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

class Logger : virtual public Formattable
{
public:
  struct LoggerSettings
  {
    LogAppenderMapping appender_mapping;
  };

  String to_string() const override;

  friend class LoggerFactory;

private:
  Logger(LoggerSettings& settings);
  Logger(LoggerSettings& settings, const String& tag);

public:
  Logger(const Logger& other) = default;
  Logger(Logger&& other)      = default;

  Logger& operator=(const Logger& other) = default;
  Logger& operator=(Logger&& other)      = default;

public:
  template <typename... Args>
  inline Void log(LogLevel level, const String& message, Args... args)
  {
    this->push_log(level, message, FormatArgsStore(std::forward<Args>(args)...));
  }

  template <typename... Args>
  inline Void trace(const String& message, Args... args)
  {
    this->log(LogLevel::Trace, message, args...);
  }

  template <typename... Args>
  inline Void debug(const String& message, Args... args)
  {
    this->log(LogLevel::Debug, message, args...);
  }

  template <typename... Args>
  inline Void info(const String& message, Args... args)
  {
    this->log(LogLevel::Info, message, args...);
  }

  template <typename... Args>
  inline Void warn(const String& message, Args... args)
  {
    this->log(LogLevel::Warn, message, args...);
  }

  template <typename... Args>
  inline Void error(const String& message, Args... args)
  {
    this->log(LogLevel::Error, message, args...);
  }

  template <typename... Args>
  inline Void fatal(const String& message, Args... args)
  {
    this->log(LogLevel::Fatal, message, args...);
  }

private:
  Void push_log(LogLevel level, const String& message, const FormatArgsStore& args);

private:
  String          m_tag;
  LoggerSettings& m_settings;
};

class LoggerFactory
{
public:
  LoggerFactory();
  ~LoggerFactory();

public:
  SharedPtr<Logger> get(const String& tag);

  Void add_appender(const SharedPtr<LogAppender>& appender);
  Void remove_appender(const String& name);

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

}  // namespace setsugen