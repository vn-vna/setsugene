#include <setsugen/conf.h>

namespace setsugen
{

FileConfigurationSource::FileConfigurationSource(const std::string& path, Format format, bool required)
    : ConfigurationSource(required), m_path(path), m_format(format)
{
  if (m_format == Format::Auto)
  {
    auto ext = m_path.substr(m_path.find_last_of('.') + 1);
    if (ext == "json")
    {
      m_format = Format::Json;
    }
    else if (ext == "toml")
    {
      m_format = Format::Toml;
    }
    else if (ext == "yaml")
    {
      m_format = Format::Yaml;
    }
    else
    {
      throw InvalidFormatException("Cannot determine format of file '{}'", m_path);
    }
  }
}

SerializedData
FileConfigurationSource::load()
{
  SerializedData data;
  std::ifstream  file(m_path);

  if (!file.good())
  {
    throw FileNotFoundException("Cannot open configuration file {}", m_path);
  }

  switch (m_format)
  {
    case Format::Json:
    {
      auto conf = Json::Configurations{.deserializer_config = {.allow_c_comments = true, .allow_yaml_comments = false}};
      data.parse(file, Json{conf});
    }
    break;

    default:
    {
      throw InvalidFormatException("Configuration Source type provided is not supported");
    }
  }

  return data;
}

} // namespace setsugen
