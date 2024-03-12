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

class NoSectionFoundException;

class Configuration
{
public:
  Configuration();

public:
private:
  DArray<ConfigurationSource> m_sources;
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
  virtual Void   load(IStream& stream)                                = 0;
  virtual String get_config(const String& section, const String& key) = 0;

public:
  static ConfigurationSource from_stream(Stream& stream);
  static ConfigurationSource from_file(const String& file_name);
};

class NoSectionFoundException : virtual public SetsugenException
{
public:
  explicit NoSectionFoundException(const String& section);
  ~NoSectionFoundException() override = default;
};

}  // namespace setsugen