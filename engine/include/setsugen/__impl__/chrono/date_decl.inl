#pragma once

#include "chrono_fwd.inl"

#include "../format/format_fwd.inl"

namespace setsugen
{

enum class TimeZoneOffset : Int32
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
  Date(Int32 year = 1970, Int32 month = 1, Int32 day = 1, Int32 weekday = 0, Int32 hour = 0, Int32 minute = 0,
       Int32 second = 0, Int32 millisecond = 0, Int32 microsecond = 0, Int32 tzoffset = 0);

  inline Int32 year() const;
  inline Int32 month() const;
  inline Int32 day() const;
  inline Int32 weekday() const;
  inline Int32 hour() const;
  inline Int32 minute() const;
  inline Int32 second() const;
  inline Int32 millisecond() const;
  inline Int32 microsecond() const;
  inline Int32 tzh() const;
  inline Int32 tzm() const;

  inline Void set_year(Int32 year);
  inline Void set_month(Int32 month);
  inline Void set_day(Int32 day);
  inline Void set_hour(Int32 hour);
  inline Void set_minute(Int32 minute);
  inline Void set_second(Int32 second);
  inline Void set_millisecond(Int32 millisecond);
  inline Void set_microsecond(Int32 microsecond);
  inline Void set_tzoffset(Int32 tzoffset);
  inline Void set_tzh(Int32 tzh);
  inline Void set_tzm(Int32 tzm);

  /**
   * @brief Create a new date object with the current date and time in another
   * timezone.
   *
   * @param tzoffset
   * @return Date
   */
  inline Date use_tzoffset(Int32 tzoffset) const;

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
  static Date from_string(const String& str, const String& format);

  inline static constexpr const char* ISO_8601_FORMAT = "&YY-&mm-&ddT&HH:&ii:&ss.&ff&ZZ";

private:
  struct ParserContext
  {
    InputStream& stream;
    InputStream& fms;
    Int32         ampm;
  };

  Void parse_next_token(ParserContext& ctx);
  Void parse_year(ParserContext& ctx);
  Void parse_month(ParserContext& ctx);
  Void parse_day(ParserContext& ctx);
  Void parse_weekday(ParserContext& ctx);
  Void parse_hour(ParserContext& ctx);
  Void parse_minute(ParserContext& ctx);
  Void parse_second(ParserContext& ctx);
  Void parse_millisecond(ParserContext& ctx);
  Void parse_microsecond(ParserContext& ctx);
  Void parse_tzoffset(ParserContext& ctx);
  Void check_nontoken(ParserContext& ctx);
  Void fix_parsed_values(ParserContext& ctx);

  String print(const String& format) const;

  static Date new_dangling_date();

  Int32 m_year;
  Int32 m_month;
  Int32 m_day;
  Int32 m_weekday;
  Int32 m_hour;
  Int32 m_minute;
  Int32 m_second;
  Int32 m_millisecond;
  Int32 m_microsecond;
  Int32 m_tzoffset;
};

template<>
class Stringify<Date>
{
public:
  static Void stringify(const FormatContext& context, const Date& value);

private:
  static Void stringify_year(OutputStream& output, InputStream& fms, const Date& value);
  static Void stringify_month(OutputStream& output, InputStream& fms, const Date& value);
  static Void stringify_day(OutputStream& output, InputStream& fms, const Date& value);
  static Void stringify_weekday(OutputStream& output, InputStream& fms, const Date& value);
  static Void stringify_hour(OutputStream& output, InputStream& fms, const Date& value);
  static Void stringify_minute(OutputStream& output, InputStream& fms, const Date& value);
  static Void stringify_second(OutputStream& output, InputStream& fms, const Date& value);
  static Void stringify_millisecond(OutputStream& output, InputStream& fms, const Date& value);
  static Void stringify_microsecond(OutputStream& output, InputStream& fms, const Date& value);
  static Void stringify_tzoffset(OutputStream& output, InputStream& fms, const Date& value);
};

} // namespace setsugen
