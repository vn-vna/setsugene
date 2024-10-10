#include <setsugen/exception.h>
#include <setsugen/format.h>

#include <utility>

namespace setsugen
{

ArgDescription::~ArgDescription() noexcept
{}

ArgDescription::ArgDescription(const ArgDescription& other)
    : m_data{other.m_data}, m_index{other.m_index}, m_callback{other.m_callback}
{}

ArgDescription::ArgDescription(ArgDescription&& other) noexcept
    : m_data{std::exchange(other.m_data, nullptr)}, m_index{std::exchange(other.m_index, -1)},
      m_callback{std::exchange(other.m_callback, nullptr)}
{}

} // namespace setsugen
