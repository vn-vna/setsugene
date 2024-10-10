#include <utility>
#include <setsugen/serde.h>

namespace setsugen
{

DataStorage<SerializedType::Bool>::DataStorage(Bool b) : m_value(b)
{}


DataStorage<SerializedType::Bool>::DataStorage(const DataStorage &other) : m_value(other.m_value)
{}


DataStorage<SerializedType::Bool>::DataStorage(DataStorage &&other) noexcept : m_value(std::exchange(other.m_value, false))
{}


DataStorage<SerializedType::Bool> &
DataStorage<SerializedType::Bool>::operator=(Bool b)
{
  m_value = b;
  return *this;
}


DataStorage<SerializedType::Bool> &
DataStorage<SerializedType::Bool>::operator=(const DataStorage &other)
{
  m_value = other.m_value;
  return *this;
}


DataStorage<SerializedType::Bool> &
DataStorage<SerializedType::Bool>::operator=(DataStorage &&other) noexcept
{
  m_value = std::exchange(other.m_value, false);
  return *this;
}


Bool
DataStorage<SerializedType::Bool>::operator==(const DataStorage &other) const
{
  return m_value == other.m_value;
}


Bool
DataStorage<SerializedType::Bool>::operator!=(const DataStorage &other) const
{
  return !(*this == other);
}


Bool
DataStorage<SerializedType::Bool>::value() const noexcept
{
  return m_value;
}


DataStorage<SerializedType::Bool>::operator Bool() const noexcept
{
  return m_value;
}
} // namespace setsugen
