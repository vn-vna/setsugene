#pragma once

#include "serde_fwd.inl"

namespace setsugen
{

template<>
class DataStorage<SerializedType::String>
{
public:
  DataStorage(const char* value);
  DataStorage(const std::string& value);
  DataStorage(std::string&& value);
  DataStorage(std::string_view value);
  DataStorage(const DataStorage& other);
  DataStorage(DataStorage&& other) noexcept;

  template<typename T>
    requires StringType<T>
  DataStorage& operator=(T&& value);

  DataStorage& operator=(const DataStorage& other);

  DataStorage& operator=(DataStorage&& other) noexcept;

  bool operator==(const DataStorage& other) const;

  bool operator!=(const DataStorage& other) const;

  std::string value() const noexcept;

private:
  std::string m_value;
};


} // namespace setsugen
