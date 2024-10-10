#include <setsugen/conf.h>

namespace setsugen
{

ConfigurationLoader::
ConfigurationLoader()
    : m_defaults{}, m_overrides{}, m_sources{}
{}

ConfigurationLoader&
ConfigurationLoader::set_default(String key, SerializedData value)
{
  m_defaults.emplace_back(std::move(key), std::move(value));
  return *this;
}

ConfigurationLoader&
ConfigurationLoader::set_override(String key, SerializedData value)
{
  m_overrides.emplace_back(std::move(key), std::move(value));
  return *this;
}

Configuration
ConfigurationLoader::load()
{
  Configuration config{};
  for (const auto& [key, value]: m_defaults)
  {
    *config.dive_insert(key) = value;
  }

  for (const auto& source: m_sources)
  {
    try
    {
      auto data = source->load();
      config.merge(data);
    }
    catch (const ConfigurationSourceException& e)
    {
      if (source->is_required())
      {
        throw ConfigurationException("Required configuration source failed: {}", {e.what()});
      }
    }
  }

  for (const auto& [key, value]: m_overrides)
  {
    *config.dive(key) = value;
  }

  return config;
}
} // namespace setsugen
