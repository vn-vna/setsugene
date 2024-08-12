#pragma once

#include <setsugen/format.h>
#include <setsugen/pch.h>
#include <setsugen/macros.h>

#define SETSUGENE_DECLARE_EXCEPTION(ExName)                                                                            \
  class ExName : virtual public SetsugenException                                                                      \
  {                                                                                                                    \
  public:                                                                                                              \
    template<typename... Args>                                                                                         \
    explicit ExName(const std::string& message, Args&&... args)                                                        \
        : SetsugenException(message, std::forward<Args>(args)...)                                                      \
    {}                                                                                                                 \
    ~           ExName() override = default;                                                                           \
    const char* exception_name() const                                                                                 \
    {                                                                                                                  \
      return #ExName;                                                                                                  \
    }                                                                                                                  \
  }

namespace setsugen
{
struct FormatContext;


class SetsugenException : public std::runtime_error
{
public:
  template<typename... Args>
  explicit SetsugenException(const std::string& message, Args&&... args)
      : std::runtime_error(Formatter::format(message, std::forward<Args>(args)...))
  {}


  ~SetsugenException() override = default;


  virtual const char* exception_type() const
  {
    return "SetsugenException";
  }
};

SETSUGENE_DECLARE_EXCEPTION(NotImplementedException);
SETSUGENE_DECLARE_EXCEPTION(FileNotFoundException);
SETSUGENE_DECLARE_EXCEPTION(InvalidStateException);
SETSUGENE_DECLARE_EXCEPTION(InvalidFormatException);
SETSUGENE_DECLARE_EXCEPTION(InvalidSyntaxException);
SETSUGENE_DECLARE_EXCEPTION(InvalidArgumentException);
SETSUGENE_DECLARE_EXCEPTION(InvalidOperationException);
SETSUGENE_DECLARE_EXCEPTION(OutOfBoundsException);
SETSUGENE_DECLARE_EXCEPTION(OutOfMemoryException);
SETSUGENE_DECLARE_EXCEPTION(EngineException);

template<typename T>
concept ExceptionType = std::is_base_of_v<SetsugenException, T>;


template<ExceptionType Ex>
class Stringify<Ex>
{
public:
  static void stringify(const FormatContext& context, const Ex& value)
  {
    context.result << "[[ Exception: type = " << value.exception_type() << ", message = " << value.what() << " ]]";
  }
};
} // namespace setsugen
