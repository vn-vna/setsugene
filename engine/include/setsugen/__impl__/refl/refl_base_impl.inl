#pragma once

#include "refl_base_decl.inl"

namespace setsugen
{

template<typename ReflectionClass>
DArray<ReflectionField>&
ReflectionBase<ReflectionClass>::get_fields() const
{
  static auto fields = Lazy<DArray<ReflectionField>>{[] { return ReflectionClass::register_fields(); }};

  return *fields.get();
}

} // namespace setsugen
