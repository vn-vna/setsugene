#pragma once

#include "serde_fwd.inl"

namespace setsugen
{

class Toml
{
public:
  Void serialize(OutputStream& stream, const SerializedData& data);
  Void deserialize(InputStream& stream, SerializedData& data);
};

}
