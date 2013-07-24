#include "DateTime.h"

#ifndef ARDUINO
using namespace std;
#endif

// PUBLIC FUNCTIONS

DateTime::DateTime()
{
    setEpoch();
}

DateTime::DateTime(int year, byte month, byte day, byte hour, byte minute, byte second, int millisecond)
{
    _year = year - MIN_YEAR;
    _month = month;
    _day = day;
    _hour = hour;
    _minute = minute;
    _second = second;
    _millisecond = millisecond;
    _string = 0;
    if (!isValid()) setEpoch();
}

void DateTime::setEpoch()
{
    _year = 0;
    _month = 1;
    _day = 1;
    _hour = 0;
    _minute = 0;
    _second = 0;
    _millisecond = 0;
    _string = 0;
    _status = 0;
    setStatus(Valid, true);
}

int DateTime::year() const
{
    return MIN_YEAR + _year;
}

byte DateTime::month() const
{
    return _month;
}

byte DateTime::day() const
{
    return _day;
}

byte DateTime::hour() const
{
    return _hour;
}

byte DateTime::minute() const
{
    return _minute;
}

byte DateTime::second() const
{
    return _second;
}

int DateTime::millisecond() const
{
    return _millisecond;
}

boolean DateTime::isLeapYear(int year)
{
    //http://en.wikipedia.org/wiki/Leap_year
    return (year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0));
}

boolean DateTime::isLeapYear() const
{
    return isLeapYear(year());
}

byte DateTime::daysInMonth() const
{
    return daysInMonth(_month, year());
}

byte DateTime::daysInMonth(byte month, int year)
{
// http://en.wikipedia.org/wiki/Month
    switch (month)
    {
    case 1:
        return 31;
        break;
    case 2:
        return DateTime::isLeapYear(year) ? 29 : 28;
        break;
    case 3:
        return 31;
        break;
    case 4:
        return 30;
        break;
    case 5:
        return 31;
        break;
    case 6:
        return 30;
        break;
    case 7:
        return 31;
        break;
    case 8:
        return 31;
        break;
    case 9:
        return 30;
        break;
    case 10:
        return 31;
        break;
    case 11:
        return 30;
        break;
    case 12:
        return 31;
        break;
    }
    return 0;
}

void DateTime::setStatus(DateTime::Status status, boolean state)
{
    if (state) _status |= status;
    else _status &= (255 - status);
}

boolean DateTime::getStatus(DateTime::Status status)
{
    return (_status & status);
}

void DateTime::setAdjustment(byte value)
{
    switch (value)
    {
    case 0:
        setStatus(AdjustedBit0, false);
        setStatus(AdjustedBit1, false);
        break;
    case 1:
        setStatus(AdjustedBit0, true);
        setStatus(AdjustedBit1, false);
        break;
    case 2:
        setStatus(AdjustedBit0, false);
        setStatus(AdjustedBit1, true);
        break;
    case 3:
        setStatus(AdjustedBit0, true);
        setStatus(AdjustedBit1, true);
        break;
    }
}

byte DateTime::getAdjustment() const
{
    return _status & ADJUSTMENT_MASK;
}

void DateTime::overflowed() {
  setEpoch();
  setStatus(Valid, false);
  setStatus(Overflow, true);
}

long DateTime::abs(long value) {
  if (value < 0) return -value;
  return value;
}

//byte DateTime::leapDaysInRange(DateTime alpha, DateTime omega)
//// Precondition: alpha <= omega
//{
//    // Counts the number of WHOLE leap days within the range.
//    byte leaps = 0;
//    // 1. Check for leap day inclusion in alpha.year()
//    if (isLeapYear(alpha.year()) &&
//        alpha <= DateTime(alpha.year(), 2, 29, 0, 0, 0, 0) &&
//        omega >= DateTime(alpha.year(), 3, 1, 0, 0, 0, 0)) leaps++;
//    // 2. Check for leap day inclusion in omega.year()
//    if (isLeapYear(omega.year()) &&
//        omega.year() != alpha.year() &&
//        alpha <= DateTime(omega.year(), 2, 29, 0, 0, 0, 0) &&
//        omega >= DateTime(omega.year(), 3, 1, 0, 0, 0, 0)) leaps++;
//    // 3. Iterate: for every 4 years count leap year if isLeapYear(year)
//    int year = alpha.year();
//    do year++;
//    while(!DateTime::isLeapYear(year));
//    while(year < omega.year())
//    {
//        if (DateTime::isLeapYear(year)) leaps++;
//        year += 4;
//    }
//    return leaps;
//}
//
//long DateTime::nonLeapDaysInRange(DateTime alpha, DateTime omega) {
//// Precondition: alpha <= omega
//  long days = 0;
//  DateTime start = DateTime(alpha.year(), alpha.month(), alpha.day(), 0, 0, 0, 0);
//  DateTime finish = DateTime(omega.year(), omega.month(), omega.day(), 0, 0, 0, 0);
//  if (alpha > start) days--;
//  int daysToEndOfMonth = DateTime::daysInMonth(start.month(), 1999) - start.day(); // Always use non-leap year
//  if ()
//}

void DateTime::addOneDay() {
  if (_day < daysInMonth()) _day++;
  else {
    _day = 1;
    addOneMonth();
  }
}

void DateTime::addOneMonth() {
  if (_month < MONTHS_PER_YEAR) _month++;
  else {
    _month = 1;
    addOneYear();
  }
}

void DateTime::addOneYear() {
  if (_year < MAX_YEAR) _year++;
  else overflowed();
}

long DateTime::daysInRange(DateTime alpha, DateTime omega) {
  // Precondition: alpha < omega
  long days = 0;
  if (DateTime(alpha.year(), alpha.month(), alpha.day(), omega.hour(), omega.minute(), omega.second(), omega.millisecond()) < alpha) days--;
  alpha = DateTime(alpha.year(), alpha.month(), alpha.day(), 0, 0, 0, 0);
  omega = DateTime(omega.year(), omega.month(), omega.day(), 0, 0, 0, 0);
  while (alpha < omega) {
    alpha.addOneDay();
    days++;
  }
  return days;
}

DateTime& DateTime::add(long interval, Period period)
{
    long carry = 0;
    int direction = (interval < 0) ? -1 : 1;
    long intervalMagnitude = DateTime::abs(interval);
//  // Should accept a positive or negative interval for any period.
//  if (interval == 0) return *this;
//  int newValue = 0;
//  if (period == Millisecond) {
//    int magnitude = _millisecond + interval;
//    interval = magnitude / MILLISECONDS_PER_SECOND; // carry value
//    _millisecond = magnitude % MILLISECONDS_PER_SECOND;
//    if (_millisecond < 0) {
//      _millisecond += MILLISECONDS_PER_SECOND;
//      interval -= 1;
//    }
//    if (interval != 0) period = Second; // carry required
//  }
//  if (period == Second) {
//    int magnitude = _second + interval;
//    interval = magnitude / SECONDS_PER_MINUTE;
//    newValue = magnitude % SECONDS_PER_MINUTE;
//    if (newValue < 0) {
//      _second = newValue + SECONDS_PER_MINUTE;
//      interval -= 1;
//    } else {
//      _second = (byte)newValue;
//    }
//    if (interval != 0) period = Minute;
//  }
//  if (period == Minute) {
//    int magnitude = _minute + interval;
//    interval = magnitude / MINUTES_PER_HOUR;
//    newValue = magnitude % MINUTES_PER_HOUR;
//    if (newValue < 0) {
//      _minute = newValue + MINUTES_PER_HOUR;
//      interval -= 1;
//    } else {
//      _minute = (byte)newValue;
//    }
//    if (interval != 0) period = Hour;
//  }
//  if (period == Hour) {
//    int magnitude = _hour + interval;
//    interval = magnitude / HOURS_PER_DAY;
//    newValue = magnitude % HOURS_PER_DAY;
//    if (newValue < 0) {
//      _hour = newValue + HOURS_PER_DAY;
//      interval -= 1;
//    } else {
//      _hour = (byte)newValue;
//    }
//    if (interval != 0) period = Day;
//  }
    if (period == Day)
    {
        carry = 0;
        if (intervalMagnitude >= DAYS_PER_400_YEARS) {
            overflowed();
            return *this;
        }
        while (intervalMagnitude >= DAYS_PER_100_YEARS_MIN) {
          if ((year() + 100) > MAX_YEAR) {
            overflowed();
            return *this;
          }

        }
//    while(interval) { // TODO Replace iteration
//      int magnitude = _day + interval;
//      int daysInMonth = this->daysInMonth();
//      if (magnitude > daysInMonth) {
//        _day = 1;
//        add(1, DateTime::Month);
//        interval = magnitude - daysInMonth - 1;
//      } else if (magnitude < 1) {
//        int tempDay = day();
//        _day = 1;
//        add(-1, DateTime::Month);
//        _day = this->daysInMonth();
//        interval = interval + tempDay;
//      } else {
//          _day += interval;
//          interval = 0;
//      }
//    }
        if (carry != 0)
        {
            period = Year;
            interval = carry;
        }
    }

    if (period == Month) // TODO: Overflow checks
    // Can create erroneous dates eg. 31st Feb
    // See correction below
    {
        long magnitude = this->month() + interval;
        interval = magnitude / MONTHS_PER_YEAR;
        _month = (byte)(magnitude % MONTHS_PER_YEAR);
        if (_month == 0)
        {
            _month = MONTHS_PER_YEAR;
            interval--;
        }
        if (interval != 0) period = Year;
    }

    if (period == Year)
    {
        long testYear = interval + year();
        if (testYear > MAX_YEAR || testYear < MIN_YEAR)   // overflow will occur
        {
          overflowed();
          return *this;
        }
        else _year += interval;
    }

    // Correct for different month lengths, if required.
    if (_day > daysInMonth())
    {
        setAdjustment(_day - daysInMonth());
        _day = daysInMonth();
    }
    return *this;
}

#ifndef ARDUINO
char* DateTime::intToString(int value)
{
    static char ramBuffer[10];
    sprintf(ramBuffer, "%d", value);
    return ramBuffer;
}
#endif

String& DateTime::toString()
{
    //http://arduino.cc/en/Reference/StringObject
    String* output = new String();
    *output += intToString(year());
    *output += '-';
    if (_month < 10) *output += '0';
    *output += intToString(_month);
    *output += '-';
    if (_day < 10) *output += '0';
    *output += intToString(_day);
    *output += ' ';
    if (_hour < 10) *output += '0';
    *output += intToString(_hour);
    *output += ':';
    if (_minute < 10) *output += '0';
    *output += intToString(_minute);
    *output += ':';
    if (_second < 10) *output += '0';
    *output += intToString(_second);
    *output += '.';
    if (_millisecond < 100) *output += '0';
    if (_millisecond < 10) *output += '0';
    *output += intToString(_millisecond);

    delete(_string);
    _string = output;
    return *_string;
}

boolean DateTime::isBefore(const DateTime &other) const
{
    if (this->year() < other.year()) return true;
    if (this->year() > other.year()) return false;
    if (this->month() < other.month()) return true;
    if (this->month() > other.month()) return false;
    if (this->day() < other.day()) return true;
    if (this->day() > other.day()) return false;
    if (this->hour() < other.hour()) return true;
    if (this->hour() > other.hour()) return false;
    if (this->minute() < other.minute()) return true;
    if (this->minute() > other.minute()) return false;
    if (this->second() < other.second()) return true;
    if (this->second() > other.second()) return false;
    if (this->millisecond() < other.millisecond()) return true;
    if (this->millisecond() > other.millisecond()) return false;
    return false;
}

boolean DateTime::isEqualTo(const DateTime &other) const
{
    return (this->year() == other.year() &&
            this->month() == other.month() &&
            this->day() == other.day() &&
            this->hour() == other.hour() &&
            this->minute() == other.minute() &&
            this->second() == other.second() &&
            this->millisecond() == other.millisecond());
}

boolean DateTime::operator == (const DateTime &other) const
{
    return this->isEqualTo(other);
}

boolean DateTime::operator != (const DateTime &other) const
{
    return !this->isEqualTo(other);
}

boolean DateTime::operator < (const DateTime &other) const
{
    return this->isBefore(other);
}

boolean DateTime::operator <= (const DateTime &other) const
{
    return this->isBefore(other) || this->isEqualTo(other);
}

boolean DateTime::operator > (const DateTime &other) const
{
    return other.isBefore(*this);
}

boolean DateTime::operator >= (const DateTime &other) const
{
    return other.isBefore(*this) || other.isEqualTo(*this);
}

// PRIVATE FUNCTIONS

boolean DateTime::isValid()
{
    boolean validity = true;
    // all years are valid (0 - 255) = (1900 - 2155)
    if (_month == 0) validity = false;
    else if (_month > MONTHS_PER_YEAR) validity = false;
    else if (_day == 0) validity = false;
    else if (_day > daysInMonth()) validity = false; // month must be checked prior to calling daysInMonth()
    else if (_hour > (HOURS_PER_DAY - 1)) validity = false;
    else if (_minute > (MINUTES_PER_HOUR - 1)) validity = false;
    else if (_second > (SECONDS_PER_MINUTE - 1)) validity = false;
    else if (_millisecond < 0) validity = false;
    else if (_millisecond > (MILLISECONDS_PER_SECOND - 1)) validity = false;
    if (!validity) setStatus(Valid, false);
    return validity;
}
