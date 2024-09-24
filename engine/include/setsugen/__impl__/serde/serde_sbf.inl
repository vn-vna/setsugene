#pragma once

#include "serde_fwd.inl"

namespace setsugen
{

class Sbf
{
public:
  void serialize(std::ostream& stream, const SerializedData& data);
  void deserialize(std::istream& stream, SerializedData& data);
};

} // namespace setsugen
