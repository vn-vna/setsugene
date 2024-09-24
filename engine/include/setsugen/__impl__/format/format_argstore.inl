#pragma once

#include "format_decl.inl"

namespace setsugen
{
template<typename K, Formattable V>
void
FormatArgsStore::set(K index, V&& value)
{
  using ErasedType = std::remove_cvref_t<V>;
  auto arg_fn      = std::make_unique<ArgDescription>(
    [] (std::stringstream &ss, const void *data, const FormatPlaceholder &placeholder)
    {
      std::stringstream temp;

      if (placeholder.specs.contains('w'))
      {
        temp << std::setw(get_int_spec(placeholder.specs.at('w')));
      }

      if (placeholder.specs.contains('p'))
      {
        temp << std::setprecision(get_int_spec(placeholder.specs.at('p')));
      }

      Stringify<ErasedType>::stringify({temp, placeholder}, *reinterpret_cast<const ErasedType*>(data));
      ss << temp.str();
    },
    std::forward<V>(value));
  FormatIndex findex = create_index(index);
  m_args[findex]     = std::move(arg_fn);
}

template<typename T>
FormatIndex
FormatArgsStore::create_index(T&& index)
{
  if constexpr (StringType<std::remove_cvref_t<T>>)
  {
    return std::string(index);
  } else
  {
    return std::forward<T>(index);
  }
}

inline int
FormatArgsStore::get_int_spec(const std::string_view& view)
{
  char buffer[128];
  auto size = view.end() - view.begin();
  std::memcpy(buffer, view.data(), size);
  buffer[size] = '\0';
  return std::stoi(buffer);
}
}
