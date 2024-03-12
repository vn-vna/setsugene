#pragma once

#include <setsugen/pch.h>

// Setsugen headers
#include <setsugen/format.h>

// C++ Standard headers
#include <chrono>

namespace setsugen
{

class Duration : virtual public Formattable
{
public:
  explicit Duration(UInt64 duration = 0);
  ~Duration() noexcept;

public:
  UInt64 get_day() const;
  UInt64 get_hour() const;
  UInt64 get_minute() const;
  UInt64 get_second() const;
  UInt64 get_millisecond() const;

  String to_string() const override;

public:
  Duration& operator=(const Duration& other);
  Duration  operator+(const Duration& other) const;
  Duration  operator-(const Duration& other) const;

private:
  UInt64 m_data;

private:
  friend class TimePoint;
};

class TimePoint : virtual public Formattable
{
public:
  TimePoint(UInt64 timepoint = 0);
  TimePoint(const String& time_str, const String& format = TimePoint::DEFAULT_FORMAT);

public:
  Int32 get_year() const;
  Int32 get_month() const;
  Int32 get_day() const;
  Int32 get_hour() const;
  Int32 get_minute() const;
  Int32 get_second() const;
  Int32 get_millisecond() const;

  Int32 get_day_of_week() const;

  String to_string() const override;

public:
  TimePoint& operator=(const TimePoint& other);
  TimePoint  operator+(const Duration& dur);
  TimePoint  operator-(const Duration& dur);
  Duration   operator-(const TimePoint& other);

public:
  static constexpr const Char* DEFAULT_FORMAT = "%Y-%m-%d %H:%M:%S";

private:
  UInt64 m_data;
  String m_format;
};

}  // namespace setsugen