#pragma once

#include <setsugen/format.h>
#include <setsugen/pch.h>


namespace setsugen
{
struct FormatContext;

class SetsugenException : public std::runtime_error
{
public:
  template<typename... Args>
  explicit SetsugenException(const std::string& message, Args&&... args)
      : m_message(Formatter::format(message, std::forward<Args>(args)...).c_str()),
        std::runtime_error(m_message.c_str())
  {}

  ~SetsugenException() override = default;

  virtual const char* exception_type() const
  {
    return "SetsugenException";
  }

private:
  std::string m_message;
};

class NotImplementedException : public SetsugenException
{
public:
  template<typename... Args>
  explicit NotImplementedException(const std::string& message, Args&&... args)
      : SetsugenException(message, std::forward<Args>(args)...)
  {}

  ~NotImplementedException() override = default;

  const char* exception_type() const override
  {
    return "NotImplementedException";
  }
};

class InvalidStateException : public SetsugenException
{
public:
  template<typename... Args>
  explicit InvalidStateException(const std::string& message, Args&&... args)
      : SetsugenException(message, std::forward<Args>(args)...)
  {}

  ~InvalidStateException() override = default;

  const char* exception_type() const override
  {
    return "InvalidStateException";
  }
};

class InvalidFormatException : public SetsugenException
{
public:
  template<typename... Args>
  explicit InvalidFormatException(const std::string& message, Args&&... args)
      : SetsugenException(message, std::forward<Args>(args)...)
  {}

  ~InvalidFormatException() override = default;

  const char* exception_type() const override
  {
    return "InvalidFormatException";
  }
};

class InvalidArgumentException : public SetsugenException
{
public:
  template<typename... Args>
  explicit InvalidArgumentException(const std::string& message, Args&&... args)
      : SetsugenException(message, std::forward<Args>(args)...)
  {}

  ~InvalidArgumentException() override = default;

  const char* exception_type() const override
  {
    return "InvalidArgumentException";
  }
};

class InvalidOperationException : public SetsugenException
{
public:
  template<typename... Args>
  explicit InvalidOperationException(const std::string& message, Args&&... args)
      : SetsugenException(message, std::forward<Args>(args)...)
  {}

  ~InvalidOperationException() override = default;

  const char* exception_type() const override
  {
    return "InvalidOperationException";
  }
};

class EngineException : public SetsugenException
{
public:
  template<typename... Args>
  explicit EngineException(const std::string& message, Args&&... args)
      : SetsugenException(message, std::forward<Args>(args)...)
  {}

  ~EngineException() override = default;

  const char* exception_type() const override
  {
    return "EngineException";
  }
};

template<typename T>
concept ExceptionType = std::is_base_of_v<SetsugenException, T>;

template<ExceptionType Ex>
class Stringify<Ex>
{
public:
  static void stringify(const FormatContext& context, const Ex& value)
  {
    context.result << "[[ Exception: type = " << value.exception_type() << " ,message = " << value.what() << " ]]";
  }
};

} // namespace setsugen
