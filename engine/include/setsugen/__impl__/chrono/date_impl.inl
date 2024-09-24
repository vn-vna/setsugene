#pragma once

#include "calendar_decl.inl"
#include "date_decl.inl"
#include "timepoint_decl.inl"

namespace setsugen
{

int
Date::year() const
{
  return m_year;
}

int
Date::month() const
{
  return m_month;
}

int
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

int
Date::weekday() const
{
  return m_weekday;
}

int
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

int
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

int
Date::second() const
{
  return m_second;
}

int
Date::millisecond() const
{
  return m_millisecond;
}

int
Date::microsecond() const
{
  return m_microsecond;
}

int
Date::tzh() const
{
  return m_tzoffset / 60;
}

int
Date::tzm() const
{
  return m_tzoffset % 60;
}

void
Date::set_year(int year)
{
  m_year = year;
}

void
Date::set_month(int month)
{
  m_month = month;
}

void
Date::set_day(int day)
{
  m_day = day;
}

void
Date::set_hour(int hour)
{
  m_hour = hour;
}

void
Date::set_minute(int minute)
{
  m_minute = minute;
}

void
Date::set_second(int second)
{
  m_second = second;
}

void
Date::set_millisecond(int millisecond)
{
  m_millisecond = millisecond;
}

void
Date::set_microsecond(int microsecond)
{
  m_microsecond = microsecond;
}

void
Date::set_tzoffset(int tzoffset)
{
  m_tzoffset = tzoffset;
}

void
Date::set_tzh(int tzh)
{
  m_tzoffset = tzh * 60 + tzm();
}

void
Date::set_tzm(int tzm)
{
  m_tzoffset = tzh() * 60 + tzm;
}

Date
Date::use_tzoffset(int tzoffset) const
{
  return Date{m_year, m_month, m_day, m_hour, m_minute, m_second, m_millisecond, m_microsecond, tzoffset};
}

Date
Date::now()
{
  return GregorianCalendar{}.to_date(TimePoint{});
}

} // namespace setsugen
