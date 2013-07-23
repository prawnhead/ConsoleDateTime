#ifndef ARDUINO
  #include <iostream>
#endif

#include "DateTime.h"
#define int int

using namespace std;

int tests = 0;
int fails = 0;

void testIntToString(int value, String expected) {
  tests++;
  if (expected.compare(DateTime::intToString(value))) {
    fails++;
    printf("FAILURE of intToString(). \t Expected: %s. Actual: %s.\n", expected.c_str(), DateTime::intToString(value));
  }
}

void testDateTimeValues(int year,
                        byte month,
                        byte day,
                        byte hour,
                        byte minute,
                        byte second,
                        int millisecond,
                        DateTime actual,
                        String message) {
  tests++;
  if (!(actual.year() == year &&
        actual.month() == month &&
        actual.day() == day &&
        actual.hour() == hour &&
        actual.minute() == minute &&
        actual.second() == second &&
        actual.millisecond() == millisecond)) {
    fails++;
//    printf("FAIL \t%s\n\tExpected: %d-%02d-%02d %02d:%02d:%02d.%03d\n\tActual:   %s\n", message.c_str(), year, month, day, hour, minute, second, millisecond, actual.toString().c_str());
  }
}

int main()
{
  DateTime test;

  testIntToString(0, "0");
  testIntToString(1, "1");
  testIntToString(-1, "-1");
  testIntToString(32767, "32767");
  testIntToString(-32768, "-32768");
  testIntToString(40000, "40000");
  testIntToString(-40000, "-40000");

  //testDateTimeValues(1900, 1, 1, 0, 0, 0, 0, DateTime(), "Default");

  if (tests == 0) cout << "No tests performed." << endl;
  else {
    float passRate = (tests - fails)/(float) tests * 100;
    printf("\nTEST PASS RATE: %3.2f%%. %d tests.\n", passRate, tests);
    if (passRate < 100) {
      cout << endl;
      cout << "  *****   *     * *      **" << endl;
      cout << "  *      * *    * *      **" << endl;
      cout << "  ****  *   *   * *      **" << endl;
      cout << "  *    *******  * *        " << endl;
      cout << "  *   *       * * *****  **" << endl;
      cout << endl;
    }
    else cout << "Pass." << endl;
  }
  return 0;
}
