#include <setsugen/conf.h>

namespace setsugen
{

SerializedConfigurationSource::
SerializedConfigurationSource(const SerializedData& data, Bool required)
    : ConfigurationSource(required)
{
  m_data = data;
}

SerializedData
SerializedConfigurationSource::load()
{
  return std::move(m_data);
}

} // namespace setsugen
