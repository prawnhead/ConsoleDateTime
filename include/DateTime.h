#ifndef DATETIME_H
#define DATETIME_H
#ifndef ARDUINO
  #include <iostream>
  #include <string>
  using namespace std;
  typedef uint8_t byte;
  typedef string String;
#else
  #include <Arduino.h>
#endif

class DateTime
{
  public:
    DateTime();
    virtual ~DateTime();
    String toString();
  protected:
  private:
    byte _year, _month, _day, _hour, _minute, _second;
    unsigned int _millisecond;
};

#endif // DATETIME_H
