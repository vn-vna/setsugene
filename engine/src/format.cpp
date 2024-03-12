// Private headers
#include "format_impl.h"

namespace setsugen
{

const FormatArgsStore FormatArgsStore::NO_ARGS;

Formatter::Formatter(const String& fmt_template)
    : m_template(fmt_template)
{}

String Formatter::format(const FormatArgsStore& args) const
{
  try
  {
    return fmt::vformat(this->m_template, *static_cast<const FmtArgStore*>(args.mp_args));
  }
  catch (std::exception& ex)
  {
    throw InvalidOperationException(Formatter::format("Failed to format string ({0})", ex.what()));
  }
}

String Formatter::to_string() const
{
  return fmt::format("Formatter[template='{}']", m_template);
}

FormatArgsStore::FormatArgsStore()
    : mp_args(new FmtArgStore())
{}

FormatArgsStore::~FormatArgsStore()
{
  auto pargs = static_cast<FmtArgStore*>(this->mp_args);
  delete pargs;
}

EXPLICIT_INSTANTIATE_SETSUGEN_FORMAT_FOR_CLS(String);
EXPLICIT_INSTANTIATE_SETSUGEN_FORMAT_FOR_CLS(SetsugenException);

EXPLICIT_INSTANTIATE_SETSUGEN_FORMAT_FOR_NONCLS(const Char*);
EXPLICIT_INSTANTIATE_SETSUGEN_FORMAT_FOR_NONCLS(Char*);
EXPLICIT_INSTANTIATE_SETSUGEN_FORMAT_FOR_NONCLS(Int64);
EXPLICIT_INSTANTIATE_SETSUGEN_FORMAT_FOR_NONCLS(Int32);
EXPLICIT_INSTANTIATE_SETSUGEN_FORMAT_FOR_NONCLS(Int16);
EXPLICIT_INSTANTIATE_SETSUGEN_FORMAT_FOR_NONCLS(Int8);
EXPLICIT_INSTANTIATE_SETSUGEN_FORMAT_FOR_NONCLS(UInt64);
EXPLICIT_INSTANTIATE_SETSUGEN_FORMAT_FOR_NONCLS(UInt32);
EXPLICIT_INSTANTIATE_SETSUGEN_FORMAT_FOR_NONCLS(UInt16);
EXPLICIT_INSTANTIATE_SETSUGEN_FORMAT_FOR_NONCLS(UInt8);
EXPLICIT_INSTANTIATE_SETSUGEN_FORMAT_FOR_NONCLS(Float);
EXPLICIT_INSTANTIATE_SETSUGEN_FORMAT_FOR_NONCLS(Double);

String level_to_string(LogLevel level)
{
  const Char* level_str;

  switch (level)
  {
  case LogLevel::Trace:
    level_str = "TRACE";
    break;

  case LogLevel::Debug:
    level_str = "DEBUG";
    break;

  case LogLevel::Info:
    level_str = "INFO";
    break;

  case LogLevel::Warn:
    level_str = "WARN";
    break;

  case LogLevel::Error:
    level_str = "ERROR";
    break;

  case LogLevel::Fatal:
    level_str = "FATAL";
    break;

  default:
    level_str = "UNKNOWN";
    break;
  }

  return {level_str};
}

template <>
FormatArgsStore& FormatArgsStore::apply_arg<LogLevel>(const String& key, LogLevel value)
{
  return this->apply_arg(key, level_to_string(value));
}

template <>
FormatArgsStore& FormatArgsStore::push_arg<LogLevel>(LogLevel value)
{
  return this->push_arg(level_to_string(value));
}

}  // namespace setsugen