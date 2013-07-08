#include "DateTime.h"

#ifndef ARDUINO
  using namespace std;
#endif


DateTime::DateTime()
{
  #ifndef ARDUINO
  cout << "DateTime constructor" << endl;
  #else
  Serial.println("DateTime constructor");
  #endif
}

DateTime::~DateTime()
{
  #ifndef ARDUINO
  cout << "DateTime constructor" << endl;
  #else
  Serial.println("DateTime constructor");
  #endif
}
