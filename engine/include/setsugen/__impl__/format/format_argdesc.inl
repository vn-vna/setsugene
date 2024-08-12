#pragma once

namespace setsugen
{

template<typename T>
ArgDescription::ArgDescription(const FmtCall& callback, T&& value): m_fmt_call{callback}
{
  using ErasedType = std::remove_cvref_t<T>;
  if constexpr (std::is_lvalue_reference_v<T>)
  {
    m_data    = reinterpret_cast<void*>(const_cast<ErasedType*>(&value));
    m_deleter = [](void*)
        {};
  }
  else
  {
    m_data    = new ErasedType{std::forward<T>(value)};
    m_deleter = [](void* data)
    {
      delete reinterpret_cast<ErasedType*>(data);
    };
  }
}

constexpr void
ArgDescription::operator()(std::stringstream& ss, const FormatPlaceholder& placeholder) const
{
  std::invoke(m_fmt_call, ss, m_data, placeholder);
}



}