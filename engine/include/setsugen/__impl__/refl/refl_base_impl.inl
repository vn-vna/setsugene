#pragma once

#include "refl_base_decl.inl"

namespace setsugen
{

template<typename ReflectionClass>
std::vector<ReflectionField>&
ReflectionBase<ReflectionClass>::get_fields() const
{
  static auto fields = Lazy<std::vector<ReflectionField>>{[] { return ReflectionClass::register_fields(); }};

  return *fields.get();
}

} // namespace setsugen
