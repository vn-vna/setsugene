#pragma once

#include "chrono_fwd.inl"

#include "../format/format_fwd.inl"

namespace setsugen
{

enum class TimeZoneOffset : int
{
  UTC_PLUS_13  = 780,
  UTC_PLUS_12  = 720,
  UTC_PLUS_11  = 660,
  UTC_PLUS_10  = 600,
  UTC_PLUS_9   = 540,
  UTC_PLUS_8   = 480,
  UTC_PLUS_7   = 420,
  UTC_PLUS_6   = 360,
  UTC_PLUS_5   = 300,
  UTC_PLUS_4   = 240,
  UTC_PLUS_3   = 180,
  UTC_PLUS_2   = 120,
  UTC_PLUS_1   = 60,
  UTC          = 0,
  UTC_MINUS_1  = -60,
  UTC_MINUS_2  = -120,
  UTC_MINUS_3  = -180,
  UTC_MINUS_4  = -240,
  UTC_MINUS_5  = -300,
  UTC_MINUS_6  = -360,
  UTC_MINUS_7  = -420,
  UTC_MINUS_8  = -480,
  UTC_MINUS_9  = -540,
  UTC_MINUS_10 = -600,
  UTC_MINUS_11 = -660,
  UTC_MINUS_12 = -720,
  UTC_MINUS_13 = -780,
};

/**
 * @brief Date class to represent a date and time.
 * Format specifiers used in the format string which
 * can be used to stringify and parse dates:
 * - &Y   - Short year (e.g. 21)
 * - &YY  - Long year (e.g. 2021)
 * - &m   - Month (1-12)
 * - &mm  - Month (01-12)
 * - &M   - Short month name (e.g. Jan)
 * - &MM  - Long month name (e.g. January)
 * - &d   - Day (1-31)
 * - &dd  - Day (01-31)
 * - &D   - Day in year (1-366)
 * - &DD  - Day in year (01-366)
 * - &w   - Weekday (0-6)
 * - &W   - Short weekday name (e.g. Mon)
 * - &WW  - Long weekday name (e.g. Monday)
 * - &H   - Hour (0-23)
 * - &HH  - Hour (00-23)
 * - &h   - Hour (1-12)
 * - &hh  - Hour (01-12)
 * - &A   - AM/PM
 * - &a   - am/pm
 * - &i   - Minute (0-59)
 * - &ii  - Minute (00-59)
 * - &s   - Second (0-59)
 * - &ss  - Second (00-59)
 * - &f   - Millisecond (0-999)
 * - &ff  - Millisecond (00-999)
 * - &u   - Microsecond (0-999)
 * - &uu  - Microsecond (00-999)
 * - &z   - Timezone offset in minute (e.g. +0000)
 * - &Z   - Timezone offset in hour (e.g. +00:00)
 * - &&   - Ampersand sign
 */
class Date
{
public:
  Date(int year = 1970, int month = 1, int day = 1, int weekday = 0, int hour = 0, int minute = 0, int second = 0,
       int millisecond = 0, int microsecond = 0, int tzoffset = 0);

  inline int year() const;
  inline int month() const;
  inline int day() const;
  inline int weekday() const;
  inline int hour() const;
  inline int minute() const;
  inline int second() const;
  inline int millisecond() const;
  inline int microsecond() const;
  inline int tzh() const;
  inline int tzm() const;

  inline void set_year(int year);
  inline void set_month(int month);
  inline void set_day(int day);
  inline void set_hour(int hour);
  inline void set_minute(int minute);
  inline void set_second(int second);
  inline void set_millisecond(int millisecond);
  inline void set_microsecond(int microsecond);
  inline void set_tzoffset(int tzoffset);
  inline void set_tzh(int tzh);
  inline void set_tzm(int tzm);

  /**
   * @brief Create a new date object with the current date and time in another
   * timezone.
   *
   * @param tzoffset
   * @return Date
   */
  inline Date use_tzoffset(int tzoffset) const;

  /**
   * @brief Get the current date and time.
   *
   * @return Date
   */
  inline static Date now();

  /**
   * @brief Parse a date from a string using a specific format.
   * @param str
   * @param format
   * @return Date
   */
  static Date from_string(const std::string& str, const std::string& format);

  inline static constexpr const char* ISO_8601_FORMAT = "&YY-&mm-&ddT&HH:&ii:&ss.&ff&ZZ";

private:
  struct ParserContext
  {
    std::istream& stream;
    std::istream& fms;
    int           ampm;
  };

  void parse_next_token(ParserContext& ctx);
  void parse_year(ParserContext& ctx);
  void parse_month(ParserContext& ctx);
  void parse_day(ParserContext& ctx);
  void parse_weekday(ParserContext& ctx);
  void parse_hour(ParserContext& ctx);
  void parse_minute(ParserContext& ctx);
  void parse_second(ParserContext& ctx);
  void parse_millisecond(ParserContext& ctx);
  void parse_microsecond(ParserContext& ctx);
  void parse_tzoffset(ParserContext& ctx);
  void check_nontoken(ParserContext& ctx);
  void fix_parsed_values(ParserContext& ctx);

  std::string print(const std::string& format) const;

  static Date new_dangling_date();

  int m_year;
  int m_month;
  int m_day;
  int m_weekday;
  int m_hour;
  int m_minute;
  int m_second;
  int m_millisecond;
  int m_microsecond;
  int m_tzoffset;
};

template<>
class Stringify<Date>
{
public:
  static void stringify(const FormatContext& context, const Date& value);

private:
  static void stringify_year(std::ostream& output, std::istream fms, const Date& value);
  static void stringify_month(std::ostream& output, std::istream fms, const Date& value);
  static void stringify_day(std::ostream& output, std::istream fms, const Date& value);
  static void stringify_weekday(std::ostream& output, std::istream fms, const Date& value);
  static void stringify_hour(std::ostream& output, std::istream fms, const Date& value);
  static void stringify_minute(std::ostream& output, std::istream fms, const Date& value);
  static void stringify_second(std::ostream& output, std::istream fms, const Date& value);
  static void stringify_millisecond(std::ostream& output, std::istream fms, const Date& value);
  static void stringify_microsecond(std::ostream& output, std::istream fms, const Date& value);
  static void stringify_tzoffset(std::ostream& output, std::istream fms, const Date& value);
};

} // namespace setsugen
