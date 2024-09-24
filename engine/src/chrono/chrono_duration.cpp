#include <setsugen/chrono.h>

namespace setsugen
{

Duration::Duration(unsigned long long duration) : m_data(duration)
{}

Duration::~Duration() noexcept
{}

} // namespace setsugen
