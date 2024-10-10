#pragma once

#include "chrono_fwd.inl"

namespace setsugen
{

class TimePoint final
{
public:
  TimePoint();
  TimePoint(UInt64 timepoint);

  UInt64 data() const;

  ~TimePoint() noexcept;

  TimePoint operator+(const Duration& dur) const;
  TimePoint operator-(const Duration& dur) const;

  Duration operator-(const TimePoint& other) const;

  Date to_date() const;

  static TimePoint now();

private:
  unsigned long long m_data;
  String        m_format;
};

} // namespace setsugen
