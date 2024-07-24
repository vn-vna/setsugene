#include "./serde_ffm-yaml.h"

namespace setsugen
{

Yaml::Yaml() noexcept
  : m_config{}
{ }

Yaml::Yaml(const Configurations& config) noexcept
  : m_config{config}
{}

void
Yaml::serialize(std::ostream& stream, const SerializedData& data) const
{

}

void
Yaml::deserialize(std::istream& stream, SerializedData& data) const
{
  yaml_parser_t parser;
  std::memset(&parser, 0, sizeof(parser));

  yaml_parser_initialize(&parser);
}


}