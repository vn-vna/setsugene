#pragma once

#include "serde_fwd.inl"

namespace setsugen
{

template<>
class DataStorage<SerializedType::Null>
{
public:
  DataStorage();
  DataStorage(std::nullptr_t value);
  DataStorage(const DataStorage& other);
  DataStorage(DataStorage&& other);
  ~DataStorage() noexcept;

  DataStorage& operator=(const DataStorage& other);
  DataStorage& operator=(DataStorage&& other);

  bool operator==(const DataStorage& other) const;
  bool operator!=(const DataStorage& other) const;

  operator bool() const noexcept;
};

}
