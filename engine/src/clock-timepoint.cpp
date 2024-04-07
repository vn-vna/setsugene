// Dependency headers
#include <date/date.h>

// Private headers
#include "clock-units.h"

namespace setsugen
{
TimePoint::TimePoint(unsigned long long timepoint) : m_data{timepoint}
{}

TimePoint::TimePoint(const std::string& time_str, const std::string& format)
{}

int
TimePoint::get_year() const
{
  auto dp = date::floor<date::days>(TimePointUnit{DurationUnit{this->m_data}});
  return (int) date::year_month_day(dp).year();
}

int
TimePoint::get_month() const
{
  auto dp = date::floor<date::days>(TimePointUnit{DurationUnit{this->m_data}});
  return (unsigned int) date::year_month_day(dp).month();
}

int
TimePoint::get_day() const
{
  auto dp = date::floor<date::days>(TimePointUnit{DurationUnit{this->m_data}});
  return (unsigned int) date::year_month_day(dp).day();
}

int
TimePoint::get_hour() const
{
  auto tp = TimePointUnit{DurationUnit{this->m_data}};
  auto dp = date::floor<std::chrono::milliseconds>(tp);
  return date::hh_mm_ss(tp - dp).hours().count();
}

int
TimePoint::get_minute() const
{
  auto tp = TimePointUnit{DurationUnit{this->m_data}};
  auto dp = date::floor<std::chrono::milliseconds>(tp);
  return date::hh_mm_ss(tp - dp).minutes().count();
}

int
TimePoint::get_second() const
{
  auto tp = TimePointUnit{DurationUnit{this->m_data}};
  auto dp = date::floor<std::chrono::milliseconds>(tp);
  return (int) date::hh_mm_ss(tp - dp).seconds().count();
}

int
TimePoint::get_millisecond() const
{
  auto tp = TimePointUnit{DurationUnit{this->m_data}};
  auto dp = date::floor<std::chrono::milliseconds>(tp);
  return (int) date::hh_mm_ss(tp - dp).subseconds().count();
}

int
TimePoint::get_day_of_week() const
{
  auto tp = TimePointUnit{DurationUnit{this->m_data}};
  auto dp = date::floor<date::days>(tp);
  return (int) date::weekday(dp).c_encoding();
}

TimePoint&
TimePoint::operator=(const TimePoint& other)
{
  this->m_data = other.m_data;
  return *this;
}

TimePoint
TimePoint::operator+(const Duration& dur)
{
  this->m_data += dur.m_data;
  return *this;
}

TimePoint
TimePoint::operator-(const Duration& dur)
{
  this->m_data -= dur.m_data;
  return *this;
}

Duration
TimePoint::operator-(const TimePoint& other)
{
  return Duration{this->m_data - other.m_data};
}

} // namespace setsugen
