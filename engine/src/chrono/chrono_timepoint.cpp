#include <setsugen/chrono.h>

#include <chrono>

namespace setsugen
{

inline UInt64
__now_std()
{
  return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch())
      .count();
}
TimePoint::TimePoint() : m_data(__now_std())
{}

TimePoint::TimePoint(UInt64 timepoint) : m_data(timepoint)
{}

TimePoint::~TimePoint() noexcept
{}

UInt64
TimePoint::data() const
{
  return m_data;
}

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
