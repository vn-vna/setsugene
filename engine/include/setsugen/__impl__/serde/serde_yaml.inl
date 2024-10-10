#pragma once

#include "serde_fwd.inl"

namespace setsugen
{

class Yaml
{
public:
  struct Configurations
  {};

  Yaml() noexcept;
  Yaml(const Configurations& conf) noexcept;

  Void serialize(OutputStream& stream, const SerializedData& data) const;
  Void deserialize(InputStream& stream, SerializedData& data) const;

private:
  Configurations m_config;
};


}
