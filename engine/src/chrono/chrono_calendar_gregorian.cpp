#include <setsugen/chrono.h>

namespace setsugen
{

GregorianCalendar::GregorianCalendar()
{}

GregorianCalendar::~GregorianCalendar() noexcept
{}

Date
GregorianCalendar::to_date(const TimePoint& timepoint) const
{
  auto data = timepoint.data();

  // Calculate the date base on the epoch 1/1/1970 00:00:00.000000 UTC+0 (Unix epoch)
  // The result is the date in the Gregorian calendar that distanced `data` microseconds from the epoch

  // Calculate the number of days since the epoch
  auto days = data / 86400000000; // 86400000000 microseconds in a day

  // Calculate weekday since the epoch
  int weekday = (days + 4) % 7; // 4 is the weekday of the epoch

  // Calculate the number of years since the epoch
  int year = 1970;

  while (true)
  {
    auto days_in_year = 365;

    if (year % 4 == 0)
    {
      days_in_year = 366;

      if (year % 100 == 0)
      {
        days_in_year = 365;

        if (year % 400 == 0)
        {
          days_in_year = 366;
        }
      }
    }

    if (days < days_in_year)
    {
      break;
    }

    days -= days_in_year;
    year++;
  }

  // Calculate the number of months since the epoch
  int month = 1;

  while (true)
  {
    auto days_in_month = 31;

    if (month == 4 || month == 6 || month == 9 || month == 11)
    {
      days_in_month = 30;
    }
    else if (month == 2)
    {
      days_in_month = 28;

      if (year % 4 == 0)
      {
        days_in_month = 29;

        if (year % 100 == 0)
        {
          days_in_month = 28;

          if (year % 400 == 0)
          {
            days_in_month = 29;
          }
        }
      }
    }

    if (days < days_in_month)
    {
      break;
    }

    days -= days_in_month;
    month++;
  }

  int day = (int) (days + 1);

  // Calculate the time of the day
  auto time = data % 86400000000; // microseconds in a day

  int hour = (int) (time / 3600000000); // microseconds in an hour
  time %= 3600000000;

  int minute = (int) (time / 60000000); // microseconds in a minute
  time %= 60000000;

  int second = (int) (time / 1000000); // microseconds in a second
  time %= 1000000;

  int millisecond = (int) (time / 1000); // microseconds in a millisecond
  time %= 1000;

  int microsecond = (int) time;

  return {year, month, day, weekday, hour, minute, second, millisecond, microsecond};
}

} // namespace setsugen
