#ifndef ARDUINO
  #include <iostream>
#endif
#include "DateTime.h"

using namespace std;

int main()
{
  DateTime test;
  cout << test.toString() << endl;
  for (int i = 1; i <= 12; i++) {
    cout << test.monthToString(i) << endl;
  }
  for (int i = 1; i <= 12; i++) {
    cout << test.monthToShortString(i) << endl;
  }
  for (int i = 1; i <= 7; i++) {
    cout << test.dayOfWeekToString((DateTime::DayOfWeek)i) << endl;
  }
  for (int i = 1; i <= 7; i++) {
    cout << test.dayOfWeekToShortString((DateTime::DayOfWeek)i) << endl;
  }
  return 0;
}
