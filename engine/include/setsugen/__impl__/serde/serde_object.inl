#pragma once

#include "serde_fwd.inl"

namespace setsugen
{

template<>
class DataStorage<SerializedType::Object>
{
public:
  using Iter  = UnorderedMap<String, SerializedData>::iterator;
  using CIter = UnorderedMap<String, SerializedData>::const_iterator;

  DataStorage();
  DataStorage(const DataStorage& other);
  DataStorage(DataStorage&& other) noexcept;
  DataStorage(Initializer<SerializedData> list);

  DataStorage& operator=(const DataStorage& other);
  DataStorage& operator=(DataStorage&& other) noexcept;

  SerializedData&       operator[](const String& key);
  const SerializedData& operator[](const String& key) const;

  Bool has_key(const String& key) const;

  size_t size() const;
  Iter   begin();
  Iter   end();
  CIter  begin() const;
  CIter  end() const;

private:
  UnorderedMap<String, SerializedData> m_map;
};

} // namespace setsugen
