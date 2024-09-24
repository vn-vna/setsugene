#pragma once

#include "serde_fwd.inl"

namespace setsugen
{

template<>
class DataStorage<SerializedType::Object>
{
public:
  using Iter  = std::unordered_map<std::string, SerializedData>::iterator;
  using CIter = std::unordered_map<std::string, SerializedData>::const_iterator;

  DataStorage();
  DataStorage(const DataStorage& other);
  DataStorage(DataStorage&& other) noexcept;
  DataStorage(std::initializer_list<SerializedData> list);

  DataStorage& operator=(const DataStorage& other);
  DataStorage& operator=(DataStorage&& other) noexcept;

  SerializedData&       operator[](const std::string& key);
  const SerializedData& operator[](const std::string& key) const;

  bool has_key(const std::string& key) const;

  size_t size() const;
  Iter   begin();
  Iter   end();
  CIter  begin() const;
  CIter  end() const;

private:
  std::unordered_map<std::string, SerializedData> m_map;
};

} // namespace setsugen
