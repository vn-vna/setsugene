#pragma once

#include "serde_fwd.inl"

namespace setsugen
{

template<>
class DataStorage<SerializedType::Integer>
{
public:
  DataStorage(int64_t value);
  DataStorage(const DataStorage& other);
  DataStorage(DataStorage&& other) noexcept;

  int64_t value() const noexcept;

  DataStorage& operator=(int64_t value);
  DataStorage& operator=(const DataStorage& other);
  DataStorage& operator=(DataStorage&& other) noexcept;

  Bool operator==(const DataStorage& other) const;
  Bool operator!=(const DataStorage& other) const;
  Bool operator<(const DataStorage& other) const;
  Bool operator>(const DataStorage& other) const;
  Bool operator<=(const DataStorage& other) const;
  Bool operator>=(const DataStorage& other) const;

  explicit operator Bool() const noexcept;

private:
  int64_t m_value;
};

}
