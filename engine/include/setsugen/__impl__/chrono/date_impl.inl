#pragma once

#include "calendar_decl.inl"
#include "date_decl.inl"
#include "timepoint_decl.inl"

namespace setsugen
{

Int32
Date::year() const
{
  return m_year;
}

Int32
Date::month() const
{
  return m_month;
}

Int32
Date::day() const
{
  auto daymin = m_hour * 60 + m_minute + m_tzoffset;
  if (daymin < 0)
  {
    return m_day - 1;
  }
  if (daymin >= 1440)
  {
    return m_day + 1;
  }
  return m_day;
}

Int32
Date::weekday() const
{
  return m_weekday;
}

Int32
Date::hour() const
{
  auto daymin = m_hour * 60 + m_minute + m_tzoffset;
  if (daymin < 0)
  {
    daymin += 1440;
  }
  if (daymin >= 1440)
  {
    daymin -= 1440;
  }
  return daymin / 60;
}

Int32
Date::minute() const
{
  auto daymin = m_hour * 60 + m_minute + m_tzoffset;

  if (daymin < 0)
  {
    daymin += 1440;
  }
  if (daymin >= 1440)
  {
    daymin -= 1440;
  }
  return daymin % 60;
}

Int32
Date::second() const
{
  return m_second;
}

Int32
Date::millisecond() const
{
  return m_millisecond;
}

Int32
Date::microsecond() const
{
  return m_microsecond;
}

Int32
Date::tzh() const
{
  return m_tzoffset / 60;
}

Int32
Date::tzm() const
{
  return m_tzoffset % 60;
}

Void
Date::set_year(Int32 year)
{
  m_year = year;
}

Void
Date::set_month(Int32 month)
{
  m_month = month;
}

Void
Date::set_day(Int32 day)
{
  m_day = day;
}

Void
Date::set_hour(Int32 hour)
{
  m_hour = hour;
}

Void
Date::set_minute(Int32 minute)
{
  m_minute = minute;
}

Void
Date::set_second(Int32 second)
{
  m_second = second;
}

Void
Date::set_millisecond(Int32 millisecond)
{
  m_millisecond = millisecond;
}

Void
Date::set_microsecond(Int32 microsecond)
{
  m_microsecond = microsecond;
}

Void
Date::set_tzoffset(Int32 tzoffset)
{
  m_tzoffset = tzoffset;
}

Void
Date::set_tzh(Int32 tzh)
{
  m_tzoffset = tzh * 60 + tzm();
}

Void
Date::set_tzm(Int32 tzm)
{
  m_tzoffset = tzh() * 60 + tzm;
}

Date
Date::use_tzoffset(Int32 tzoffset) const
{
  return Date{m_year, m_month, m_day, m_hour, m_minute, m_second, m_millisecond, m_microsecond, tzoffset};
}

Date
Date::now()
{
  return GregorianCalendar{}.to_date(TimePoint{});
}

} // namespace setsugen
