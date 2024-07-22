#include <utility>
#include <setsugen/serde.h>

namespace setsugen
{
DataStorage<SerializedType::Integer>::DataStorage(int64_t value)
  : m_value{value}
{}


DataStorage<SerializedType::Integer>::DataStorage(const DataStorage &other)
  : m_value(other.m_value)
{}


DataStorage<SerializedType::Integer>::DataStorage(DataStorage &&other) noexcept
  : m_value(std::exchange(other.m_value, 0))
{}


int64_t DataStorage<SerializedType::Integer>::value() const noexcept
{
  return m_value;
}


DataStorage<SerializedType::Integer> &
DataStorage<SerializedType::Integer>::operator=(const DataStorage &other) = default;

DataStorage<SerializedType::Integer> &
DataStorage<SerializedType::Integer>::operator=(DataStorage &&other) noexcept = default;


DataStorage<SerializedType::Integer>::operator bool() const noexcept
{
  return m_value != 0;
}


bool
DataStorage<SerializedType::Integer>::operator==(const DataStorage &other) const
{
  return m_value == other.m_value;
}


bool
DataStorage<SerializedType::Integer>::operator!=(const DataStorage &other) const
{
  return m_value != other.m_value;
}


bool
DataStorage<SerializedType::Integer>::operator<(const DataStorage &other) const
{
  return m_value < other.m_value;
}


bool
DataStorage<SerializedType::Integer>::operator>(const DataStorage &other) const
{
  return m_value > other.m_value;
}


bool
DataStorage<SerializedType::Integer>::operator<=(const DataStorage &other) const
{
  return m_value <= other.m_value;
}


bool
DataStorage<SerializedType::Integer>::operator>=(const DataStorage &other) const
{
  return m_value >= other.m_value;
}
} // namespace setsugen
