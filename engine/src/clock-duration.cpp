#include <setsugen/clock.h>

// Private headers
#include "clock-units.h"

namespace setsugen
{
constexpr const unsigned long long cv_milliseconds = 10;
constexpr const unsigned long long cv_seconds      = 1000 * cv_milliseconds;
constexpr const unsigned long long cv_minutes      = 60 * cv_seconds;
constexpr const unsigned long long cv_hours        = 60 * cv_minutes;
constexpr const unsigned long long cv_days         = 24 * cv_hours;

Duration::Duration(unsigned long long duration) : m_data{duration}
{}

Duration::~Duration() noexcept = default;

unsigned long long
Duration::get_day() const
{
  return m_data / cv_days;
}

unsigned long long
Duration::get_hour() const
{
  return m_data / cv_hours;
}

unsigned long long
Duration::get_minute() const
{
  return m_data / cv_minutes;
}

unsigned long long
Duration::get_second() const
{
  return m_data / cv_seconds;
}

unsigned long long
Duration::get_millisecond() const
{
  return m_data / cv_milliseconds;
}

void
Duration::stringify(const FormatContext& context) const
{}

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

void
TimePoint::set_format(const std::string& format)
{
  m_format = Formatter::format("{{{}}}", format);
}

void
TimePoint::stringify(const FormatContext& context) const
{}

} // namespace setsugen
