#pragma once

#include "serde_fwd.inl"

namespace setsugen
{

template<>
class DataStorage<SerializedType::String>
{
public:
  DataStorage(const char* value);
  DataStorage(const String& value);
  DataStorage(String&& value);
  DataStorage(std::string_view value);
  DataStorage(const DataStorage& other);
  DataStorage(DataStorage&& other) noexcept;

  template<typename T>
    requires StringType<T>
  DataStorage& operator=(T&& value);

  DataStorage& operator=(const DataStorage& other);

  DataStorage& operator=(DataStorage&& other) noexcept;

  Bool operator==(const DataStorage& other) const;

  Bool operator!=(const DataStorage& other) const;

  String value() const noexcept;

private:
  String m_value;
};


} // namespace setsugen
