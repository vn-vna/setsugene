#pragma once

#include "conf_fwd.inl"

namespace setsugen
{

class Configuration
{
public:
  Configuration();

  ~Configuration();

  Configuration get_child(const String& key) const;

  String  get_string(const String& key, Optional<String>) const;
  Int32   get_int(const String& key, Optional<Int32>) const;
  Int64   get_long(const String& key, Optional<Int64>) const;
  Float32 get_float(const String& key, Optional<Float32>) const;
  Float64 get_double(const String& key, Optional<Float64>) const;

private:
  Configuration(const SerializedData& data);

  SerializedData* dive(const String& key) const;
  SerializedData* dive_insert(const String& key) const;
  Void            merge(const SerializedData& other);
  Void            change_value(const String& key, const SerializedData& value);

  Bool m_env_patch;
  SerializedData mutable m_data;

  friend class ConfigurationLoader;
};

class ConfigurationLoader
{
public:
  ConfigurationLoader();

  template<typename Source, typename... Args>
  ConfigurationLoader& add_source(Args... args);

  ConfigurationLoader& set_default(String key, SerializedData value);
  ConfigurationLoader& set_override(String key, SerializedData value);
  ConfigurationLoader& enable_env_patch();

  Configuration load();

private:
  DArray<std::pair<String, SerializedData>> m_defaults;
  DArray<std::pair<String, SerializedData>> m_overrides;
  DArray<Owner<ConfigurationSource>>        m_sources;
};

class ConfigurationSource
{
public:
  ConfigurationSource(Bool required);

  virtual ~ConfigurationSource() = default;

  virtual SerializedData load() = 0;

  Bool is_required();

protected:
  Bool m_required;
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

  FileConfigurationSource(const String& path, Format format = Format::Auto, Bool required = true);

  SerializedData load() override;

private:
  String m_path;
  Format m_format;
};

class SerializedConfigurationSource : public ConfigurationSource
{
public:
  explicit SerializedConfigurationSource(const SerializedData& data, Bool required = true);

  SerializedData load() override;

private:
  SerializedData m_data;
};

class CliArgsConfigurationSource : public ConfigurationSource
{
public:
  CliArgsConfigurationSource(Int32 argc, char** argv);
};

class EnvConfigurationSource : public ConfigurationSource
{
public:
  EnvConfigurationSource();
};

} // namespace setsugen
