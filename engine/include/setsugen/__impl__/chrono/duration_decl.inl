#pragma once

#include "chrono_fwd.inl"

namespace setsugen
{

/**
 * @brief Represents a duration of time.
 * This class is used to represent a duration of time in a generic way.
 * The scale of the duration is in 100 nanosecond intervals and is stored as an
 * unsigned 64-bit integer.
 */
class Duration final
{
public:
  explicit Duration(unsigned long long duration = 0);
  ~Duration() noexcept;

  inline uint64_t as_milliseconds() const;
  inline uint64_t as_seconds() const;
  inline uint64_t as_minutes() const;
  inline uint64_t as_hours() const;
  inline uint64_t as_days() const;

  inline static Duration milliseconds(uint64_t ms);
  inline static Duration seconds(uint64_t s);
  inline static Duration minutes(uint64_t m);
  inline static Duration hours(uint64_t h);
  inline static Duration days(uint64_t d);

  inline Duration& operator=(const Duration& other);
  inline Duration  operator+(const Duration& other) const;
  inline Duration  operator-(const Duration& other) const;

private:
  unsigned long long m_data;

  static constexpr uint64_t CV_TO_MICROSECONDS = 1;
  static constexpr uint64_t CV_TO_MILLISECONDS = 1000 * CV_TO_MICROSECONDS;
  static constexpr uint64_t CV_TO_SECONDS      = 1000 * CV_TO_MILLISECONDS;
  static constexpr uint64_t CV_TO_MINUTES      = 60 * CV_TO_SECONDS;
  static constexpr uint64_t CV_TO_HOURS        = 60 * CV_TO_MINUTES;
  static constexpr uint64_t CV_TO_DAYS         = 24 * CV_TO_HOURS;

  friend class TimePoint;
};

} // namespace setsugen
