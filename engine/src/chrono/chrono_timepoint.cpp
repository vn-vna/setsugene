#include <setsugen/chrono.h>

#include <chrono>

namespace setsugen
{

inline uint64_t
__now_std()
{
  return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch())
      .count();
}

TimePoint::TimePoint() : m_data(__now_std())
{}

TimePoint::TimePoint(uint64_t timepoint) : m_data(timepoint)
{}

TimePoint::~TimePoint() noexcept
{}

TimePoint
TimePoint::operator+(const Duration& dur) const
{
  return TimePoint{m_data + dur.m_data};
}

TimePoint
TimePoint::operator-(const Duration& dur) const
{
  return TimePoint{m_data - dur.m_data};
}

Duration
TimePoint::operator-(const TimePoint& other) const
{
  return Duration{m_data - other.m_data};
}

} // namespace setsugen
