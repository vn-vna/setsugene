#pragma once

#include "serde_fwd.inl"

namespace setsugen
{

template<>
class DataStorage<SerializedType::Float>
{
public:
  DataStorage(double value);
  DataStorage(const DataStorage& other);
  DataStorage(DataStorage&& other) noexcept;

  DataStorage& operator=(double value);
  DataStorage& operator=(const DataStorage& other);
  DataStorage& operator=(DataStorage&& other);

  bool operator==(const DataStorage& other) const;
  bool operator!=(const DataStorage& other) const;
  bool operator<(const DataStorage& other) const;
  bool operator>(const DataStorage& other) const;
  bool operator<=(const DataStorage& other) const;
  bool operator>=(const DataStorage& other) const;

  double value() const noexcept;
  operator bool() const noexcept;

private:
  double m_value;
};


} // namespace setsugen
