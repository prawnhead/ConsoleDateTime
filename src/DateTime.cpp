#include "DateTime.h"

#ifndef ARDUINO
  using namespace std;
#endif

// PUBLIC FUNCTIONS

DateTime::DateTime() {
  epoch();
}

DateTime::DateTime(int year, byte month, byte day, byte hour, byte minute, byte second, int millisecond) {
  _year = year - MIN_YEAR;
  _month = month;
  _day = day;
  _hour = hour;
  _minute = minute;
  _second = second;
  _millisecond = millisecond;
  _string = 0;
}

void DateTime::epoch() {
  _year = 0;
  _month = 1;
  _day = 1;
  _hour = 0;
  _minute = 0;
  _second = 0;
  _millisecond = 0;
  _string = 0;
}

int DateTime::year() const {
  return MIN_YEAR + _year;
}

byte DateTime::month() const {
  return _month;
}

byte DateTime::day() const {
  return _day;
}

byte DateTime::hour() const {
  return _hour;
}

byte DateTime::minute() const {
  return _minute;
}

byte DateTime::second() const {
  return _second;
}

int DateTime::millisecond() const {
  return _millisecond;
}

boolean DateTime::isLeapYear(int year) {
  //http://en.wikipedia.org/wiki/Leap_year
  return (year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0));
}

boolean DateTime::isLeapYear() const {
  return isLeapYear(year());
}

byte DateTime::daysInMonth() const {
  return daysInMonth(_month, year());
}

byte DateTime::daysInMonth(byte month, int year) {
 // http://en.wikipedia.org/wiki/Month
 switch (month) {
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

DateTime& DateTime::add(int interval, Period period) {
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
//    if (period == Day) {
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
//  }
//  if (period == Month) {  // TODO Can create invalid dates! 2000-01-31 +1 Month = ?
//    int magnitude = this->month() + interval;  // 1 -1 = 0
//    interval = magnitude / MONTHS_PER_YEAR;
//    _month = (byte)(magnitude % MONTHS_PER_YEAR);
//    if (!_month) {
//      _month = MONTHS_PER_YEAR;
//      interval--;
//    }
//    if (interval != 0) period = Year;
//  }
  if (period == Year) { // TODO: Add error checking here
    int testYear = interval + _year;
    if (testYear > MAX_YEAR || testYear < MIN_YEAR) { // overflow will occur
      epoch();

    } else _year += interval;
  }

//  // Correct for different month lengths, if required.
//  if (_day > daysInMonth()) {
//    _daysAdjusted = _day - daysInMonth();
//    _day = daysInMonth();
//  }
  return *this;
}

#ifndef ARDUINO
char* DateTime::intToString(int value) {
  static char ramBuffer[10];
  sprintf(ramBuffer, "%d", value);
  return ramBuffer;
}
#endif

String& DateTime::toString() {
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

// PRIVATE FUNCTIONS
