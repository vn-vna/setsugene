#pragma once

#include "serde_fwd.inl"

namespace setsugen
{

class Sbf
{
public:
  Void serialize(OutputStream& stream, const SerializedData& data);
  Void deserialize(InputStream& stream, SerializedData& data);
};

} // namespace setsugen
