#pragma once

#include "serde_fwd.inl"

namespace setsugen
{

template<>
class Stringify<SerializedType>
{
public:
  static void stringify(const FormatContext& ctx, const SerializedType& value);
};

template<>
class Stringify<SerializedData>
{
public:
  static void stringify(const FormatContext& context, const SerializedData& value);
};

std::ostream& operator<<(std::ostream& os, const SerializedData& data);


}
