#include <setsugen/serde.h>

namespace setsugen
{
DataStorage<SerializedType::String>::DataStorage(const char *value)
    : m_value{value}
{}


DataStorage<SerializedType::String>::DataStorage(const std::string &value)
    : m_value{value}
{}


DataStorage<SerializedType::String>::DataStorage(std::string &&value)
    : m_value{value}
{}


DataStorage<SerializedType::String>::DataStorage(std::string_view value)
    : m_value{value}
{}


DataStorage<SerializedType::String>::DataStorage(const DataStorage &other)
    : m_value(other.m_value)
{}


DataStorage<SerializedType::String>::DataStorage(DataStorage &&other) noexcept
    : m_value(std::move(other.m_value))
{}


DataStorage<SerializedType::String> &
DataStorage<SerializedType::String>::operator=(const DataStorage &other)
{
    m_value = other.m_value;
    return *this;
}


DataStorage<SerializedType::String> &
DataStorage<SerializedType::String>::operator=(DataStorage &&other) noexcept
{
    m_value = std::move(other.m_value);
    return *this;
}


bool
DataStorage<SerializedType::String>::operator==(const DataStorage &other) const
{
    return m_value == other.m_value;
}


bool
DataStorage<SerializedType::String>::operator!=(const DataStorage &other) const
{
    return m_value != other.m_value;
}


std::string
DataStorage<SerializedType::String>::get() const noexcept
{
    return m_value;
}
} // namespace setsugen
