#ifndef DATETIME_H
#define DATETIME_H
#ifndef ARDUINO
  #include <iostream>
  #include <string>
  #include <cstdio>
  #define F(X) X
  #define PROGMEM
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
#define MONTHS_PER_YEAR 12
#define MIN_YEAR 1900
#define MAX_YEAR 2155

const char monthNames[] PROGMEM = "Error\0January\0February\0March\0April\0May\0June\0July\0August\0September\0October\0November\0December";
const byte monthNameIndex[] = {0, 6, 14, 23, 29, 35, 39, 44, 49, 56, 66, 74, 83};
const char monthNamesShort[] PROGMEM = "Err\0Jan\0Feb\0Mar\0Apr\0May\0Jun\0Jul\0Aug\0Sep\0Oct\0Nov\0Dec";
const char dayNames[] PROGMEM = "Error\0Sunday\0Monday\0Tuesday\0Wednesday\0Thursday\0Friday\0Saturday";
const byte dayNameIndex[] = {0, 6, 13, 20, 28, 38, 47, 54};
const char dayNamesShort[] PROGMEM = "Err\0Sun\0Mon\0Tue\0Wed\0Thu\0Fri\0Sat";

class DateTime
{
  public:
    enum Period { Year, Month, Day, Hour, Minute, Second, Millisecond };
    enum DayOfWeek { Error, Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday };
    enum TimeSource { Compiler, NMEA };

    DateTime();
    DateTime(char* date, char* time, DateTime::TimeSource source); // Compiler or GPS strings
    DateTime(int year, int month, int day, int hour, int minute, int second, int millisecond);
    void initialise();
    virtual ~DateTime();

    int year() const;
    byte month() const;
    byte day() const;
    byte hour() const;
    byte hourTens() const;
    byte hourUnits() const;
    byte minute() const;
    byte minuteTens() const;
    byte minuteUnits() const;
    byte second() const;
    int millisecond() const;
    int getPeriod(Period period) const;
    byte daysAdjusted() const;
    void zeroDaysAdjusted();

    DateTime::DayOfWeek dayOfWeek() const;
    boolean isLeapYear() const;
    boolean isLeapDay() const;
    boolean isLastDayOfMonth() const;

    DateTime& add(int interval, Period period);
    byte daysInMonth() const;
    long intervalTo(const DateTime other, Period period);
    long intervalIncrement(DateTime& other, Period period);
    unsigned long totalMilliseconds() const;

    boolean isEarlierThan(const DateTime &other) const;
    boolean isEqualTo(const DateTime &other) const;

    boolean operator == (const DateTime &other) const;
    boolean operator != (const DateTime &other) const;
    boolean operator < (const DateTime &other) const;
    boolean operator <= (const DateTime &other) const;
    boolean operator > (const DateTime &other) const;
    boolean operator >= (const DateTime &other) const;

    String& toString();
    String& monthToString();
    String& monthToString(int month);
    String& monthToShortString();
    String& monthToShortString(int month);
    String& dayOfWeekToString();
    String& dayOfWeekToString(enum DayOfWeek day);
    String& dayOfWeekToShortString();
    String& dayOfWeekToShortString(DayOfWeek day);

    static byte leapDaysInRange(DateTime earlier, DateTime later);
    static boolean isLeapYear(int year);

  protected:
    byte _year; // 0 = 1900. 255 = 2155;
    byte _month, _day, _hour, _minute, _second;
    int _millisecond;
    byte _daysAdjusted; // represents days subtracted if _day > daysInMonth
    String* _stringValue;
  private:
    String& getProgMemString(const char *progMemString, byte index);
  #ifndef ARDUINO
    char* intToString(int value);
  #endif
    int parse(char number);
    int parse(char* number, int characters);
    byte monthFromString(char* string);
    boolean isValid();
};

#endif // DATETIME_H
