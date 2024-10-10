#pragma once

#include "serde_fwd.inl"

namespace setsugen
{

template<>
class DataStorage<SerializedType::Float>
{
public:
  DataStorage(Float64 value);
  DataStorage(const DataStorage& other);
  DataStorage(DataStorage&& other) noexcept;

  DataStorage& operator=(Float64 value);
  DataStorage& operator=(const DataStorage& other);
  DataStorage& operator=(DataStorage&& other);

  Bool operator==(const DataStorage& other) const;
  Bool operator!=(const DataStorage& other) const;
  Bool operator<(const DataStorage& other) const;
  Bool operator>(const DataStorage& other) const;
  Bool operator<=(const DataStorage& other) const;
  Bool operator>=(const DataStorage& other) const;

  Float64 value() const noexcept;
  operator Bool() const noexcept;

private:
  Float64 m_value;
};


} // namespace setsugen
