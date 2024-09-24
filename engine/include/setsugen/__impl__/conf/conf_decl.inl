#pragma once

#include "conf_fwd.inl"

namespace setsugen
{

class Configuration
{
public:
  ~Configuration();
  Configuration();

  std::string get_string(const std::string& key) const;
  int         get_int(const std::string& key) const;
  long long   get_long(const std::string& key) const;
  float       get_float(const std::string& key) const;
  double      get_double(const std::string& key) const;

private:
  SerializedData* dive(const std::string& key) const;
  SerializedData* dive_insert(const std::string& key) const;
  void            merge(const SerializedData& other);
  void            change_value(const std::string& key, const SerializedData& value);

  bool m_env_patch;
  SerializedData mutable m_data;

  friend class ConfigurationLoader;
};

class ConfigurationLoader
{
public:
  ConfigurationLoader();

  template<typename Source, typename... Args>
  ConfigurationLoader& add_source(Args... args);

  ConfigurationLoader& set_default(std::string key, SerializedData value);
  ConfigurationLoader& set_override(std::string key, SerializedData value);
  ConfigurationLoader& enable_env_patch();

  Configuration load();

private:
  std::vector<std::pair<std::string, SerializedData>> m_defaults;
  std::vector<std::pair<std::string, SerializedData>> m_overrides;
  std::vector<std::unique_ptr<ConfigurationSource>>   m_sources;
};

class ConfigurationSource
{
public:
  ConfigurationSource(bool required);

  virtual ~ConfigurationSource() = default;

  virtual SerializedData load() = 0;

  bool is_required();

protected:
  bool m_required;
};

class FileConfigurationSource : public ConfigurationSource
{
public:
  enum class Format
  {
    Auto,
    Json,
    Toml,
    Yaml,
  };

  FileConfigurationSource(const std::string& path, Format format = Format::Auto, bool required = true);

  SerializedData load() override;

private:
  std::string m_path;
  Format      m_format;
};

class SerializedConfigurationSource : public ConfigurationSource
{
public:
  explicit SerializedConfigurationSource(const SerializedData& data, bool required = true);

  SerializedData load() override;

private:
  SerializedData m_data;
};

class CliArgsConfigurationSource : public ConfigurationSource
{
public:
  CliArgsConfigurationSource(int argc, char** argv);
};

class EnvConfigurationSource : public ConfigurationSource
{
public:
  EnvConfigurationSource();
};

} // namespace setsugen
