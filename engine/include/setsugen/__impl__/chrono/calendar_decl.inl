#pragma once

#include "chrono_fwd.inl"

namespace setsugen
{

class GregorianCalendar final
{
public:
  GregorianCalendar();
  ~GregorianCalendar() noexcept;

  Date      to_date(const TimePoint& timepoint) const;
  TimePoint to_timepoint(const Date& date) const;
};

} // namespace setsugen
