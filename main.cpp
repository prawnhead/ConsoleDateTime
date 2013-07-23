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
    printf("FAILURE of intToString().\n\tExpected: %s\n\tActual:   %s.\n", expected.c_str(), DateTime::intToString(value));
  }
}

void testToString(DateTime actual, String expected) {
  tests++;
  if (expected.compare(actual.toString())) {
    fails++;
    printf("FAILURE of toString().\n\tExpected: %s\n\tActual:   %s.\n", expected.c_str(), actual.toString().c_str());
  }
}

//void testDateTimeValues(int year,
//                        byte month,
//                        byte day,
//                        byte hour,
//                        byte minute,
//                        byte second,
//                        int millisecond,
//                        DateTime actual,
//                        String message) {
//  tests++;
//  if (!(actual.year() == year &&
//        actual.month() == month &&
//        actual.day() == day &&
//        actual.hour() == hour &&
//        actual.minute() == minute &&
//        actual.second() == second &&
//        actual.millisecond() == millisecond)) {
//    fails++;
////    printf("FAIL \t%s\n\tExpected: %d-%02d-%02d %02d:%02d:%02d.%03d\n\tActual:   %s\n", message.c_str(), year, month, day, hour, minute, second, millisecond, actual.toString().c_str());
//  }
//}

int main()
{
  DateTime test;

  // In-range tests
  testIntToString(0, "0");
  testIntToString(1, "1");
  testIntToString(-1, "-1");
  testIntToString(32767, "32767");
  testIntToString(-32768, "-32768");
  // Out-of-range tests
  testIntToString(40000, "-25536");  // wrap around expected
  testIntToString(-40000, "25536");  // wrap around expected

  // Tests must be in-range only as range checking will be added later.
  testToString(DateTime(1900, 1, 1, 0, 0, 0, 0), "1900-01-01 00:00:00.000");  // Earliest possible
  testToString(DateTime(2155, 12, 31, 23, 59, 59, 999), "2155-12-31 23:59:59.999");  // Latest possible
  testToString(DateTime(2013, 7, 23, 11, 1, 34, 935), "2013-07-23 11:01:34.935");  // Random (today)

//  testDateTimeValues(1900, 1, 1, 0, 0, 0, 0, DateTime(), "Default");

  if (tests == 0) cout << "No tests performed." << endl;
  else {
    float passRate = (tests - fails)/(float) tests * 100;
    printf("TEST PASS RATE: %3.2f%%. %d tests.\n", passRate, tests);
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
