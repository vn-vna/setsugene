#pragma once

#include "refl_fwd.inl"

namespace setsugen
{

template<typename R>
class ReflectionBase
{
public:
  DArray<ReflectionField>& get_fields() const;
};

template<typename T>
class Reflection;

} // namespace setsugen

