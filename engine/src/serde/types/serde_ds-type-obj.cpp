#include <setsugen/serde.h>
#include <setsugen/exception.h>

namespace setsugen
{
using ObjectStorage = DataStorage<SerializedType::Object>;

ObjectStorage::DataStorage() = default;

ObjectStorage::DataStorage(const ObjectStorage &other) = default;

ObjectStorage::DataStorage(ObjectStorage &&other) noexcept = default;


ObjectStorage::DataStorage(std::initializer_list<SerializedData> list)
{
  for (const auto &data: list)
  {
    if (data.get_type() != SerializedType::Array)
    {
      throw InvalidArgumentException("ObjectStorage initializer list must contain only arrays");
    }

    auto &arr = data.get_array();
    if (arr.size() != 2)
    {
      throw InvalidArgumentException("ObjectStorage initializer list arrays must have 2 elements");
    }

    if (arr[0].get_type() != SerializedType::String)
    {
      throw InvalidArgumentException("ObjectStorage initializer list array first element must be a string");
    }

    m_map[arr[0].get_string().value()] = arr[1];
  }
}


ObjectStorage &ObjectStorage::operator=(const ObjectStorage &other) = default;

ObjectStorage &ObjectStorage::operator=(ObjectStorage &&other) noexcept = default;


SerializedData &ObjectStorage::operator[](const std::string &key)
{
  return m_map[key];
}


DataStorage<SerializedType::Object>::Iter
ObjectStorage::begin()
{
  return m_map.begin();
}


DataStorage<SerializedType::Object>::Iter
ObjectStorage::end()
{
  return m_map.end();
}


DataStorage<SerializedType::Object>::CIter
ObjectStorage::begin() const
{
  return m_map.begin();
}


DataStorage<SerializedType::Object>::CIter
ObjectStorage::end() const
{
  return m_map.end();
}


const SerializedData &ObjectStorage::operator[](const std::string &key) const
{
  return m_map.at(key);
}


size_t ObjectStorage::size() const
{
  return m_map.size();
}
} // namespace setsugen
