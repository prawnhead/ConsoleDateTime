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

void testDateTimeValues(int year, byte month, byte day, byte hour, byte minute, byte second, int millisecond, DateTime actual, String message) {
  tests++;
  if (!(actual.year() == year &&
        actual.month() == month &&
        actual.day() == day &&
        actual.hour() == hour &&
        actual.minute() == minute &&
        actual.second() == second &&
        actual.millisecond() == millisecond)) {
    fails++;
    printf("FAIL \t%s\n\tExpected: %d-%02d-%02d %02d:%02d:%02d.%03d\n\tActual:   %s\n", message.c_str(), year, month, day, hour, minute, second, millisecond, actual.toString().c_str());
  }
}

String getPeriod(DateTime::Period period) {
  switch (period) {
  case DateTime::Millisecond:
    return "Millisecond";
    break;
  case DateTime::Second:
    return "Second";
    break;
  case DateTime::Minute:
    return "Minute";
    break;
  case DateTime::Hour:
    return "Hour";
    break;
  case DateTime::Day:
    return "Day";
    break;
  case DateTime::Month:
    return "Month";
    break;
  case DateTime::Year:
    return "Year";
    break;
  default:
    return "Error";
  }
}

void testIntervalTo(DateTime alpha, DateTime omega, DateTime::Period period, long expected) {
  tests++;
  long actual = alpha.intervalTo(omega, period);
  if (actual != expected) {
    fails++;
    printf("FAIL \t%s intervals from %s to %s.\n\tExpected: %ld\n\tActual:   %ld\n", getPeriod(period).c_str(), alpha.toString().c_str(), omega.toString().c_str(), expected, actual);
  }
}

void testLeapDaysInRange(DateTime alpha, DateTime omega, byte expected) {
  tests++;
  byte actual = DateTime::leapDaysInRange(alpha, omega);
  if (actual != expected) {
    fails++;
    printf("FAIL \tLeap days from %s to %s.\n\tExpected: %d\n\tActual:   %d\n", alpha.toString().c_str(), omega.toString().c_str(), expected, actual);
  }
}

void testAdd(DateTime start, DateTime::Period period, int duration, DateTime expected) {
  tests++;
  DateTime actual = DateTime(start);
  actual.add(duration, period);
  if (actual != expected) {
    fails++;
    printf("FAIL \tAdd %d %s to %s\n\tExpected: %s\n\tActual:   %s\n", duration, getPeriod(period).c_str(), start.toString().c_str(), expected.toString().c_str(), actual.toString().c_str());
  }
}

int main()
{
  DateTime test;

  // Test add()
//  testAdd(DateTime(1996, 2, 29, 0, 0, 0, 0), DateTime::Year, 4, DateTime(2000, 2, 29, 0, 0, 0, 0));

//  // Test DateTime::leapDaysInRange()
//  testLeapDaysInRange(DateTime(1900, 1, 1, 0, 0, 0, 0), DateTime(1900, 1, 1, 0, 0, 0, 0), 0);
//  testLeapDaysInRange(DateTime(1900, 1, 1, 0, 0, 0, 0), DateTime(1901, 1, 1, 0, 0, 0, 0), 0);
//  testLeapDaysInRange(DateTime(1904, 1, 1, 0, 0, 0, 0), DateTime(1904, 12, 31, 0, 0, 0, 0), 1);
//  testLeapDaysInRange(DateTime(1900, 1, 1, 0, 0, 0, 0), DateTime(2000, 1, 1, 0, 0, 0, 0), 24);
//  testLeapDaysInRange(DateTime(1900, 1, 1, 0, 0, 0, 0), DateTime(2155, 1, 1, 0, 0, 0, 0), 62);
//
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
//  cout << "Test constructors" << endl;
//  testDateTimeValues(1900, 1, 1, 0, 0, 0, 0, DateTime(), "Default (epoch)");
//  testDateTimeValues(1900, 1, 1, 0, 0, 0, 0, DateTime(1900, 1, 1, 0, 0, 0, 0), "Earliest date");
//  testDateTimeValues(2155, 12, 31, 23, 59, 59, 999, DateTime(2155, 12, 31, 23, 59, 59, 999), "Latest date");
//  testDateTimeValues(1900, 1, 1, 0, 0, 0, 0, DateTime(1800, 1, 1, 0, 0, 0, 0), "Underrange year");
//  testDateTimeValues(1900, 1, 1, 0, 0, 0, 0, DateTime(2156, 1, 1, 0, 0, 0, 0), "Overrange year");
//  testDateTimeValues(1900, 1, 1, 0, 0, 0, 0, DateTime(2000, 0, 1, 0, 0, 0, 0), "Underrange month");
//  testDateTimeValues(1900, 1, 1, 0, 0, 0, 0, DateTime(2000, 13, 1, 0, 0, 0, 0), "Overrange month");
//  testDateTimeValues(1900, 1, 1, 0, 0, 0, 0, DateTime(2000, 1, 0, 0, 0, 0, 0), "Underrange day");
//  testDateTimeValues(1900, 1, 1, 0, 0, 0, 0, DateTime(2000, 1, 32, 0, 0, 0, 0), "Overrange day");
//  testDateTimeValues(1900, 1, 1, 0, 0, 0, 0, DateTime(2000, 1, 1, 24, 0, 0, 0), "Overrange hour");
//  testDateTimeValues(1900, 1, 1, 0, 0, 0, 0, DateTime(2000, 1, 1, 0, 60, 0, 0), "Overrange minute");
//  testDateTimeValues(1900, 1, 1, 0, 0, 0, 0, DateTime(2000, 1, 1, 0, 0, 60, 0), "Overrange second");
//  testDateTimeValues(1900, 1, 1, 0, 0, 0, 0, DateTime(2000, 1, 1, 0, 0, 0, 1000), "Overrange millisecond");
//
//  // __DATE__ format: Mar 12 2013
//  // __TIME__ format: 23:17:51
//  testDateTime(DateTime(1900, 1, 1, 0, 0, 0, 0), DateTime("Jan 01 1900", "00:00:00", DateTime::Compiler), "Earliest compiler __DATE__ and __TIME__");
//  testDateTime(DateTime(2155, 12, 31, 23, 59, 59, 0), DateTime("Dec 31 2155", "23:59:59", DateTime::Compiler), "Latest compiler __DATE__ and __TIME__");
//
//  cout << "Test add()" << endl;
//  testDateTime(DateTime(2000, 1, 1, 0, 0, 0, 999).add(1, DateTime::Millisecond), DateTime(2000, 1, 1, 0, 0, 1, 0), "Seconds rollover");
//  testDateTime(DateTime(2000, 1, 1, 0, 0, 59, 0).add(1, DateTime::Second), DateTime(2000, 1, 1, 0, 1, 0, 0), "Minutes rollover");
//  testDateTime(DateTime(2000, 1, 1, 0, 59, 0, 0).add(1, DateTime::Minute), DateTime(2000, 1, 1, 1, 0, 0, 0), "Hours rollover");
//  testDateTime(DateTime(2000, 1, 1, 23, 0, 0, 0).add(1, DateTime::Hour), DateTime(2000, 1, 2, 0, 0, 0, 0), "Day rollover");
//  testDateTime(DateTime(2000, 1, 31, 0, 0, 0, 0).add(1, DateTime::Day), DateTime(2000, 2, 1, 0, 0, 0, 0), "Month rollover");
//  testDateTime(DateTime(2000, 12, 1, 0, 0, 0, 0).add(1, DateTime::Month), DateTime(2001, 1, 1, 0, 0, 0, 0), "Year rollover");
//  testDateTime(DateTime(2000, 12, 31, 23, 59, 59, 999).add(1, DateTime::Millisecond), DateTime(2001, 1, 1, 0, 0, 0, 0), "Cascade rollover");
//
//  testDateTime(DateTime(2000, 1, 1, 0, 0, 0, 0).add(-1, DateTime::Millisecond), DateTime(1999, 12, 31, 23, 59, 59, 999), "Subtract a millisecond");
//  testDateTime(DateTime(2000, 1, 1, 0, 0, 0, 0).add(-1, DateTime::Second), DateTime(1999, 12, 31, 23, 59, 59, 000), "Subtract a second");
//  testDateTime(DateTime(2000, 1, 1, 0, 0, 0, 0).add(-1, DateTime::Minute), DateTime(1999, 12, 31, 23, 59, 00, 000), "Subtract a minute");
//  testDateTime(DateTime(2000, 1, 1, 0, 0, 0, 0).add(-1, DateTime::Hour), DateTime(1999, 12, 31, 23, 00, 00, 000), "Subtract an hour");
//  testDateTime(DateTime(2000, 1, 1, 0, 0, 0, 0).add(-1, DateTime::Day), DateTime(1999, 12, 31, 00, 00, 00, 000), "Subtract a day");
//  testDateTime(DateTime(2000, 1, 1, 0, 0, 0, 0).add(-1, DateTime::Month), DateTime(1999, 12, 1, 00, 00, 00, 000), "Subtract a month");
//  testDateTime(DateTime(2000, 1, 1, 0, 0, 0, 0).add(-1, DateTime::Year), DateTime(1999, 1, 1, 00, 00, 00, 000), "Subtract a year");
//
//  cout << "Test leap years" << endl;
//  testDateTime(DateTime(1995, 2, 28, 23, 59, 59, 999).add(1, DateTime::Millisecond), DateTime(1995, 3, 1, 0, 0, 0, 0), "Non leap year 28th Feb -> 1st Mar");
//  testDateTime(DateTime(1996, 2, 28, 23, 59, 59, 999).add(1, DateTime::Millisecond), DateTime(1996, 2, 29, 0, 0, 0, 0), "Standard leap year 28th Feb -> 29th Feb");
//  testDateTime(DateTime(1900, 2, 28, 23, 59, 59, 999).add(1, DateTime::Millisecond), DateTime(1900, 3, 1, 0, 0, 0, 0), "Century non leap year 28th Feb -> 1st Mar");
//  testDateTime(DateTime(2000, 2, 28, 23, 59, 59, 999).add(1, DateTime::Millisecond), DateTime(2000, 2, 29, 0, 0, 0, 0), "Century leap year 28th Feb -> 29th Feb");
//  testDateTime(DateTime(1995, 3, 1, 0, 0, 0, 0).add(-1, DateTime::Millisecond), DateTime(1995, 2, 28, 23, 59, 59, 999), "Non leap year 28th Feb <- 1st Mar");
//  testDateTime(DateTime(1996, 3, 1, 0, 0, 0, 0).add(-1, DateTime::Millisecond), DateTime(1996, 2, 29, 23, 59, 59, 999), "Standard leap year 29th Feb <- 1st Mar");
//  testDateTime(DateTime(1900, 3, 1, 0, 0, 0, 0).add(-1, DateTime::Millisecond), DateTime(1900, 2, 28, 23, 59, 59, 999), "Century non leap year 28th Feb <- 1st Mar");
//  testDateTime(DateTime(2000, 3, 1, 0, 0, 0, 0).add(-1, DateTime::Millisecond), DateTime(2000, 2, 29, 23, 59, 59, 999), "Century leap year 29th Feb <- 1st Mar");
//
//  cout << "Test intervals" << endl; // TODO: Complete intervalTo tests
//  // Years - zero
//  testIntervalTo(DateTime(2000, 1, 1, 0, 0, 0, 0), DateTime(2000, 1, 1, 0, 0, 0, 0), DateTime::Year, 0);
//
//  // Years - positive
//  testIntervalTo(DateTime(2000, 1, 1, 0, 0, 0, 0), DateTime(2001, 1, 1, 0, 0, 0, 0), DateTime::Year, 1);
//  testIntervalTo(DateTime(2000, 1, 1, 0, 0, 0, 0), DateTime(2002, 1, 1, 0, 0, 0, 0), DateTime::Year, 2);
//  testIntervalTo(DateTime(2000, 1, 1, 0, 0, 0, 1), DateTime(2001, 1, 1, 0, 0, 0, 0), DateTime::Year, 0);
//  testIntervalTo(DateTime(2000, 1, 1, 0, 0, 0, 1), DateTime(2002, 1, 1, 0, 0, 0, 0), DateTime::Year, 1);
//  testIntervalTo(DateTime(1900, 1, 1, 0, 0, 0, 0), DateTime(2000, 1, 1, 0, 0, 0, 0), DateTime::Year, 100);
//  testIntervalTo(DateTime(1900, 1, 1, 0, 0, 0, 0), DateTime(2155, 12, 31, 23, 59, 59, 999), DateTime::Year, 255);
//
//  // Years - negative
//  testIntervalTo(DateTime(2001, 1, 1, 0, 0, 0, 0), DateTime(2000, 1, 1, 0, 0, 0, 0), DateTime::Year, -1);
//  testIntervalTo(DateTime(2002, 1, 1, 0, 0, 0, 0), DateTime(2000, 1, 1, 0, 0, 0, 0), DateTime::Year, -2);
//  testIntervalTo(DateTime(2001, 1, 1, 0, 0, 0, 0), DateTime(2000, 1, 1, 0, 0, 0, 1), DateTime::Year, 0);
//  testIntervalTo(DateTime(2002, 1, 1, 0, 0, 0, 0), DateTime(2000, 1, 1, 0, 0, 0, 1), DateTime::Year, -1);
//  testIntervalTo(DateTime(2000, 1, 1, 0, 0, 0, 0), DateTime(1900, 1, 1, 0, 0, 0, 0), DateTime::Year, -100);
//  testIntervalTo(DateTime(2155, 12, 31, 23, 59, 59, 999), DateTime(1900, 1, 1, 0, 0, 0, 0), DateTime::Year, -255);
//
//  // Years - leap years
//  testIntervalTo(DateTime(2000, 2, 29, 0, 0, 0, 0), DateTime(2001, 2, 28, 0, 0, 0, 0), DateTime::Year, 1);
//  testIntervalTo(DateTime(2000, 2, 29, 0, 0, 0, 0), DateTime(1999, 2, 28, 0, 0, 0, 0), DateTime::Year, -1);
//
//  // Months - zero
//  testIntervalTo(DateTime(2000, 1, 1, 0, 0, 0, 0), DateTime(2000, 1, 1, 0, 0, 0, 0), DateTime::Month, 0);
//
//  // Months - positive
//  testIntervalTo(DateTime(2000, 1, 1, 0, 0, 0, 0), DateTime(2000, 2, 1, 0, 0, 0, 0), DateTime::Month, 1);
//  testIntervalTo(DateTime(2000, 1, 1, 0, 0, 0, 0), DateTime(2000, 3, 1, 0, 0, 0, 0), DateTime::Month, 2);
//  testIntervalTo(DateTime(2000, 1, 1, 0, 0, 0, 0), DateTime(2001, 1, 1, 0, 0, 0, 0), DateTime::Month, 12);
//  testIntervalTo(DateTime(1900, 1, 1, 0, 0, 0, 0), DateTime(2000, 1, 1, 0, 0, 0, 0), DateTime::Month, 1200);
//  testIntervalTo(DateTime(1900, 1, 1, 0, 0, 0, 0), DateTime(2155, 12, 31, 23, 59, 59, 999), DateTime::Month, 3071);
//
//  // Months - negative
//  testIntervalTo(DateTime(2000, 1, 1, 0, 0, 0, 0), DateTime(1999, 12, 1, 0, 0, 0, 0), DateTime::Month, -1);
//  testIntervalTo(DateTime(2000, 1, 1, 0, 0, 0, 0), DateTime(1999, 11, 1, 0, 0, 0, 0), DateTime::Month, -2);
//  testIntervalTo(DateTime(2000, 1, 1, 0, 0, 0, 0), DateTime(1999, 1, 1, 0, 0, 0, 0), DateTime::Month, -12);
//  testIntervalTo(DateTime(2000, 1, 1, 0, 0, 0, 0), DateTime(1900, 1, 1, 0, 0, 0, 0), DateTime::Month, -1200);
//  testIntervalTo(DateTime(2155, 12, 31, 23, 59, 59, 999), DateTime(1900, 1, 1, 0, 0, 0, 0), DateTime::Month, -3071);
//
  // Days
  // Century periods
  testIntervalTo(DateTime(2000, 1, 1, 0, 0, 0, 0), DateTime(2000, 1, 1, 0, 0, 0, 0), DateTime::Day, 0);
  testIntervalTo(DateTime(1900, 1, 1, 0, 0, 0, 0), DateTime(2000, 1, 1, 0, 0, 0, 0), DateTime::Day, 36524);
  testIntervalTo(DateTime(2000, 1, 1, 0, 0, 0, 0), DateTime(2100, 1, 1, 0, 0, 0, 0), DateTime::Day, 36525);
  // Leap periods
  testIntervalTo(DateTime(1900, 1, 1, 0, 0, 0, 0), DateTime(1904, 1, 1, 0, 0, 0, 0), DateTime::Day, 1460);  // 0 leap days
  testIntervalTo(DateTime(1904, 1, 1, 0, 0, 0, 0), DateTime(1908, 1, 1, 0, 0, 0, 0), DateTime::Day, 1461);  // 1 leap day
  testIntervalTo(DateTime(1900, 1, 1, 0, 0, 0, 0), DateTime(1912, 1, 1, 0, 0, 0, 0), DateTime::Day, 4382);  // 2 leap days
  testIntervalTo(DateTime(1999, 1, 1, 0, 0, 0, 0), DateTime(2003, 1, 1, 0, 0, 0, 0), DateTime::Day, 1461);  // 1 millennial leap day
  testIntervalTo(DateTime(2099, 1, 1, 0, 0, 0, 0), DateTime(2103, 1, 1, 0, 0, 0, 0), DateTime::Day, 1460);  // 0 millennial leap days
  // Year periods
  testIntervalTo(DateTime(1901, 1, 1, 0, 0, 0, 0), DateTime(1902, 1, 1, 0, 0, 0, 0), DateTime::Day, 365);  // 0 leap days normal year
  testIntervalTo(DateTime(1904, 1, 1, 0, 0, 0, 0), DateTime(1905, 1, 1, 0, 0, 0, 0), DateTime::Day, 366);  // 1 leap day, leap year
  testIntervalTo(DateTime(1900, 1, 1, 0, 0, 0, 0), DateTime(1901, 1, 1, 0, 0, 0, 0), DateTime::Day, 365);  // 0 leap days, century
  testIntervalTo(DateTime(2000, 1, 1, 0, 0, 0, 0), DateTime(2001, 1, 1, 0, 0, 0, 0), DateTime::Day, 366);  // 1 leap day, century
  testIntervalTo(DateTime(2100, 1, 1, 0, 0, 0, 0), DateTime(2101, 1, 1, 0, 0, 0, 0), DateTime::Day, 365);  // 0 leap days, century

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

  return 0;
}
