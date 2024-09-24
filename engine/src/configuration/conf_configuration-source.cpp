#include <setsugen/conf.h>

namespace setsugen
{

ConfigurationSource::
ConfigurationSource(bool required)
    : m_required(required)
{}

bool
ConfigurationSource::is_required()
{
  return m_required;
}

} // namespace setsugen
