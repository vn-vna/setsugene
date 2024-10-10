#pragma once

#include <setsugen/format.h>
#include <setsugen/pch.h>

#define SETSUGENE_DECLARE_EXCEPTION(ExName)                                                                            \
  class ExName : virtual public SetsugenException                                                                      \
  {                                                                                                                    \
  public:                                                                                                              \
    explicit ExName(const String& message, Initializer<ArgDescription> args = {})                       \
        : SetsugenException(#ExName, message, args)                                                                    \
    {}                                                                                                                 \
    ~ExName() override = default;                                                                                      \
  }

namespace setsugen
{

struct FormatContext;

class SetsugenException : public std::runtime_error
{
public:
  explicit SetsugenException(const String& type, const String& message,
                             Initializer<ArgDescription> args = {})
      : std::runtime_error(Formatter::format(message, args)), m_type{type}
  {}

  ~SetsugenException() override = default;

  const char* exception_type() const
  {
    return m_type.c_str();
  }

protected:
  String m_type;
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
SETSUGENE_DECLARE_EXCEPTION(PluginException);

template<typename T>
concept ExceptionType = std::is_base_of_v<SetsugenException, T>;

template<ExceptionType Ex>
class Stringify<Ex>
{
public:
  static Void stringify(const FormatContext& context, const Ex& value)
  {
    context.result << "[[ Exception: type = " << value.exception_type() << ", message = " << value.what() << " ]]";
  }
};
} // namespace setsugen
