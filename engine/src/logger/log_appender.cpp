#include <setsugen/logger.h>

namespace setsugen
{

LogAppender::LogAppender(const String& name, const String& format)
    : m_settings{true, name, Formatter(format), LogLevel::Debug}
{}

const LogAppender::AppenderSettings&
LogAppender::get_settings() const
{
  return this->m_settings;
}

Void
LogAppender::set_level(LogLevel level)
{
  this->m_settings.min_level = level;
}

Void
LogAppender::set_format(const String& format)
{
  this->m_settings.formatter = Formatter(format);
}

Void
LogAppender::set_enabled(Bool enabled)
{
  this->m_settings.enabled = enabled;
}

} // namespace setsugen
