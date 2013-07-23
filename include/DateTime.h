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

class DateTime
{
  public:
    /* TESTED */ DateTime();
    /* TESTED */ DateTime(int year, byte month, byte day, byte hour, byte minute, byte second, int millisecond);

    /* TESTED */ int year();
    /* TESTED */ byte month();
    /* TESTED */ byte day();
    /* TESTED */ byte hour();
    /* TESTED */ byte minute();
    /* TESTED */ byte second();
    /* TESTED */ int millisecond();

    /* TESTED */ static boolean isLeapYear(int year);

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
