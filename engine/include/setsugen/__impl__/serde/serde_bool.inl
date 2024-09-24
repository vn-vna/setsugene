
#pragma once

#include "serde_fwd.inl"

namespace setsugen
{

template<>
class DataStorage<SerializedType::Bool>
{
public:
  DataStorage(bool b);
  DataStorage(const DataStorage& other);
  DataStorage(DataStorage&& other) noexcept;

  DataStorage& operator=(bool b);
  DataStorage& operator=(const DataStorage& other);
  DataStorage& operator=(DataStorage&& other) noexcept;

  bool operator==(const DataStorage& other) const;
  bool operator!=(const DataStorage& other) const;

  bool value() const noexcept;

  operator bool() const noexcept;

private:
  bool m_value;
};


}
