#include <setsugen/logger.h>

namespace setsugen
{

LogAppenderMapping::LogAppenderMapping()  = default;
LogAppenderMapping::~LogAppenderMapping() = default;

void
LogAppenderMapping::add_appender(const std::shared_ptr<LogAppender>& appender)
{
  const auto& name = appender->get_settings().name;
  this->remove_appender(name);
  m_appender_order.push_back(appender);
  m_lookup_table[name] = std::next(m_appender_order.end(), -1);
}

void
LogAppenderMapping::remove_appender(const std::string& name)
{
  if (m_lookup_table.find(name) != m_lookup_table.end())
  {
    m_appender_order.erase(m_lookup_table[name]);
    m_lookup_table.erase(name);
  }
}

LogAppenderMapping::AppenderListIter
LogAppenderMapping::begin()
{
  return this->m_appender_order.begin();
}

LogAppenderMapping::AppenderListIter
LogAppenderMapping::end()
{
  return this->m_appender_order.end();
}

} // namespace setsugen
