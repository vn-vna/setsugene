#pragma once

#include "serde_array.inl"

namespace setsugen
{

template<IterableType T>
requires ScalarType<typename T::value_type>
DataStorage<SerializedType::Array>::DataStorage(const T& data) : m_arrays()
{
  for (auto& value: data)
  {
    m_arrays.push_back(value);
  }
}

} // namespace setsugen
