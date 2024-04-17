#pragma once

#include <setsugen/pch.h>

// Setsugen headers
#include <setsugen/format.h>

// C++ Standard headers
#include <chrono>

namespace setsugen
{
class Duration final
{
public:
  explicit Duration(unsigned long long duration = 0);
  ~Duration() noexcept;

  unsigned long long get_day() const;
  unsigned long long get_hour() const;
  unsigned long long get_minute() const;
  unsigned long long get_second() const;
  unsigned long long get_millisecond() const;

  void stringify(const FormatContext& context) const;

  Duration& operator=(const Duration& other);
  Duration  operator+(const Duration& other) const;
  Duration  operator-(const Duration& other) const;

private:
  unsigned long long m_data;

  friend class TimePoint;
};

class TimePoint final
{
public:
  TimePoint(unsigned long long timepoint = 0);
  TimePoint(const std::string& time_str, const std::string& format = DEFAULT_FORMAT);

  ~TimePoint() noexcept;

  int get_year() const;
  int get_month() const;
  int get_day() const;
  int get_hour() const;
  int get_minute() const;
  int get_second() const;
  int get_millisecond() const;
  int get_day_of_week() const;

  void set_format(const std::string& format);

  void stringify(const FormatContext& context) const;

  TimePoint& operator=(const TimePoint& other);
  TimePoint  operator+(const Duration& dur);
  TimePoint  operator-(const Duration& dur);
  Duration   operator-(const TimePoint& other);

  static constexpr auto DEFAULT_FORMAT = "%Y-%m-%d %H:%M:%S";

private:
  unsigned long long m_data;
  std::string        m_format;
};
} // namespace setsugen
