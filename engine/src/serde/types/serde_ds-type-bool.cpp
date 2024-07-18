#include <utility>
#include <setsugen/serde.h>

namespace setsugen
{
using SerializedType::Bool;


DataStorage<Bool>::DataStorage(bool b) : m_value(b)
{}


DataStorage<Bool>::DataStorage(const DataStorage &other) : m_value(other.m_value)
{}


DataStorage<Bool>::DataStorage(DataStorage &&other) noexcept : m_value(std::exchange(other.m_value, false))
{}


DataStorage<Bool> &
DataStorage<Bool>::operator=(bool b)
{
  m_value = b;
  return *this;
}


DataStorage<Bool> &
DataStorage<Bool>::operator=(const DataStorage &other)
{
  m_value = other.m_value;
  return *this;
}


DataStorage<Bool> &
DataStorage<Bool>::operator=(DataStorage &&other) noexcept
{
  m_value = std::exchange(other.m_value, false);
  return *this;
}


bool
DataStorage<Bool>::operator==(const DataStorage &other) const
{
  return m_value == other.m_value;
}


bool
DataStorage<Bool>::operator!=(const DataStorage &other) const
{
  return !(*this == other);
}


bool
DataStorage<Bool>::get() const noexcept
{
  return m_value;
}


DataStorage<Bool>::operator bool() const noexcept
{
  return m_value;
}
} // namespace setsugen
