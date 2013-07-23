#ifndef DATETIME_H
#define DATETIME_H
#ifndef ARDUINO
  #include <iostream>
  #include <string>
  #include <cstdio>
  #define F(X) X
  #define PROGMEM
  #define int int16_t
  using namespace std;
  typedef uint8_t byte;
  typedef string String;
  typedef bool boolean;
#else
  #include <Arduino.h>
  #define intToString(X) X
#endif

//#define MILLISECONDS_PER_SECOND 1000
//#define SECONDS_PER_MINUTE 60
//#define MINUTES_PER_HOUR 60
//#define HOURS_PER_DAY 24
//#define MONTHS_PER_YEAR 12
//#define DAYS_PER_NORMAL_YEAR 365
#define MIN_YEAR 1900
#define MAX_YEAR 2155

class DateTime
{
  public:

    enum Period { Year, Month, Day, Hour, Minute, Second, Millisecond };
    enum Codes { Valid = 1, Overflow = 2};
    //enum DayOfWeek { Error, Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday };
    //enum TimeSource { Compiler, NMEA };

    /* TESTED */ DateTime();
    /* TESTED */ DateTime(int year, byte month, byte day, byte hour, byte minute, byte second, int millisecond);

    /* TESTED */ void epoch(); // reset to default date/time

    /* TESTED */ int year() const;
    /* TESTED */ byte month() const;
    /* TESTED */ byte day() const;
    /* TESTED */ byte hour() const;
    /* TESTED */ byte minute() const;
    /* TESTED */ byte second() const;
    /* TESTED */ int millisecond() const;

    /* TESTED */ static boolean isLeapYear(int year);
    /* TESTED */ boolean isLeapYear() const;
    /* TESTED */ static byte daysInMonth(byte month, int year);
    /* TESTED */ byte daysInMonth() const;

    DateTime& add(int interval, Period period);
#ifndef ARDUINO
    /* TESTED */ static char* intToString(int value);
#endif
    /* TESTED */ String& toString();

  protected:
    byte _year; // 0-255 represents 1900-2155
    byte _month, _day, _hour, _minute, _second;
    int _millisecond;
    String* _string;
  private:
};

#endif // DATETIME_H
