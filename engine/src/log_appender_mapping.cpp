#include <setsugen/logger.h>

namespace setsugen
{

LogAppenderMapping::LogAppenderMapping()  = default;
LogAppenderMapping::~LogAppenderMapping() = default;

Void LogAppenderMapping::add_appender(const SharedPtr<LogAppender>& appender)
{
  const auto& name = appender->get_settings().name;
  this->remove_appender(name);
  m_appender_order.push_back(appender);
  m_lookup_table[name] = std::next(m_appender_order.end(), -1);
}

Void LogAppenderMapping::remove_appender(const String& name)
{
  if (m_lookup_table.find(name) != m_lookup_table.end())
  {
    m_appender_order.erase(m_lookup_table[name]);
    m_lookup_table.erase(name);
  }
}

}  // namespace setsugen