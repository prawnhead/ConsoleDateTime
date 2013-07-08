#ifndef DATETIME_H
#define DATETIME_H
#ifndef ARDUINO
  #include <iostream>
  #include <string>
  typedef uint8_t byte;
  using namespace std;
#endif

class DateTime
{
  public:
    DateTime();
    virtual ~DateTime();
    string toString();
  protected:
  private:
    byte _year, _month, _day, _hour, _minute, _second;
    unsigned int _millisecond;
};

#endif // DATETIME_H
