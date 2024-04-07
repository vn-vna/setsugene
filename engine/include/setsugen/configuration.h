#pragma once

// Setsugen headers
#include <setsugen/exception.h>
#include <setsugen/pch.h>

// C++ standard headers
#include <ios>
#include <string>
#include <vector>

namespace setsugen
{
class Configuration;
class ConfigurationSource;
class ConfigurationBuilder;

class  Configuration
{
public:
  Configuration();

public:
private:
  std::vector<ConfigurationSource> m_sources;
};

class ConfigurationSource
{
public:
  enum class Source
  {
    Yaml,
    Json,
    Toml,
  };

public:
  ConfigurationSource()          = default;
  virtual ~ConfigurationSource() = default;

public:
  virtual void        load(std::istream& stream)                                     = 0;
  virtual std::string get_config(const std::string& section, const std::string& key) = 0;

public:
  static ConfigurationSource from_stream(std::istream& stream);
  static ConfigurationSource from_file(const std::string& file_name);
};

class NoSectionFoundException : virtual public SetsugenException
{
public:
  explicit NoSectionFoundException(const std::string& section);
  ~NoSectionFoundException() override = default;
};

} // namespace setsugen
