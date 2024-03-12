// Dependency headers
#include <date/date.h>

// Private headers
#include "clock-units.h"
#include "format_impl.h"

namespace setsugen
{

TimePoint::TimePoint(UInt64 timepoint)
    : m_data {timepoint}
{}

TimePoint::TimePoint(const String& time_str, const String& format)
{}

Int32 TimePoint::get_year() const
{
  auto dp = date::floor<date::days>(TimePointUnit {DurationUnit {this->m_data}});
  return (Int32) date::year_month_day(dp).year();
}

Int32 TimePoint::get_month() const
{
  auto dp = date::floor<date::days>(TimePointUnit {DurationUnit {this->m_data}});
  return (UInt32) date::year_month_day(dp).month();
}

Int32 TimePoint::get_day() const
{
  auto dp = date::floor<date::days>(TimePointUnit {DurationUnit {this->m_data}});
  return (UInt32) date::year_month_day(dp).day();
}

Int32 TimePoint::get_hour() const
{
  auto tp = TimePointUnit {DurationUnit {this->m_data}};
  auto dp = date::floor<std::chrono::milliseconds>(tp);
  return date::hh_mm_ss(tp - dp).hours().count();
}

Int32 TimePoint::get_minute() const
{
  auto tp = TimePointUnit {DurationUnit {this->m_data}};
  auto dp = date::floor<std::chrono::milliseconds>(tp);
  return date::hh_mm_ss(tp - dp).minutes().count();
}

Int32 TimePoint::get_second() const
{
  auto tp = TimePointUnit {DurationUnit {this->m_data}};
  auto dp = date::floor<std::chrono::milliseconds>(tp);
  return (Int32) date::hh_mm_ss(tp - dp).seconds().count();
}

Int32 TimePoint::get_millisecond() const
{
  auto tp = TimePointUnit {DurationUnit {this->m_data}};
  auto dp = date::floor<std::chrono::milliseconds>(tp);
  return (Int32) date::hh_mm_ss(tp - dp).subseconds().count();
}

Int32 TimePoint::get_day_of_week() const
{
  auto tp = TimePointUnit {DurationUnit {this->m_data}};
  auto dp = date::floor<date::days>(tp);
  return (Int32) date::weekday(dp).c_encoding();
}

TimePoint& TimePoint::operator=(const TimePoint& other)
{
  this->m_data = other.m_data;
  return *this;
}

TimePoint TimePoint::operator+(const Duration& dur)
{
  this->m_data += dur.m_data;
  return *this;
}

TimePoint TimePoint::operator-(const Duration& dur)
{
  this->m_data -= dur.m_data;
  return *this;
}

Duration TimePoint::operator-(const TimePoint& other)
{
  return Duration {this->m_data - other.m_data};
}

String TimePoint::to_string() const
{
  return Formatter::format(
      "{}", std::chrono::time_point_cast<StdDuration>(TimePointUnit {DurationUnit {this->m_data}})
  );
}

EXPLICIT_INSTANTIATE_SETSUGEN_FORMAT_FOR_CLS(TimePoint);

}  // namespace setsugen