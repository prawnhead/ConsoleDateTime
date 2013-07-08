#ifndef ARDUINO
  #include <iostream>
#endif
#include "DateTime.h"

using namespace std;

int main()
{
  DateTime test;
  cout << test.toString() << endl;
  return 0;
}
