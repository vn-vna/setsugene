#pragma once

// Setsugen headers
#include <setsugen/configuration.h>

// C++ Standard headers
#include <memory>

// Dependency headers
#include <yaml-cpp/yaml.h>

namespace setsugen::impl__
{

class ConfigurationSource_Yaml : virtual public ConfigurationSource
{
public:
  ConfigurationSource_Yaml();
  ~ConfigurationSource_Yaml() override = default;

public:
  void        load(std::istream& stream) override;
  std::string get_config(const std::string& section, const std::string& key) override;

private:
  std::unique_ptr<YAML::Node> mp_root;
};

} // namespace setsugen::impl__
