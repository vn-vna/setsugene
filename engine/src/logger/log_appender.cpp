#include <setsugen/logger.h>

namespace setsugen
{

LogAppender::LogAppender(const std::string& name, const std::string& format)
    : m_settings{true, name, Formatter(format), LogLevel::Debug}
{}

const LogAppender::AppenderSettings&
LogAppender::get_settings() const
{
  return this->m_settings;
}

void
LogAppender::set_level(LogLevel level)
{
  this->m_settings.min_level = level;
}

void
LogAppender::set_format(const std::string& format)
{
  this->m_settings.formatter = Formatter(format);
}

void
LogAppender::set_enabled(bool enabled)
{
  this->m_settings.enabled = enabled;
}

} // namespace setsugen
