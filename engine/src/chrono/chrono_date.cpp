#include <setsugen/chrono.h>
#include <setsugen/exception.h>

#include <sstream>

constexpr const char* months[] = { //
    "January", "February", "March",     "April",   "May",      "June",
    "July",    "August",   "September", "October", "November", "December"};

constexpr const char* weekdays[] = { //
    "Sunday",   "Monday", "Tuesday", "Wednesday",
    "Thursday", "Friday", "Saturday"};

int
__get_day_in_month(int month, int year)
{
  if (month == 2)
  {
    if (year % 4 == 0)
    {
      if (year % 100 == 0)
      {
        if (year % 400 == 0)
        {
          return 29;
        }
        return 28;
      }
      return 29;
    }
    return 28;
  }

  if (month == 4 || month == 6 || month == 9 || month == 11)
  {
    return 30;
  }

  return 31;
}

bool
__check_stream(std::istream& stream, const char* str, int max_len = 100)
{
  auto fallback_pos = stream.tellg();
  for (size_t i = 0; i < std::strlen(str) && i < max_len; i++)
  {
    if (stream.peek() != str[i])
    {
      stream.seekg(fallback_pos);
      return false;
    }
    stream.ignore();
  }

  return true;
}

int
__get_short_month_from_stream(std::istream& stream)
{
  for (int i = 0; i < 12; i++)
  {
    if (__check_stream(stream, months[i], 3))
    {
      return i + 1;
    }
  }

  throw setsugen::InvalidFormatException("Invalid short month format");
}

int
__get_long_month_from_stream(std::istream& stream)
{
  for (int i = 0; i < 12; i++)
  {
    if (__check_stream(stream, months[i]))
    {
      return i + 1;
    }
  }

  throw setsugen::InvalidFormatException("Invalid long month format");
}

int
__get_short_weekday_from_stream(std::istream& stream)
{
  for (int i = 0; i < 7; i++)
  {
    if (__check_stream(stream, weekdays[i], 3))
    {
      return i;
    }
  }

  throw setsugen::InvalidFormatException("Invalid short weekday format");
}

int
__get_long_weekday_from_stream(std::istream& stream)
{
  for (int i = 0; i < 7; i++)
  {
    if (__check_stream(stream, weekdays[i]))
    {
      return i;
    }
  }

  throw setsugen::InvalidFormatException("Invalid long weekday format");
}

int
__get_number_from_stream(std::istream& stream, int count, int max = 100)
{
  std::vector<char> buffer;
  if (-1 == count) // Variadic
  {
    for (int i = 0; i < max; i++)
    {
      if (std::isdigit(stream.peek()))
      {
        buffer.push_back((char) stream.get());
      }
      else
      {
        break;
      }
    }
  }
  else
  {
    for (int i = 0; i < count; i++)
    {
      if (std::isdigit(stream.peek()))
      {
        buffer.push_back((char) stream.get());
      }
      else
      {
        break;
      }
    }
  }

  buffer.push_back('\0');

  try
  {
    return std::stoi(buffer.data());
  }
  catch (const std::exception& e)
  {
    throw setsugen::InvalidFormatException("Invalid number format {}",
                                           buffer.data());
  }
}

int
__get_timezone_in_minute(std::istream& stream)
{
  int sign = 1;
  if (stream.peek() == '-')
  {
    sign = -1;
    stream.ignore();
  }
  else if (stream.peek() == '+')
  {
    stream.ignore();
  }
  else
  {
    throw setsugen::InvalidFormatException("Invalid timezone format");
  }

  return sign * __get_number_from_stream(stream, 4);
}

int
__get_timezone_in_hour(std::istream& stream)
{
  int sign = 1;
  if (stream.peek() == '-')
  {
    sign = -1;
    stream.ignore();
  }
  else if (stream.peek() == '+')
  {
    stream.ignore();
  }
  else
  {
    throw setsugen::InvalidFormatException("Invalid timezone format");
  }

  int hour = __get_number_from_stream(stream, 2);
  if (stream.peek() == ':')
  {
    stream.ignore();
    int minute = __get_number_from_stream(stream, 2);
    return sign * (hour * 60 + minute);
  }
  else
  {
    throw setsugen::InvalidFormatException("Invalid timezone format");
  }

  return sign * hour * 60;
}


namespace setsugen
{

Date::Date(int year, int month, int day, int weekday, int hour, int minute,
           int second, int millisecond, int microsecond, int tzoffset)
    : m_year(year), m_month(month), m_day(day), m_weekday(weekday),
      m_hour(hour), m_minute(minute), m_second(second),
      m_millisecond(millisecond), m_microsecond(microsecond),
      m_tzoffset(tzoffset)
{}

void
Date::parse_next_token(ParserContext& ctx)
{
  ctx.fms.ignore(); // Ignore the ampersand sign
  char c = ctx.fms.peek();

  switch (c)
  {
    case '&':
    {
      if (__check_stream(ctx.stream, "&"))
      {
        ctx.fms.ignore(); // Ignore the ampersand sign
      }
      else
      {
        throw InvalidFormatException("Format does not match the input string");
      }
      break;
    }

    case 'Y':
    {
      parse_year(ctx);
      break;
    }

    case 'm':
    case 'M':
    {
      parse_month(ctx);
      break;
    }

    case 'd':
    {
      parse_day(ctx);
      break;
    }

    case 'w':
    case 'W':
    {
      parse_weekday(ctx);
      break;
    }

    case 'H':
    case 'h':
    case 'a':
    {
      parse_hour(ctx);
      break;
    }

    case 'i':
    {
      parse_minute(ctx);
      break;
    }

    case 's':
    {
      parse_second(ctx);
      break;
    }

    case 'f':
    {
      parse_millisecond(ctx);
      break;
    }

    case 'u':
    {
      parse_microsecond(ctx);
      break;
    }

    case 'z':
    case 'Z':
    {
      parse_tzoffset(ctx);
      break;
    }

    default:
    {
      throw InvalidFormatException("Unknown format specifier '{}'", c);
    }
  }
}

void
Date::parse_year(ParserContext& ctx)
{
  ctx.fms.ignore(); // Ignore the 'Y' character

  if (ctx.fms.peek() == 'Y')
  {
    m_year = __get_number_from_stream(ctx.stream, 4);
  }
  else
  {
    m_year = __get_number_from_stream(ctx.stream, 2);
  }

  ctx.fms.ignore();
}

void
Date::parse_month(ParserContext& ctx)
{
  char c = ctx.fms.get();

  switch (c)
  {
    case 'm': // Parse numeric month
    {
      if (ctx.fms.peek() == 'm')
      {
        ctx.fms.ignore(); // Ignore the 'm' character
        m_month = __get_number_from_stream(ctx.stream, 2);
      }
      else
      {
        m_month = __get_number_from_stream(ctx.stream, -1, 12);
      }
      break;

      case 'M':
      {
        if (ctx.fms.peek() == 'M')
        {
          ctx.fms.ignore(); // Ignore the 'M' character
          m_month = __get_long_month_from_stream(ctx.stream);
        }
        else
        {
          m_month = __get_short_month_from_stream(ctx.stream);
        }
      }
    }
  }
}

void
Date::parse_day(ParserContext& ctx)
{
  ctx.fms.ignore(); // Ignore the 'd' character

  if (ctx.fms.peek() == 'd')
  {
    ctx.fms.ignore(); // Ignore the 'd' character
    m_day = __get_number_from_stream(ctx.stream, 2);
  }
  else
  {
    m_day = __get_number_from_stream(ctx.stream, -1, 31);
  }
}

void
Date::parse_weekday(ParserContext& ctx)
{
  char c = ctx.fms.get();

  if (c == 'w')
  {
    m_weekday = __get_number_from_stream(ctx.stream, 1);
  }
  else if (c == 'W')
  {
    if (ctx.fms.peek() == 'W')
    {
      ctx.fms.ignore(); // Ignore the 'W' character
      m_weekday = __get_long_weekday_from_stream(ctx.stream);
    }
    else
    {
      m_weekday = __get_short_weekday_from_stream(ctx.stream);
    }
  }
}

void
Date::parse_hour(ParserContext& ctx)
{
  char c = ctx.fms.get();
  switch (c)
  {
    case 'H':
    {
      if (ctx.ampm > 0)
      {
        throw InvalidFormatException("Cannot mix 12-hour and 24-hour formats");
      }

      if (ctx.fms.peek() == 'H')
      {
        ctx.fms.ignore(); // Ignore the 'H' character
        m_hour = __get_number_from_stream(ctx.stream, 2);
      }
      else
      {
        m_hour = __get_number_from_stream(ctx.stream, -1, 23);
      }

      ctx.ampm = -1;
      break;
    }

    case 'h':
    {
      if (ctx.ampm < 0)
      {
        throw InvalidFormatException("Cannot mix 12-hour and 24-hour formats");
      }

      if (ctx.fms.peek() == 'h')
      {
        ctx.fms.ignore(); // Ignore the 'h' character
        m_hour = __get_number_from_stream(ctx.stream, 2);
      }
      else
      {
        m_hour = __get_number_from_stream(ctx.stream, -1, 12);
      }
      break;
    }

    case 'a':
    {
      if (ctx.ampm < 0)
      {
        throw InvalidFormatException("Cannot mix 12-hour and 24-hour formats");
      }

      if (ctx.ampm > 0)
      {
        throw InvalidFormatException("Cannot mix both AM and PM formats");
      }

      if (__check_stream(ctx.stream, "am"))
      {
        ctx.ampm = 1;
      }

      if (__check_stream(ctx.stream, "pm"))
      {
        ctx.ampm = 2;
      }

      break;
    }

    case 'A':
    {
      if (ctx.ampm > 0)
      {
        throw InvalidFormatException("Cannot mix 12-hour and 24-hour formats");
      }

      if (ctx.ampm > 0)
      {
        throw InvalidFormatException("Cannot mix both AM and PM formats");
      }

      if (__check_stream(ctx.stream, "AM"))
      {
        ctx.ampm = 1;
      }

      if (__check_stream(ctx.stream, "PM"))
      {
        ctx.ampm = 2;
      }

      break;
    }
  }
}

void
Date::parse_minute(ParserContext& ctx)
{
  ctx.fms.ignore(); // Ignore the 'i' character
  if (ctx.fms.peek() == 'i')
  {
    ctx.fms.ignore(); // Ignore the 'i' character
    m_minute = __get_number_from_stream(ctx.stream, 2);
  }
  else
  {
    m_minute = __get_number_from_stream(ctx.stream, -1, 59);
  }
}

void
Date::parse_second(ParserContext& ctx)
{
  ctx.fms.ignore(); // Ignore the 's' character
  if (ctx.fms.peek() == 's')
  {
    ctx.fms.ignore(); // Ignore the 's' character
    m_second = __get_number_from_stream(ctx.stream, 2);
  }
  else
  {
    m_second = __get_number_from_stream(ctx.stream, -1, 59);
  }
}

void
Date::parse_millisecond(ParserContext& ctx)
{
  ctx.fms.ignore(); // Ignore the 'f' character
  if (ctx.fms.peek() == 'f')
  {
    ctx.fms.ignore(); // Ignore the 'f' character
    m_millisecond = __get_number_from_stream(ctx.stream, 3);
  }
  else
  {
    m_millisecond = __get_number_from_stream(ctx.stream, -1, 999);
  }
}

void
Date::parse_microsecond(ParserContext& ctx)
{
  ctx.fms.ignore(); // Ignore the 'u' character
  if (ctx.fms.peek() == 'u')
  {
    ctx.fms.ignore(); // Ignore the 'u' character
    m_microsecond = __get_number_from_stream(ctx.stream, 3);
  }
  else
  {
    m_microsecond = __get_number_from_stream(ctx.stream, -1, 999);
  }
}

void
Date::parse_tzoffset(ParserContext& ctx)
{
  char c = ctx.fms.get();

  switch (c)
  {
    case 'z':
    {
      m_tzoffset = __get_timezone_in_minute(ctx.stream);
      break;
    }

    case 'Z':
    {
      m_tzoffset = __get_timezone_in_hour(ctx.stream);
      break;
    }
  }
}

void
Date::check_nontoken(ParserContext& ctx)
{
  char c = (char) ctx.fms.peek();
  char d = (char) ctx.stream.peek();

  if (c != d)
  {
    throw InvalidFormatException("Format does not match the input string");
  }

  ctx.fms.ignore();
  ctx.stream.ignore();
}

void
Date::fix_parsed_values(ParserContext& ctx)
{
  if (ctx.ampm == 1) // AM
  {
    if (m_hour == 12)
    {
      m_hour = 0;
    }
  }
  else if (ctx.ampm == 2) // PM
  {
    if (m_hour < 12)
    {
      m_hour += 12;
    }
  }

  int max_int = std::numeric_limits<int>::max();

  if (m_year < 1970 || m_year > 9999)
  {
    throw InvalidFormatException("Year must be between 1970 and 9999");
  }

  if (m_month < 1 || m_month > 12)
  {
    throw InvalidFormatException("Month must be between 1 and 12");
  }

  if (m_day < 1 || m_day > __get_day_in_month(m_month, m_year))
  {
    throw InvalidFormatException("Day must be between 1 and {}",
                                 __get_day_in_month(m_month, m_year));
  }

  if (m_hour == -max_int)
  {
    m_hour = 0;
  }

  if (m_hour < 0 || m_hour > 23)
  {
    throw InvalidFormatException("Hour must be between 0 and 23");
  }

  if (m_minute == -max_int)
  {
    m_minute = 0;
  }

  if (m_minute < 0 || m_minute > 59)
  {
    throw InvalidFormatException("Minute must be between 0 and 59");
  }

  if (m_second == -max_int)
  {
    m_second = 0;
  }

  if (m_second < 0 || m_second > 59)
  {
    throw InvalidFormatException("Second must be between 0 and 59");
  }

  if (m_millisecond == -max_int)
  {
    m_millisecond = 0;
  }

  if (m_millisecond < 0 || m_millisecond > 999)
  {
    throw InvalidFormatException("Millisecond must be between 0 and 999");
  }

  if (m_microsecond == -max_int)
  {
    m_microsecond = 0;
  }

  if (m_microsecond < 0 || m_microsecond > 999)
  {
    throw InvalidFormatException("Microsecond must be between 0 and 999");
  }

  if (m_tzoffset == -max_int)
  {
    m_tzoffset = 0;
  }

  if (m_tzoffset < -720 || m_tzoffset > 720)
  {
    throw InvalidFormatException(
        "Timezone offset must be between -13:00 and +13:00");
  }

  if (m_tzoffset % 15 != 0)
  {
    throw InvalidFormatException(
        "Timezone offset must be in 15-minute increments");
  }

  int day_in_year = 0;
  for (int i = 1; i < m_month; i++)
  {
    day_in_year += __get_day_in_month(i, m_year);
  }

  int day_since_epoch = 0;
  for (int i = 1970; i < m_year; i++)
  {
    day_since_epoch += 365;
    if (i % 4 == 0)
    {
      if (i % 100 == 0)
      {
        if (i % 400 == 0)
        {
          day_since_epoch += 1;
        }
      }
      else
      {
        day_since_epoch += 1;
      }
    }
  }

  day_since_epoch += day_in_year + m_day - 1;
  int weekday = (day_since_epoch + 4) % 7;

  if (m_weekday == -max_int)
  {
    m_weekday = weekday;
  }
  else if (m_weekday != weekday)
  {
    throw InvalidFormatException("Weekday does not match the date");
  }
}

Date
Date::from_string(const std::string& str, const std::string& format)
{
  auto date = Date::new_dangling_date();
  auto ss   = std::stringstream{str};
  auto fms  = std::stringstream{format};
  auto ctx  = ParserContext{ss, fms, 0};

  while (!ss.eof())
  {
    char c = (char) fms.peek();

    if (c == '&')
    {
      date.parse_next_token(ctx);
    }
    else
    {
      date.check_nontoken(ctx);
    }
  }

  date.fix_parsed_values(ctx);

  return date;
}

Date
Date::new_dangling_date()
{
  int max_int = std::numeric_limits<int>::max();
  return {-max_int, -max_int, -max_int, -max_int, -max_int,
          -max_int, -max_int, -max_int, -max_int, -max_int};
}


void
Stringify<Date>::stringify(const FormatContext& context, const Date& value)
{
  std::string_view fmt;
  if (context.placeholder.specs.find('f') != context.placeholder.specs.end())
  {
    fmt = context.placeholder.specs.at('f');
  }
  else
  {
    fmt = Date::ISO_8601_FORMAT;
  }

  auto fms = std::stringstream{};
  fms << fmt;

  fms.seekg(0);

  while (context.result.eof())
  {
    char c = (char) fms.peek();
    if (c == '&')
    {
      fms.ignore();
    }
    else
    {
      context.result << c;
    }
  }
}

void
Stringify<Date>::stringify_year(std::ostream& output, std::istream fms,
                                const Date& value)
{
  if (fms.peek() == 'Y')
  {
    fms.ignore();
    if (fms.peek() == 'Y')
    {
      output << value.year();
      fms.ignore();
    }
    else
    {
      output << value.year() % 100;
    }
  }
}

void
Stringify<Date>::stringify_month(std::ostream& output, std::istream fms,
                                 const Date& value)
{
  char c = fms.get();
  switch (c)
  {
    case 'm':
    {
      if (fms.peek() == 'm')
      {
        fms.ignore();
        output << value.month();
      }
      else
      {
        output << months[value.month() - 1];
      }
      break;
    }

    case 'M':
    {
      if (fms.peek() == 'M')
      {
        fms.ignore();
        output << months[value.month() - 1];
      }
      else
      {
        output << months[value.month() - 1];
      }
      break;
    }
  }
}

} // namespace setsugen
