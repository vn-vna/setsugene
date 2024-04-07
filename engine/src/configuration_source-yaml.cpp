#include "configuration_source-yaml.h"

#include <memory>

namespace setsugen::impl__
{

ConfigurationSource_Yaml::ConfigurationSource_Yaml() : mp_root{}
{}

void
ConfigurationSource_Yaml::load(std::istream& stream)
{
  mp_root = std::make_unique<YAML::Node>(YAML::Load(stream));
}

std::string
ConfigurationSource_Yaml::get_config(const std::string& section, const std::string& key)
{
  auto root = *this->mp_root;

  if (!root[section])
  {
  }

  return {};
}

} // namespace setsugen::impl__
