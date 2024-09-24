#pragma once

#include "serde_fwd.inl"

namespace setsugen
{

template<>
class DataStorage<SerializedType::Array>
{
public:
  using Iter   = std::vector<SerializedData>::iterator;
  using CIter  = std::vector<SerializedData>::const_iterator;
  using RIter  = std::vector<SerializedData>::reverse_iterator;
  using CRIter = std::vector<SerializedData>::const_reverse_iterator;

  DataStorage() noexcept;
  DataStorage(const DataStorage& other) noexcept;
  DataStorage(DataStorage&& other) noexcept;
  DataStorage(std::initializer_list<SerializedData> list);

  template<IterableType T>
    requires ScalarType<typename T::value_type>
  DataStorage(const T& data);

  DataStorage& operator=(const DataStorage& other) noexcept;
  DataStorage& operator=(DataStorage&& other) noexcept;

  DataStorage& push_back(const SerializedData& data);
  DataStorage& push_back(SerializedData&& data);
  DataStorage& pop_back();
  DataStorage& clear();
  DataStorage& erase(size_t index);
  DataStorage& insert(size_t index, const SerializedData& data);
  DataStorage& insert(size_t index, SerializedData&& data);
  DataStorage& resize(size_t size);
  DataStorage& reserve(size_t size);
  DataStorage& swap(DataStorage& other) noexcept;
  DataStorage& shrink_to_fit();

  DataStorage& sort(std::function<int(const SerializedData&, const SerializedData&)> pred);

  bool   empty() const;
  size_t size() const;
  Iter   begin();
  Iter   end();
  CIter  begin() const;
  CIter  end() const;
  RIter  rbegin();
  RIter  rend();
  CRIter rbegin() const;
  CRIter rend() const;

  SerializedData&       operator[](size_t index);
  const SerializedData& operator[](size_t index) const;

  explicit operator bool() const noexcept;

private:
  std::vector<SerializedData> m_arrays;
};


} // namespace setsugen
