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

  void serialize(std::ostream& stream, const SerializedData& data) const;
  void deserialize(std::istream& stream, SerializedData& data) const;

private:
  Configurations m_config;
};


}
