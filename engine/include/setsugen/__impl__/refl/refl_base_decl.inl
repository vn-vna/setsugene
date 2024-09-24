#pragma once

#include "refl_fwd.inl"

namespace setsugen
{

template<typename R>
class ReflectionBase
{
public:
  std::vector<ReflectionField>& get_fields() const;
};

template<typename T>
class Reflection;

} // namespace setsugen

