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
  _string = 0;
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

#ifndef ARDUINO
char* DateTime::intToString(int value) {
   static char ramBuffer[10];
   sprintf(ramBuffer, "%d", value);
   return ramBuffer;
 }
#endif

// PRIVATE FUNCTIONS
