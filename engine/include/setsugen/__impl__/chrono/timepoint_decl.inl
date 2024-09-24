#pragma once

#include "chrono_fwd.inl"

namespace setsugen
{

class TimePoint final
{
public:
  TimePoint();
  TimePoint(uint64_t timepoint);

  inline uint64_t data() const;

  ~TimePoint() noexcept;

  TimePoint operator+(const Duration& dur) const;
  TimePoint operator-(const Duration& dur) const;

  Duration operator-(const TimePoint& other) const;

  Date to_date() const;

private:
  unsigned long long m_data;
  std::string        m_format;
};

} // namespace setsugen
