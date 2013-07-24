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

#define MILLISECONDS_PER_SECOND 1000
#define SECONDS_PER_MINUTE 60
#define MINUTES_PER_HOUR 60
#define HOURS_PER_DAY 24
#define DAYS_PER_400_YEARS 146097
#define DAYS_PER_100_YEARS_MIN 36524
#define MONTHS_PER_YEAR 12
//#define DAYS_PER_NORMAL_YEAR 365
#define MIN_YEAR 1900
#define MAX_YEAR 2155
#define ADJUSTMENT_MASK 0x03

/* NOTES:
 * A month is defined as a calendar month.
 * Normal example:
 * DateTime(2001, 1, 15, 0, 0, 0, 0).add(1, DateTime::Month) == DateTime(2001, 2, 15, 0, 0, 0, 0)
 * Adjusted example:
 * DateTime(2001, 1, 31, 0, 0, 0, 0).add(1, DateTime::Month) == DateTime(2001, 2, 28, 0, 0, 0, 0)
 * When the day of the month is adjusted so as to not exceed the length of the month,
 * the getAdjustment() value is set; this indicates the number of days that were subtracted.
 * This occurs when moving by Months or Years from a month with more days to onw with less.
 */
class DateTime
{
  public:
    enum Period { Year, Month, Day, Hour, Minute, Second, Millisecond };
    enum Status { AdjustedBit0 = 1, AdjustedBit1 = 2, Valid = 4, Overflow = 8};
    //enum DayOfWeek { Error, Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday };
    //enum TimeSource { Compiler, NMEA };

    /* TESTED */ DateTime();
    /* TESTED */ DateTime(int year, byte month, byte day, byte hour, byte minute, byte second, int millisecond);

    /* TESTED */ void setEpoch(); // reset to default date/time

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

    /* TESTED */ void setStatus(DateTime::Status status, boolean state);
    /* TESTED */ boolean getStatus(DateTime::Status status);
    /* TESTED */ void setAdjustment(byte value);
    /* TESTED */ byte getAdjustment() const;

    void overflowed();
    static long abs(long value);
    void addOneDay();
    void addOneMonth();
    void addOneYear();

//    static byte leapDaysInRange(DateTime alpha, DateTime omega); // assumes alpha <= omega
//    static long nonLeapDaysInRange(DateTime alpha, DateTime omega);  // assumes alpha <= omega
    static long daysInRange(DateTime alpha, DateTime omega);

    DateTime& add(long interval, Period period);
#ifndef ARDUINO
    /* TESTED */ static char* intToString(int value);
#endif
    /* TESTED */ String& toString();

    /* ASSUMED */ boolean isBefore(const DateTime &other) const;
    /* ASSUMED */ boolean isEqualTo(const DateTime &other) const;
    /* ASSUMED */ boolean operator == (const DateTime &other) const;
    /* ASSUMED */ boolean operator != (const DateTime &other) const;
    /* ASSUMED */ boolean operator <  (const DateTime &other) const;
    /* ASSUMED */ boolean operator <= (const DateTime &other) const;
    /* ASSUMED */ boolean operator >  (const DateTime &other) const;
    /* ASSUMED */ boolean operator >= (const DateTime &other) const;

  protected:
    byte _year; // 0-255 represents 1900-2155
    byte _month, _day, _hour, _minute, _second, _status;
    int _millisecond;
    String* _string;
  private:
    boolean isValid();
};

#endif // DATETIME_H
