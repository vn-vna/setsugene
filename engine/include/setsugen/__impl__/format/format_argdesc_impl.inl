#pragma once

#include "format_argdesc.inl"

namespace setsugen
{
template<typename T>
ArgDescription::ArgDescription(const T& value) : ArgDescription(-1, value)
{}

template<typename T>
ArgDescription::ArgDescription(const FormatIndex& index, const T& value) : m_callback(get_callback<T>())
{
  m_data  = &value;
  m_index = index;
}

constexpr Void
ArgDescription::operator()(StringStream& ss, const FormatPlaceholder& placeholder) const
{
  std::invoke(m_callback, ss, m_data, placeholder);
}

template<typename T>
constexpr auto
ArgDescription::get_callback() const
{
  return [](StringStream& ss, const Void* data, const FormatPlaceholder& placeholder)
  { Stringify<T>::stringify({ss, placeholder}, *static_cast<const T*>(data)); };
}

} // namespace setsugen
