#ifndef ARDUINO
  #include <iostream>
#endif

#include "DateTime.h"

using namespace std;

int tests = 0;
int fails = 0;

void testString(String expected, String actual) {
  tests++;
  if (expected.compare(actual) != 0) {
    fails++;
    cout << "testString() failed. Expected: " << expected << ", actual: " << actual << endl;
  }
}

void testDateTime(DateTime expected, DateTime actual, String message) {
  tests++;
  if (!expected.isEqualTo(actual)) {
    fails++;
    printf("FAIL \t%s\n\tExpected: %s\n\tActual:   %s\n", message.c_str(), expected.toString().c_str(), actual.toString().c_str());
  }
}

int main()
{
  DateTime test;

//  cout << "Test day of week strings (long)" << endl;
//  testString(test.dayOfWeekToString(DateTime::Error), "Error");
//  testString(test.dayOfWeekToString(DateTime::Sunday), "Sunday");
//  testString(test.dayOfWeekToString(DateTime::Monday), "Monday");
//  testString(test.dayOfWeekToString(DateTime::Tuesday), "Tuesday");
//  testString(test.dayOfWeekToString(DateTime::Wednesday), "Wednesday");
//  testString(test.dayOfWeekToString(DateTime::Thursday), "Thursday");
//  testString(test.dayOfWeekToString(DateTime::Friday), "Friday");
//  testString(test.dayOfWeekToString(DateTime::Saturday), "Saturday");
//
//  cout << "Test day of week strings (short)" << endl;
//  testString(test.dayOfWeekToShortString(DateTime::Error), "Err");
//  testString(test.dayOfWeekToShortString(DateTime::Sunday), "Sun");
//  testString(test.dayOfWeekToShortString(DateTime::Monday), "Mon");
//  testString(test.dayOfWeekToShortString(DateTime::Tuesday), "Tue");
//  testString(test.dayOfWeekToShortString(DateTime::Wednesday), "Wed");
//  testString(test.dayOfWeekToShortString(DateTime::Thursday), "Thu");
//  testString(test.dayOfWeekToShortString(DateTime::Friday), "Fri");
//  testString(test.dayOfWeekToShortString(DateTime::Saturday), "Sat");
//
//  cout << "Test month of year strings (long)" << endl;
//  testString(test.monthToString(0), "Error");
//  testString(test.monthToString(1), "January");
//  testString(test.monthToString(2), "February");
//  testString(test.monthToString(3), "March");
//  testString(test.monthToString(4), "April");
//  testString(test.monthToString(5), "May");
//  testString(test.monthToString(6), "June");
//  testString(test.monthToString(7), "July");
//  testString(test.monthToString(8), "August");
//  testString(test.monthToString(9), "September");
//  testString(test.monthToString(10), "October");
//  testString(test.monthToString(11), "November");
//  testString(test.monthToString(12), "December");
//
//  cout << "Test month of year strings (short)" << endl;
//  testString(test.monthToShortString(0), "Err");
//  testString(test.monthToShortString(1), "Jan");
//  testString(test.monthToShortString(2), "Feb");
//  testString(test.monthToShortString(3), "Mar");
//  testString(test.monthToShortString(4), "Apr");
//  testString(test.monthToShortString(5), "May");
//  testString(test.monthToShortString(6), "Jun");
//  testString(test.monthToShortString(7), "Jul");
//  testString(test.monthToShortString(8), "Aug");
//  testString(test.monthToShortString(9), "Sep");
//  testString(test.monthToShortString(10), "Oct");
//  testString(test.monthToShortString(11), "Nov");
//  testString(test.monthToShortString(12), "Dec");
//
//  cout << "Test toString()" << endl;
//  testString(test.toString(), "1900-01-01 00:00:00.000");
//
//  cout << "Test basic DateTime" << endl;
//  testDateTime(DateTime(2000, 1, 1, 0, 0, 0, 0), DateTime(2000, 1, 1, 0, 0, 0, 0), "Basic DateTime");
//
//  cout << "Test add()" << endl;
//  testDateTime(DateTime(2000, 1, 1, 0, 0, 0, 999).add(1, DateTime::Millisecond), DateTime(2000, 1, 1, 0, 0, 1, 0), "Seconds rollover");
//  testDateTime(DateTime(2000, 1, 1, 0, 0, 59, 0).add(1, DateTime::Second), DateTime(2000, 1, 1, 0, 1, 0, 0), "Minutes rollover");
//  testDateTime(DateTime(2000, 1, 1, 0, 59, 0, 0).add(1, DateTime::Minute), DateTime(2000, 1, 1, 1, 0, 0, 0), "Hours rollover");
//  testDateTime(DateTime(2000, 1, 1, 23, 0, 0, 0).add(1, DateTime::Hour), DateTime(2000, 1, 2, 0, 0, 0, 0), "Day rollover");
//  testDateTime(DateTime(2000, 1, 31, 0, 0, 0, 0).add(1, DateTime::Day), DateTime(2000, 2, 1, 0, 0, 0, 0), "Month rollover");
//  testDateTime(DateTime(2000, 12, 1, 0, 0, 0, 0).add(1, DateTime::Month), DateTime(2001, 1, 1, 0, 0, 0, 0), "Year rollover");
//  testDateTime(DateTime(2000, 12, 31, 23, 59, 59, 999).add(1, DateTime::Millisecond), DateTime(2001, 1, 1, 0, 0, 0, 0), "Cascade rollover");

  testDateTime(DateTime(2000, 1, 1, 0, 0, 0, 0).add(-1, DateTime::Millisecond), DateTime(1999, 12, 31, 23, 59, 59, 999), "Subtract a millisecond");
//  testDateTime(DateTime(2000, 1, 1, 0, 0, 0, 0).add(-1, DateTime::Second), DateTime(1999, 12, 31, 23, 59, 59, 000), "Subtract a second");
//  testDateTime(DateTime(2000, 1, 1, 0, 0, 0, 0).add(-1, DateTime::Minute), DateTime(1999, 12, 31, 23, 59, 00, 000), "Subtract a minute");
//  testDateTime(DateTime(2000, 1, 1, 0, 0, 0, 0).add(-1, DateTime::Hour), DateTime(1999, 12, 31, 23, 00, 00, 000), "Subtract an hour");
//  testDateTime(DateTime(2000, 1, 1, 0, 0, 0, 0).add(-1, DateTime::Day), DateTime(1999, 12, 31, 00, 00, 00, 000), "Subtract a day");
//  testDateTime(DateTime(2000, 1, 1, 0, 0, 0, 0).add(-1, DateTime::Month), DateTime(1999, 12, 1, 00, 00, 00, 000), "Subtract a month");
//  testDateTime(DateTime(2000, 1, 1, 0, 0, 0, 0).add(-1, DateTime::Year), DateTime(1999, 1, 1, 00, 00, 00, 000), "Subtract a year");

  cout << "test intervals" << endl; //TODO


  float passRate = (tests - fails)/(float) tests * 100;
  printf("\nTEST PASS RATE: %3.2f%%\n", passRate);
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

  return 0;
}
