#pragma once

#include "serde_fwd.inl"

namespace setsugen
{

template<>
class Stringify<SerializedType>
{
public:
  static Void stringify(const FormatContext& ctx, const SerializedType& value);
};

template<>
class Stringify<SerializedData>
{
public:
  static Void stringify(const FormatContext& context, const SerializedData& value);
};

OutputStream& operator<<(OutputStream& os, const SerializedData& data);


}
