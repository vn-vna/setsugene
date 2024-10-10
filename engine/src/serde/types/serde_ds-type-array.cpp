#include <setsugen/serde.h>

namespace setsugen
{
using ArrayStorage = DataStorage<SerializedType::Array>;

ArrayStorage::DataStorage() noexcept = default;


ArrayStorage::DataStorage(const DataStorage &other) noexcept : m_arrays(other.m_arrays)
{}


ArrayStorage::DataStorage(DataStorage &&other) noexcept : m_arrays(std::move(other.m_arrays))
{}


ArrayStorage::DataStorage(Initializer<SerializedData> list) : m_arrays(list)
{}


ArrayStorage &ArrayStorage::operator=(const DataStorage &other) noexcept = default;

ArrayStorage &ArrayStorage::operator=(DataStorage &&other) noexcept = default;


ArrayStorage &
ArrayStorage::push_back(const SerializedData &data)
{
  m_arrays.push_back(data);
  return *this;
}


ArrayStorage &
ArrayStorage::push_back(SerializedData &&data)
{
  m_arrays.push_back(std::move(data));
  return *this;
}


ArrayStorage &
ArrayStorage::pop_back()
{
  m_arrays.pop_back();
  return *this;
}


ArrayStorage &
ArrayStorage::clear()
{
  m_arrays.clear();
  return *this;
}


ArrayStorage &
ArrayStorage::erase(size_t index)
{
  m_arrays.erase(m_arrays.begin() + index);
  return *this;
}


ArrayStorage &
ArrayStorage::insert(size_t index, const SerializedData &data)
{
  m_arrays.insert(m_arrays.begin() + index, data);
  return *this;
}


ArrayStorage &
ArrayStorage::insert(size_t index, SerializedData &&data)
{
  m_arrays.insert(m_arrays.begin() + index, std::move(data));
  return *this;
}


ArrayStorage &
ArrayStorage::resize(size_t size)
{
  m_arrays.resize(size);
  return *this;
}


ArrayStorage &
ArrayStorage::reserve(size_t size)
{
  m_arrays.reserve(size);
  return *this;
}


ArrayStorage &
ArrayStorage::swap(DataStorage &other) noexcept
{
  m_arrays.swap(other.m_arrays);
  return *this;
}


ArrayStorage &
ArrayStorage::shrink_to_fit()
{
  m_arrays.shrink_to_fit();
  return *this;
}


ArrayStorage &
ArrayStorage::sort(std::function<Int32(const SerializedData &, const SerializedData &)> pred)
{
  std::sort(m_arrays.begin(), m_arrays.end(), pred);
  return *this;
}


Bool
ArrayStorage::empty() const
{
  return m_arrays.empty();
}


size_t
ArrayStorage::size() const
{
  return m_arrays.size();
}


ArrayStorage::operator Bool() const noexcept
{
  return !m_arrays.empty();
}


ArrayStorage::Iter
ArrayStorage::begin()
{
  return m_arrays.begin();
}


ArrayStorage::Iter
ArrayStorage::end()
{
  return m_arrays.end();
}


ArrayStorage::CIter
ArrayStorage::begin() const
{
  return m_arrays.begin();
}


ArrayStorage::CIter
ArrayStorage::end() const
{
  return m_arrays.end();
}


ArrayStorage::RIter
ArrayStorage::rbegin()
{
  return m_arrays.rbegin();
}


ArrayStorage::RIter
ArrayStorage::rend()
{
  return m_arrays.rend();
}


ArrayStorage::CRIter
ArrayStorage::rbegin() const
{
  return m_arrays.rbegin();
}


ArrayStorage::CRIter
ArrayStorage::rend() const
{
  return m_arrays.rend();
}


SerializedData &
ArrayStorage::operator[](size_t index)
{
  return m_arrays[index];
}


const SerializedData &
ArrayStorage::operator[](size_t index) const
{
  return m_arrays[index];
}
} // namespace setsugen
