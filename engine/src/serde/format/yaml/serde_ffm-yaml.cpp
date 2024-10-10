#include "./serde_ffm-yaml.h"

namespace setsugen
{
Yaml::Yaml() noexcept
  : m_config{}
{}

Yaml::Yaml(const Configurations& config) noexcept
  : m_config{config}
{}

Void
Yaml::serialize(OutputStream& stream, const SerializedData& data) const
{}

Void
Yaml::deserialize(InputStream& stream, SerializedData& data) const
{}

}
