#include <setsugen/conf.h>

namespace setsugen
{

ConfigurationSource::
ConfigurationSource(Bool required)
    : m_required(required)
{}

Bool
ConfigurationSource::is_required()
{
  return m_required;
}

} // namespace setsugen
