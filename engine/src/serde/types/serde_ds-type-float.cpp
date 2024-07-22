#include <setsugen/serde.h>

namespace setsugen
{

DataStorage<SerializedType::Float>::DataStorage(double value)
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
DataStorage<SerializedType::Float>::operator=(double value)
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

bool
DataStorage<SerializedType::Float>::operator==(const DataStorage& other) const
{
  return m_value == other.m_value;
}

bool
DataStorage<SerializedType::Float>::operator!=(const DataStorage& other) const
{
  return m_value != other.m_value;
}

bool
DataStorage<SerializedType::Float>::operator<(const DataStorage& other) const
{
  return m_value < other.m_value;
}

bool
DataStorage<SerializedType::Float>::operator>(const DataStorage& other) const
{
  return m_value > other.m_value;
}

bool
DataStorage<SerializedType::Float>::operator<=(const DataStorage& other) const
{
  return m_value <= other.m_value;
}

bool
DataStorage<SerializedType::Float>::operator>=(const DataStorage& other) const
{
  return m_value >= other.m_value;
}


double DataStorage<SerializedType::Float>::value() const noexcept
{
  return m_value;
}


DataStorage<SerializedType::Float>::operator bool() const noexcept
{
  return m_value != 0.0;
}

} // namespace setsugen
