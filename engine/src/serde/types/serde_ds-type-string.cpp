#include <setsugen/serde.h>

namespace setsugen
{
DataStorage<SerializedType::String>::DataStorage(const char *value)
    : m_value{value}
{}


DataStorage<SerializedType::String>::DataStorage(const String &value)
    : m_value{value}
{}


DataStorage<SerializedType::String>::DataStorage(String &&value)
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


Bool
DataStorage<SerializedType::String>::operator==(const DataStorage &other) const
{
    return m_value == other.m_value;
}


Bool
DataStorage<SerializedType::String>::operator!=(const DataStorage &other) const
{
    return m_value != other.m_value;
}


String
DataStorage<SerializedType::String>::value() const noexcept
{
    return m_value;
}
} // namespace setsugen
