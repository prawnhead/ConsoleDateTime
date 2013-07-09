#include "DateTime.h"

#ifndef ARDUINO
  using namespace std;
#endif


DateTime::DateTime()
{
  _year = _hour = _minute = _second = _millisecond = 0;
  _month = _day = 1;
  #ifndef ARDUINO
  cout << F("DateTime constructor") << endl;
  #else
  Serial.println("DateTime constructor");
  #endif
}

DateTime::~DateTime()
{
  #ifndef ARDUINO
  cout << F("DateTime constructor") << endl;
  #else
  Serial.println("DateTime constructor");
  #endif
}

int DateTime::year() const {
  return _year + _epochYear;
}

String& DateTime::toString() {
  //http://arduino.cc/en/Reference/StringObject
  static String* output;
  if (output) delete(output);
  output = new String();
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
  return *output;
}

//// You would expect this method to be static, but this would cause
//// the String object created to be shared across all instances of
//// DateTime objects. It looks a little odd to call this 'static'
//// function on an object, but determines which object's static
//// String the value is attached to.
//String& DateTime::monthToString(int month) {
//  return getProgMemString(monthNames, monthNameIndex[month]);
//}
//
//String& DateTime::monthToShortString() {
//  return monthToShortString(_month);
//}
//
//// See note on DateTime::monthToString(int month)
//String& DateTime::monthToShortString(int month) {
//  return getProgMemString(monthNamesShort, (month * 4));
//}
//
//String& DateTime::dayOfWeekToString() {
//  return dayOfWeekToString(dayOfWeek());
//}
//
//// See note on DateTime::monthToString(int month)
//String& DateTime::dayOfWeekToString(DayOfWeek day) {
//  return getProgMemString(dayNames, dayNameIndex[day]);
//}
//
//String& DateTime::dayOfWeekToShortString() {
//  return dayOfWeekToShortString(dayOfWeek());
//}
//
//// See note on DateTime::monthToString(int month)
//String& DateTime::dayOfWeekToShortString(DayOfWeek day) {
//  return getProgMemString(dayNamesShort, (day * 4));
//}
//
//String& DateTime::getProgMemString(const char *progArray, byte index) {
//#ifndef ARDUINO // Standard C++ code
//  return *(progArray + index);
//#else           // Arduino code
//  // This function would be far simpler if the String() constructor
//  // could accept a pointer to program memory!
//  char ramBuffer[10];
//  char* progMemCString = (char*)(progArray + (index));
//  strcpy_P(ramBuffer, progMemCString);
//  static String* output;
//  delete(output);
//  output = new String(ramBuffer);
//  return *output;
//#endif
//}

#ifndef ARDUINO
  char* DateTime::intToString(int value) {
    static char ramBuffer[10];
    sprintf(ramBuffer, "%d", value);
    return ramBuffer;
  }
#endif

