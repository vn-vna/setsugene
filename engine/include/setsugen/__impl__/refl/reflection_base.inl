#pragma once

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
