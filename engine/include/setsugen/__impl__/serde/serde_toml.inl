#pragma once

#include "serde_fwd.inl"

namespace setsugen
{

class Toml
{
public:
  void serialize(std::ostream& stream, const SerializedData& data);
  void deserialize(std::istream& stream, SerializedData& data);
};

}
