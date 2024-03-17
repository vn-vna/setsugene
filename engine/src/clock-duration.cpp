#include <setsugen/clock.h>

// Private headers
#include "clock-units.h"
#include "format_impl.h"

namespace setsugen
{
constexpr const UInt64 cv_milliseconds = 10;
constexpr const UInt64 cv_seconds      = 1000 * cv_milliseconds;
constexpr const UInt64 cv_minutes      = 60 * cv_seconds;
constexpr const UInt64 cv_hours        = 60 * cv_minutes;
constexpr const UInt64 cv_days         = 24 * cv_hours;

Duration::Duration(UInt64 duration)
  : m_data{duration}
{}

Duration::~Duration() noexcept = default;

UInt64
Duration::get_day() const
{
  return m_data / cv_days;
}

UInt64
Duration::get_hour() const
{
  return m_data / cv_hours;
}

UInt64
Duration::get_minute() const
{
  return m_data / cv_minutes;
}

UInt64
Duration::get_second() const
{
  return m_data / cv_seconds;
}

UInt64
Duration::get_millisecond() const
{
  return m_data / cv_milliseconds;
}

String
Duration::to_string() const
{
  using Milliseconds = std::chrono::milliseconds;
  return Formatter::format(
    "{}", std::chrono::duration_cast<Milliseconds>(DurationUnit{this->m_data})
  );
}

Duration&
Duration::operator=(const Duration& other)
{
  this->m_data = other.m_data;
  return *this;
}

Duration
Duration::operator+(const Duration& other) const
{
  Duration result;
  result.m_data = this->m_data + other.m_data;
  return result;
}

Duration
Duration::operator-(const Duration& other) const
{
  Duration result;
  result.m_data = this->m_data - other.m_data;
  return result;
}

TimePoint::~TimePoint() noexcept = default;

Void
TimePoint::set_format(const String& format)
{
  m_format = Formatter::format("{{{}}}", format);
}

EXPLICIT_INSTANTIATE_SETSUGEN_FORMAT_FOR_CLS(Duration);
} // namespace setsugen
