#pragma once

#include "duration_decl.inl"

namespace setsugen
{

uint64_t Duration::as_milliseconds() const
{
  return m_data / CV_TO_MILLISECONDS;
}

uint64_t Duration::as_seconds() const
{
  return m_data / CV_TO_SECONDS;
}

uint64_t Duration::as_minutes() const
{
  return m_data / CV_TO_MINUTES;
}

uint64_t Duration::as_hours() const
{
  return m_data / CV_TO_HOURS;
}

uint64_t Duration::as_days() const
{
  return m_data / CV_TO_DAYS;
}

Duration Duration::milliseconds(uint64_t ms)
{
  return Duration(ms * CV_TO_MILLISECONDS);
}

Duration Duration::seconds(uint64_t s)
{
  return Duration(s * CV_TO_SECONDS);
}

Duration Duration::minutes(uint64_t m)
{
  return Duration(m * CV_TO_MINUTES);
}

Duration Duration::hours(uint64_t h)
{
  return Duration(h * CV_TO_HOURS);
}

Duration Duration::days(uint64_t d)
{
  return Duration(d * CV_TO_DAYS);
}

Duration& Duration::operator=(const Duration& other)
{
  m_data = other.m_data;
  return *this;
}

Duration Duration::operator+(const Duration& other) const
{
  return Duration(m_data + other.m_data);
}

Duration Duration::operator-(const Duration& other) const
{
  return Duration(m_data - other.m_data);
}


}
