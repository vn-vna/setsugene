
#pragma once

#include "serde_fwd.inl"

namespace setsugen
{

template<>
class DataStorage<SerializedType::Bool>
{
public:
  DataStorage(Bool b);
  DataStorage(const DataStorage& other);
  DataStorage(DataStorage&& other) noexcept;

  DataStorage& operator=(Bool b);
  DataStorage& operator=(const DataStorage& other);
  DataStorage& operator=(DataStorage&& other) noexcept;

  Bool operator==(const DataStorage& other) const;
  Bool operator!=(const DataStorage& other) const;

  Bool value() const noexcept;

  operator Bool() const noexcept;

private:
  Bool m_value;
};


}
