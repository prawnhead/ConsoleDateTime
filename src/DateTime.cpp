#include "DateTime.h"

#ifndef ARDUINO
  using namespace std;
#endif

// PUBLIC FUNCTIONS

DateTime::DateTime() {
  _year = 0;
  _month = 1;
  _day = 1;
  _hour = 0;
  _minute = 0;
  _second = 0;
  _millisecond = 0;
}

int DateTime::year() {
  return MIN_YEAR + _year;
}

byte DateTime::month() {
  return _month;
}

byte DateTime::day() {
  return _day;
}

byte DateTime::hour() {
  return _hour;
}

byte DateTime::minute() {
  return _minute;
}

byte DateTime::second() {
  return _second;
}

int DateTime::millisecond() {
  return _millisecond;
}

// PRIVATE FUNCTIONS

#ifndef ARDUINO
char* DateTime::intToString(int value) {
   static char ramBuffer[10];
   sprintf(ramBuffer, "%d", value);
   return ramBuffer;
 }
#endif
