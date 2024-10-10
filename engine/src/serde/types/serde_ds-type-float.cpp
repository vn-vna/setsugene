#include <setsugen/serde.h>

namespace setsugen
{

DataStorage<SerializedType::Float>::DataStorage(Float64 value)
{
  m_value = value;
}

DataStorage<SerializedType::Float>::DataStorage(const DataStorage& other)
{
  m_value = other.m_value;
}

DataStorage<SerializedType::Float>::DataStorage(DataStorage&& other) noexcept
{
  m_value       = other.m_value;
  other.m_value = 0.0;
}

DataStorage<SerializedType::Float>&
DataStorage<SerializedType::Float>::operator=(Float64 value)
{
  m_value = value;
  return *this;
}

auto
DataStorage<SerializedType::Float>::operator=(const DataStorage& other) -> DataStorage<SerializedType::Float>&
{
  m_value = other.m_value;
  return *this;
}

auto
DataStorage<SerializedType::Float>::operator=(DataStorage&& other) -> DataStorage<SerializedType::Float>&
{
  m_value       = other.m_value;
  other.m_value = 0.0;
  return *this;
}

Bool
DataStorage<SerializedType::Float>::operator==(const DataStorage& other) const
{
  return m_value == other.m_value;
}

Bool
DataStorage<SerializedType::Float>::operator!=(const DataStorage& other) const
{
  return m_value != other.m_value;
}

Bool
DataStorage<SerializedType::Float>::operator<(const DataStorage& other) const
{
  return m_value < other.m_value;
}

Bool
DataStorage<SerializedType::Float>::operator>(const DataStorage& other) const
{
  return m_value > other.m_value;
}

Bool
DataStorage<SerializedType::Float>::operator<=(const DataStorage& other) const
{
  return m_value <= other.m_value;
}

Bool
DataStorage<SerializedType::Float>::operator>=(const DataStorage& other) const
{
  return m_value >= other.m_value;
}


Float64 DataStorage<SerializedType::Float>::value() const noexcept
{
  return m_value;
}


DataStorage<SerializedType::Float>::operator Bool() const noexcept
{
  return m_value != 0.0;
}

} // namespace setsugen
