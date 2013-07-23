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

#define MIN_YEAR 1900
//#define MAX_YEAR 2155

//const char monthNames[] PROGMEM = "Error\0January\0February\0March\0April\0May\0June\0July\0August\0September\0October\0November\0December";
//const byte monthNameIndex[] = {0, 6, 14, 23, 29, 35, 39, 44, 49, 56, 66, 74, 83};
//const char monthNamesShort[] PROGMEM = "Err\0Jan\0Feb\0Mar\0Apr\0May\0Jun\0Jul\0Aug\0Sep\0Oct\0Nov\0Dec";
//const char dayNames[] PROGMEM = "Error\0Sunday\0Monday\0Tuesday\0Wednesday\0Thursday\0Friday\0Saturday";
//const byte dayNameIndex[] = {0, 6, 13, 20, 28, 38, 47, 54};
//const char dayNamesShort[] PROGMEM = "Err\0Sun\0Mon\0Tue\0Wed\0Thu\0Fri\0Sat";

class DateTime
{
  public:
    DateTime();

    int year();
    byte month();
    byte day();
    byte hour();
    byte minute();
    byte second();
    int millisecond();

#ifndef ARDUINO
    static char* intToString(int value);
#endif

  protected:
    byte _year; // 0-255 represents 1900-2155
    byte _month, _day, _hour, _minute, _second;
    int _millisecond;
  private:
};

#endif // DATETIME_H
