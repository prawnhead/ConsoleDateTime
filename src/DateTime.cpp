#include "DateTime.h"

#ifndef ARDUINO
  using namespace std;
#endif


DateTime::DateTime()
{
  initialise();
  #ifndef ARDUINO
//  cout << F("DateTime constructor") << endl;
  #else
  Serial.println("DateTime constructor");
  #endif
}

DateTime::DateTime(int year, int month, int day, int hour, int minute, int second, int millisecond) {
  if (year < MIN_YEAR || year > MAX_YEAR) {
    initialise();
    return;
  }
  _stringValue = 0;
  _year = year - MIN_YEAR;
  _month = month;
  _day = day;
  _hour = hour;
  _minute = minute;
  _second = second;
  _millisecond = millisecond;
  _daysAdjusted = 0;
  if (!isValid()) initialise();
}

DateTime::DateTime(char* date, char* time, DateTime::TimeSource source) {
  _stringValue = 0;
  if (source == Compiler) {
      int year = parse((date + 7), 4);
      if (year < MIN_YEAR || year > MAX_YEAR) initialise();
      else {
        _year = year - MIN_YEAR; //epoch.year();
        _month = monthFromString(date);
        _day = parse((date + 4), 2);
        _hour = parse(time, 2);
        _minute = parse(time + 3, 2);
        _second = parse(time + 6, 2);
        _millisecond = 0;
      }
  }
  if (source == NMEA) {
      _year = 100 + parse(date + 4, 2); // TODO: Check for invalid year
      _month = parse(date + 2, 2);
      _day = parse(date, 2);
      _hour = parse(time, 2);
      _minute = parse(time + 2, 2);
      _second = parse(time + 4, 2);
      _millisecond = parse(time + 7, 3);
  }
  _daysAdjusted = 0;
  if (!isValid()) initialise();
}

void DateTime::initialise() {
    _stringValue = 0;
    _year = _hour = _minute = _second = _millisecond = _daysAdjusted = 0;
    _month = _day = 1;
}

DateTime::~DateTime()
{
  #ifndef ARDUINO
//  cout << F("DateTime destructor") << endl;
  #else
  Serial.println("DateTime destructor");
  #endif
}

boolean DateTime::isLeapYear() const {
  return isLeapYear(year());
}

boolean DateTime::isLeapDay() const {
  return _month == 2 && _day == 29;
}

boolean DateTime::isLastDayOfMonth() const {
  return (_day == daysInMonth());
}

int DateTime::year() const {
  return _year + MIN_YEAR;
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

byte DateTime::hourTens() const {
  return _hour/10;
}

byte DateTime::hourUnits() const {
  return _hour%10;
}

byte DateTime::minute() const {
  return _minute;
}

byte DateTime::minuteTens() const {
  return _minute/10;
}

byte DateTime::minuteUnits() const {
  return _minute%10;
}

byte DateTime::second() const {
  return _second;
}

int DateTime::millisecond() const {
  return _millisecond;
}

DateTime::DayOfWeek DateTime::dayOfWeek() const {
  //http://en.wikipedia.org/wiki/Determination_of_the_day_of_the_week
  // Calculating only for the 2000-2099 century
  int century = 6;
  int monthFactors[12] = { 0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5 };
  int monthFactorsLeap[12] = { 6, 2, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5 };
  int twoDigitYear = this->year()%100;
  int yearOverFour = twoDigitYear/4;
  int month = this->isLeapYear() ? monthFactorsLeap[_month - 1] : monthFactors[_month - 1];
  int sum = century + twoDigitYear + yearOverFour + month + this->day();
  return (DateTime::DayOfWeek)(sum % 7 + 1);
}

DateTime& DateTime::add(int interval, Period period) {
  // Should accept a positive or negative interval for any period.
  if (interval == 0) return *this;
  int newValue = 0;
  if (period == Millisecond) {
    int magnitude = _millisecond + interval;
    interval = magnitude / MILLISECONDS_PER_SECOND; // carry value
    _millisecond = magnitude % MILLISECONDS_PER_SECOND;
    if (_millisecond < 0) {
      _millisecond += MILLISECONDS_PER_SECOND;
      interval -= 1;
    }
    if (interval != 0) period = Second; // carry required
  }
  if (period == Second) {
    int magnitude = _second + interval;
    interval = magnitude / SECONDS_PER_MINUTE;
    newValue = magnitude % SECONDS_PER_MINUTE;
    if (newValue < 0) {
      _second = newValue + SECONDS_PER_MINUTE;
      interval -= 1;
    } else {
      _second = (byte)newValue;
    }
    if (interval != 0) period = Minute;
  }
  if (period == Minute) {
    int magnitude = _minute + interval;
    interval = magnitude / MINUTES_PER_HOUR;
    newValue = magnitude % MINUTES_PER_HOUR;
    if (newValue < 0) {
      _minute = newValue + MINUTES_PER_HOUR;
      interval -= 1;
    } else {
      _minute = (byte)newValue;
    }
    if (interval != 0) period = Hour;
  }
  if (period == Hour) {
    int magnitude = _hour + interval;
    interval = magnitude / HOURS_PER_DAY;
    newValue = magnitude % HOURS_PER_DAY;
    if (newValue < 0) {
      _hour = newValue + HOURS_PER_DAY;
      interval -= 1;
    } else {
      _hour = (byte)newValue;
    }
    if (interval != 0) period = Day;
  }
  if (period == Day) {
    while(interval) { // TODO Replace iteration
      int magnitude = _day + interval;
      int daysInMonth = this->daysInMonth();
      if (magnitude > daysInMonth) {
        _day = 1;
        add(1, DateTime::Month);
        interval = magnitude - daysInMonth - 1;
      } else if (magnitude < 1) {
        int tempDay = day();
        _day = 1;
        add(-1, DateTime::Month);
        _day = this->daysInMonth();
        interval = interval + tempDay;
      } else {
        _day += interval;
        interval = 0;
      }
    }
  }
  if (period == Month) {  // TODO Can create invalid dates! 2000-01-31 +1 Month = ?
    int magnitude = this->month() + interval;  // 1 -1 = 0
    interval = magnitude / MONTHS_PER_YEAR;
    _month = (byte)(magnitude % MONTHS_PER_YEAR);
    if (!_month) {
      _month = MONTHS_PER_YEAR;
      interval--;
    }
    if (interval != 0) period = Year;
  }
  if (period == Year) _year += interval;
  if (_day > daysInMonth()) {
    _daysAdjusted = _day - daysInMonth();
    _day = daysInMonth();
  }
  return *this;
}

byte DateTime::daysInMonth() const {
  // http://en.wikipedia.org/wiki/Month
  switch (month()) {
    case 1:
      return 31;
      break;
    case 2:
      return isLeapYear() ? 29 : 28;
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

long DateTime::intervalTo(DateTime other, Period period) {
  // TODO: INCOMPLETE!
  if (*this == other) return 0;
  long int difference = 0;
  int direction = 0;
  DateTime *earlier;
  DateTime *current;
  DateTime *target;
  int limit = 0;
  switch (period) {
    case Year:
      difference = intervalIncrement(other, period);
      break;
    case Month:
      difference = MONTHS_PER_YEAR * (other.year() - this->year());
      difference += other.month() - this->month();
      break;
    case Day:
      if (*this <= other) {
        earlier = new DateTime(*this);
        current = new DateTime(*this);
        target = &other;
        direction = 1;
      } else {
        earlier = new DateTime(other);
        current = new DateTime(other);
        target = this;
        direction = -1;
      }
      // PHASE 1: Add centuries if possible
      limit = MAX_YEAR - 100;
      if (current->year() <= limit) {
        current->add(100, Year);
        while(*current <= *target) {
          difference += direction * 36524;  // Assumes turn of the century is NOT a leap year
          if (*earlier <= DateTime(2000, 2, 29, 0, 0, 0, 0) && DateTime(2000, 3, 1, 0, 0, 0, 0) <= *current) // 2000 leap year
            difference += direction;  // add leap year 2000 not included in 36524 count for "normal" century.
          *earlier = *current;
          if (current->year() > limit) break;
          current->add(100, Year);
        }
        *current = *earlier;
      }
      // PHASE 2: Add decades if possible
      limit = MAX_YEAR - 10;
      if (current->year() <= limit) {
        current->add(4, Year);
        while(*current <= *target) {
          difference += direction * 1461; // includes a leap year
          if (*earlier < DateTime(1900, 3, 1, 0, 0, 0, 0) && DateTime(1900, 3, 1, 0, 0, 0, 0) <= *current) // 1900 not a leap year
            difference -= direction;
          if (*earlier < DateTime(2100, 3, 1, 0, 0, 0, 0) && DateTime(2100, 3, 1, 0, 0, 0, 0) <= *current) // 2100 not a leap year
            difference -= direction;
          *earlier = *current;
          if (current->year() > limit) break;
          current->add(4, Year);
        }
        *current = *earlier;
      }
      // PHASE 3: Add years if possible
      limit = MAX_YEAR - 1;
      if (current->year() <= limit) {
        current->add(1, Year);
        while(*current <= *target) {
          difference += direction * DAYS_PER_NORMAL_YEAR;
          if (earlier->isLeapYear() && *earlier <= DateTime(earlier->year(), 2, 29, 0, 0, 0, 0) && DateTime(earlier->year(), 3, 1, 0, 0, 0, 0) <= *current)
            difference += direction;
          if (current->isLeapYear() && *earlier <= DateTime(current->year(), 2, 29, 0, 0, 0, 0) && DateTime(current->year(), 3, 1, 0, 0, 0, 0) <= *current)
            difference += direction;
          *earlier = *current;
          if (current->year() > limit) break;
          current->add(4, Year);
        }
        *current = *earlier;
      }
      // PHASE 4: Add months if possible

      // PHASE 5: Add days if possible
      delete earlier;
      delete current;
      break;
    default:
      break;
  }
  return difference;
}

// Calculates periods between two dates. CAUTION!
// Calculates years between ANY dates
// Calculates months between dates IN THE SAME YEAR
// Calculates days between dates IN THE SAME YEAR & MONTH
// Calculates hours between DateTimes ON THE SAME DAY, etc.
long DateTime::intervalIncrement(DateTime& other, Period period) {
  // TODO: Does not account for 1 year between 2000-02-29 and 2001-02-28
  long difference = other.getPeriod(period) - this->getPeriod(period);
  other.add(-difference, period); // will adjust automatically if beyond end of month
  if (difference == 0) return 0;
  if (this->isLeapDay() && other.month() == 2 && other.day() == 28) other.add(1, DateTime::Day);  // Special case for comparing with a leap day
  if (difference > 0) {
    if (*this > other) return difference - 1;
  } else {
    if (*this < other) return difference + 1;
  }
  return difference;
}

byte DateTime::daysAdjusted() const {
  return _daysAdjusted;
}

void DateTime::zeroDaysAdjusted() {
  _daysAdjusted = 0;
}

int DateTime::getPeriod(Period period) const {
  switch (period) {
  case Year:
    return (int)this->year();
    break;
  case Month:
    return (int)this->month();
    break;
  case Day:
    return (int)this->day();
    break;
  case Hour:
    return (int)this->hour();
    break;
  case Minute:
    return (int)this->minute();
    break;
  case Second:
    return (int)this->second();
    break;
  case Millisecond:
    return this->millisecond();
    break;
  default:
    return 0;
  }
}

unsigned long DateTime::totalMilliseconds() const {
  unsigned long result = 0;
  result += millisecond();
  result += _second * MILLISECONDS_PER_SECOND;
  result += _minute * SECONDS_PER_MINUTE * MILLISECONDS_PER_SECOND;
  result += _hour * MINUTES_PER_HOUR * SECONDS_PER_MINUTE * MILLISECONDS_PER_SECOND;
  return result;
}

boolean DateTime::isEarlierThan(const DateTime &other) const {
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

boolean DateTime::isEqualTo(const DateTime &other) const {
  return (this->year() == other.year() &&
          this->month() == other.month() &&
          this->day() == other.day() &&
          this->hour() == other.hour() &&
          this->minute() == other.minute() &&
          this->second() == other.second() &&
          this->millisecond() == other.millisecond());
}

boolean DateTime::operator == (const DateTime &other) const {
  return this->isEqualTo(other);
}

boolean DateTime::operator != (const DateTime &other) const {
  return !this->isEqualTo(other);
}

boolean DateTime::operator < (const DateTime &other) const {
  return this->isEarlierThan(other);
}

boolean DateTime::operator <= (const DateTime &other) const {
  return this->isEarlierThan(other) || this->isEqualTo(other);
}

boolean DateTime::operator > (const DateTime &other) const {
  return other.isEarlierThan(*this);
}

boolean DateTime::operator >= (const DateTime &other) const {
  return other.isEarlierThan(*this) || other.isEqualTo(*this);
}

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

  delete(_stringValue);
  _stringValue = output;
  return *_stringValue;
}

// You would expect this method to be static, but this would cause
// the String object created to be shared across all instances of
// DateTime objects. It looks a little odd to call this 'static'
// function on an object, but determines which object's static
// String the value is attached to.
String& DateTime::monthToString(int month) {
  return getProgMemString(monthNames, monthNameIndex[month]);
}

String& DateTime::monthToShortString() {
  return monthToShortString(_month);
}

// See note on DateTime::monthToString(int month)
String& DateTime::monthToShortString(int month) {
  return getProgMemString(monthNamesShort, (month * 4));
}

String& DateTime::dayOfWeekToString() {
  return dayOfWeekToString(dayOfWeek());
}

// See note on DateTime::monthToString(int month)
String& DateTime::dayOfWeekToString(DayOfWeek day) {
  return getProgMemString(dayNames, dayNameIndex[day]);
}

String& DateTime::dayOfWeekToShortString() {
  return dayOfWeekToShortString(dayOfWeek());
}

// See note on DateTime::monthToString(int month)
String& DateTime::dayOfWeekToShortString(DayOfWeek day) {
  return getProgMemString(dayNamesShort, (day * 4));
}

String& DateTime::getProgMemString(const char *progArray, byte index) {
  delete(_stringValue);
#ifndef ARDUINO // Standard C++ code
  _stringValue = new String(progArray + index);
#else           // Arduino code
  // This function would be far simpler if the String() constructor
  // could accept a pointer to program memory!
  char ramBuffer[10];
  char* progMemCString = (char*)(progArray + (index));
  strcpy_P(ramBuffer, progMemCString);
  output = new String(ramBuffer);
#endif
  return *_stringValue;
}

#ifndef ARDUINO
  char* DateTime::intToString(int value) {
    static char ramBuffer[10];
    sprintf(ramBuffer, "%d", value);
    return ramBuffer;
  }
#endif

int DateTime::parse(char* number, int characters) {
  int result = 0;
  for (int index = 0; index < characters; index++) {
    result *= 10;
    result += parse(*(number + index));
  }
  return result;
}

int DateTime::parse(char number) {
  if (number == ' ') number = '0';
  return number - 48;  // 48 = ASCII code for '0'
}

byte DateTime::monthFromString(char* string) {
  switch (*string) {
    case 'A':
      return (*(++string) == 'p') ? 4 : 8;
      break;
    case 'D':
      return 12;
      break;
    case 'F':
      return 2;
      break;
    case 'J':
      return (*(++string) == 'a') ? 1 : ((*(++string) == 'l') ? 7 : 6);
      return 0;
      break;
    case 'M':
      return (*(string + 2) == 'r') ? 3 : 5;
      break;
    case 'N':
      return 11;
      break;
    case 'O':
      return 10;
      break;
    case 'S':
      return 9;
      break;
  }
  return 0;
}

boolean DateTime::isValid() {
  // all years are valid (0 - 255) = (1900 - 2155)
  if (_month == 0) return false;
  if (_month > MONTHS_PER_YEAR) return false;
  if (_day == 0) return false;
  if (_day > daysInMonth()) return false; // month must be checked prior to calling daysInMonth()
  if (_hour > (HOURS_PER_DAY - 1)) return false;
  if (_minute > (MINUTES_PER_HOUR - 1)) return false;
  if (_second > (SECONDS_PER_MINUTE - 1)) return false;
  if (_millisecond < 0) return false;
  if (_millisecond > (MILLISECONDS_PER_SECOND - 1)) return false;
  return true;
}

byte DateTime::leapDaysInRange(DateTime earlier, DateTime later) {
  byte leapDays = 0;
  int year = earlier.year();
  while(!isLeapYear(year)) year++;
  DateTime leapDayStart = DateTime(year, 2, 29, 0, 0, 0, 0);
  DateTime leapDayEnd = DateTime(year, 3, 1, 0, 0, 0, 0);
  while (earlier <= leapDayStart && leapDayEnd <= later) {
    leapDays++;
    if (leapDayStart.year() == 2152) break;
    if (isLeapYear(leapDayStart.year() + 4)) {
      leapDayStart.add(4, Year);
      leapDayEnd.add(4, Year);
    } else {
      leapDayStart.add(8, Year);
      leapDayEnd.add(8, Year);
    }
  }
  return leapDays;
}

boolean DateTime::isLeapYear(int year) {
  //http://en.wikipedia.org/wiki/Leap_year
  return (year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0));
}
