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
    printf("FAILURE of DateTime values:\t%s\n\tExpected: %d-%02d-%02d %02d:%02d:%02d.%03d\n\tActual:   %s\n", message.c_str(), year, month, day, hour, minute, second, millisecond, actual.toString().c_str());
  }
}

void testString(String expected, String actual) {
  tests++;
  if (expected.compare(actual) != 0) {
    fails++;
    printf("FAILURE in string comparison.\n\tExpected: %s\n\tActual:   %s", expected.c_str(), actual.c_str());
  }
}

void testLeapYear(int year, boolean expected) {
  tests++;
  if (DateTime(year, 1, 1, 0, 0, 0, 0).isLeapYear(year) != expected) {
    fails++;
    printf("FAILURE of isLeapYear() for %d.\n", year);
  }
}

void testDaysInMonth(byte month, int year, byte expected) {
  tests++;
  if (DateTime(year, month, 1, 0, 0, 0, 0).daysInMonth() != expected) {
    fails++;
    printf("FAILURE of daysInMonth() for %d.\n\tExpected: %d\n\tActual:   %d\n", month, expected, DateTime(year, month, 1, 0, 0, 0, 0).daysInMonth());
  }
}

void testGetStatus(DateTime test, DateTime::Status status, boolean expected) {
  tests++;
  if (test.getStatus(status) != expected) {
    fails++;
    printf("FAILURE of getStatus() for %s\n", test.toString().c_str());
  }
}

void testGetAdjustment(DateTime test, byte expected) {
  tests++;
  if (test.getAdjustment() != expected) {
    fails++;
    printf("FAILURE of getAdjustment() for %s. Expected: %d. Actual: %d.\n", test.toString().c_str(), expected, test.getAdjustment());
  }
}

void testDaysInRange(DateTime alpha, DateTime omega, long expected) {
  tests++;
  long days = DateTime::daysInRange(alpha, omega);
  if (days != expected) {
    fails++;
    printf("FAILURE of daysInRange() for %s to %s.\n\tExpected: %d. Actual: %d.\n", alpha.toString().c_str(), omega.toString().c_str(), expected, days);
  }
}

void testDateTime(DateTime test, DateTime expected, String identifier) {
  tests++;
  if (test != expected) {
    fails++;
    printf("FAILURE of %s.\n\tExpected: %s.\n\tActual:   %s.\n", identifier.c_str(), expected.toString().c_str(), test.toString().c_str());
  }
}

void testMonthCarryBorrow(int month, int expectedMonth, int expectedYears) {
  tests++;
  int16_t newMonth = month;
  int years = DateTime::monthCarryBorrow(newMonth);
  if (newMonth != expectedMonth || years != expectedYears) {
    fails++;
    printf("FAILURE of monthCarryBorrow() for %d.\n\tExpected: %d years %d months.\n\tActual:   %d years %d months.\n", month, expectedYears, expectedMonth, years, newMonth);
  }
}

int main()
{
//  testMonthCarryBorrow(1, 1, 0);
//  testMonthCarryBorrow(2, 2, 0);
//  testMonthCarryBorrow(3, 3, 0);
//  testMonthCarryBorrow(4, 4, 0);
//  testMonthCarryBorrow(5, 5, 0);
//  testMonthCarryBorrow(6, 6, 0);
//  testMonthCarryBorrow(7, 7, 0);
//  testMonthCarryBorrow(8, 8, 0);
//  testMonthCarryBorrow(9, 9, 0);
//  testMonthCarryBorrow(10, 10, 0);
//  testMonthCarryBorrow(11, 11, 0);
//  testMonthCarryBorrow(12, 12, 0);
//  testMonthCarryBorrow(13, 1, 1);
//  testMonthCarryBorrow(14, 2, 1);
//  testMonthCarryBorrow(15, 3, 1);
//  testMonthCarryBorrow(16, 4, 1);
//  testMonthCarryBorrow(17, 5, 1);
//  testMonthCarryBorrow(18, 6, 1);
//  testMonthCarryBorrow(19, 7, 1);
//  testMonthCarryBorrow(20, 8, 1);
//  testMonthCarryBorrow(21, 9, 1);
//  testMonthCarryBorrow(22, 10, 1);
//  testMonthCarryBorrow(23, 11, 1);
//  testMonthCarryBorrow(24, 12, 1);
//  testMonthCarryBorrow(25, 1,2);
//  testMonthCarryBorrow(0, 12, -1);
//  testMonthCarryBorrow(-1, 11, -1);
//  testMonthCarryBorrow(-2, 10, -1);
//  testMonthCarryBorrow(-3, 9, -1);
//  testMonthCarryBorrow(-4, 8, -1);
//  testMonthCarryBorrow(-5, 7, -1);
//  testMonthCarryBorrow(-6, 6, -1);
//  testMonthCarryBorrow(-7, 5, -1);
//  testMonthCarryBorrow(-8, 4, -1);
//  testMonthCarryBorrow(-9, 3, -1);
//  testMonthCarryBorrow(-10, 2, -1);
//  testMonthCarryBorrow(-11, 1, -1);

//  testDateTime(DateTime(2000, 1, 1, 0, 0, 0, 0).add(0, DateTime::Millisecond), DateTime(2000, 1, 1, 0, 0, 0, 0), "Add 0 milliseconds");
//  testDateTime(DateTime(2000, 1, 1, 0, 0, 0, 0).add(1, DateTime::Millisecond), DateTime(2000, 1, 1, 0, 0, 0, 1), "Add 1 millisecond");
//  testDateTime(DateTime(2000, 1, 1, 0, 0, 0, 0).add(1500, DateTime::Millisecond), DateTime(2000, 1, 1, 0, 0, 1, 500), "Add 1500 milliseconds");
//  testDateTime(DateTime(2000, 1, 1, 0, 0, 0, 0).add(60000, DateTime::Millisecond), DateTime(2000, 1, 1, 0, 1, 0, 0), "Add 60000 milliseconds");
//  testDateTime(DateTime(2000, 1, 1, 0, 0, 0, 0).add(3600000, DateTime::Millisecond), DateTime(2000, 1, 1, 1, 0, 0, 0), "Add 3600000 milliseconds");
//  testDateTime(DateTime(2000, 1, 1, 0, 0, 0, 0).add(36000000, DateTime::Millisecond), DateTime(2000, 1, 1, 10, 0, 0, 0), "Add 36000000 milliseconds");
//  testDateTime(DateTime(2000, 1, 1, 23, 59, 59, 999).add(-1, DateTime::Millisecond), DateTime(2000, 1, 1, 23, 59, 59, 998), "Subtract 1 millisecond");
//  testDateTime(DateTime(2000, 1, 1, 23, 59, 59, 999).add(-1500, DateTime::Millisecond), DateTime(2000, 1, 1, 23, 59, 58, 499), "Subtract 1500 milliseconds");
//  testDateTime(DateTime(2000, 1, 1, 23, 59, 59, 999).add(-60000, DateTime::Millisecond), DateTime(2000, 1, 1, 23, 58, 59, 999), "Subtract 60000 milliseconds");
//  testDateTime(DateTime(2000, 1, 1, 23, 59, 59, 999).add(-3600000, DateTime::Millisecond), DateTime(2000, 1, 1, 22, 59, 59, 999), "Subtract 3600000 milliseconds");
//  testDateTime(DateTime(2000, 1, 1, 23, 59, 59, 999).add(-36000000, DateTime::Millisecond), DateTime(2000, 1, 1, 13, 59, 59, 999), "Subtract 36000000 milliseconds");
//
//  testDateTime(DateTime(2000, 1, 1, 0, 0, 0, 0).add(0, DateTime::Second), DateTime(2000, 1, 1, 0, 0, 0, 0), "Add 0 seconds");
//  testDateTime(DateTime(2000, 1, 1, 0, 0, 0, 0).add(1, DateTime::Second), DateTime(2000, 1, 1, 0, 0, 1, 0), "Add 1 second");
//  testDateTime(DateTime(2000, 1, 1, 0, 0, 0, 0).add(100, DateTime::Second), DateTime(2000, 1, 1, 0, 1, 40, 0), "Add 100 seconds");
//  testDateTime(DateTime(2000, 1, 1, 0, 0, 0, 0).add(3600, DateTime::Second), DateTime(2000, 1, 1, 1, 0, 0, 0), "Add 3600 seconds");
//  testDateTime(DateTime(2000, 1, 1, 0, 0, 0, 0).add(36000, DateTime::Second), DateTime(2000, 1, 1, 10, 0, 0, 0), "Add 36000 seconds");
//  testDateTime(DateTime(2000, 1, 1, 23, 59, 59, 999).add(-1, DateTime::Second), DateTime(2000, 1, 1, 23, 59, 58, 999), "Subtract 1 second");
//  testDateTime(DateTime(2000, 1, 1, 23, 59, 59, 999).add(-100, DateTime::Second), DateTime(2000, 1, 1, 23, 58, 19, 999), "Subtract 100 seconds");
//  testDateTime(DateTime(2000, 1, 1, 23, 59, 59, 999).add(-3600, DateTime::Second), DateTime(2000, 1, 1, 22, 59, 59, 999), "Subtract 3600 seconds");
//  testDateTime(DateTime(2000, 1, 1, 23, 59, 59, 999).add(-36000, DateTime::Second), DateTime(2000, 1, 1, 13, 59, 59, 999), "Subtract 36000 seconds");

//  // From first of month date
//  testDateTime(DateTime(2000, 1, 1, 0, 0, 0, 0).add(1, DateTime::Minute), DateTime(2000, 1, 1, 0, 1, 0, 0), "Add 1 minute");
//  testDateTime(DateTime(2000, 1, 1, 0, 0, 0, 0).add(1, DateTime::Hour), DateTime(2000, 1, 1, 1, 0, 0, 0), "Add 1 hour");
//  testDateTime(DateTime(2000, 1, 1, 0, 0, 0, 0).add(1, DateTime::Day), DateTime(2000, 1, 2, 0, 0, 0, 0), "Add 1 day");
//  testDateTime(DateTime(2000, 1, 1, 0, 0, 0, 0).add(1, DateTime::Month), DateTime(2000, 2, 1, 0, 0, 0, 0), "Add 1 month");
//  testDateTime(DateTime(2000, 1, 1, 0, 0, 0, 0).add(1, DateTime::Year), DateTime(2001, 1, 1, 0, 0, 0, 0), "Add 1 year");
//
//  // From last in (long) month date
//  testDateTime(DateTime(2000, 1, 31, 0, 0, 0, 0).add(1, DateTime::Day), DateTime(2000, 2, 1, 0, 0, 0, 0), "Add 1 day");
//  testDateTime(DateTime(2000, 1, 31, 0, 0, 0, 0).add(1, DateTime::Month), DateTime(2000, 2, 29, 0, 0, 0, 0), "Add 1 month");  // leap year
//  testDateTime(DateTime(2001, 1, 31, 0, 0, 0, 0).add(1, DateTime::Month), DateTime(2001, 2, 28, 0, 0, 0, 0), "Add 1 month");  // non leap year
//  testDateTime(DateTime(2000, 1, 31, 0, 0, 0, 0).add(1, DateTime::Year), DateTime(2001, 1, 31, 0, 0, 0, 0), "Add 1 year");
//
//  // Leap year testing
//  testDateTime(DateTime(2000, 2, 28, 23, 59, 59, 999).add(1, DateTime::Millisecond), DateTime(2000, 2, 29, 0, 0, 0, 0), "Add 1 milli end of day before leap");
//  testDateTime(DateTime(2000, 2, 29, 23, 59, 59, 999).add(1, DateTime::Millisecond), DateTime(2000, 3, 1, 0, 0, 0, 0), "Add 1 milli end of leap day");
//
//  testDateTime(DateTime(1999, 2, 28, 0, 0, 0, 0).add(365, DateTime::Day), DateTime(2000, 2, 28, 0, 0, 0, 0), "Add 365 days");
//  testDateTime(DateTime(1999, 2, 28, 0, 0, 0, 0).add(1000, DateTime::Day), DateTime(2001, 11, 24, 0, 0, 0, 0), "Add 1000 days");
//  testDateTime(DateTime(1900, 1, 1, 0, 0, 0, 0).add(93500, DateTime::Day), DateTime(2155, 12, 30, 0, 0, 0, 0), "Add 93500 days");

//  // From first of month date
//  testDateTime(DateTime(2000, 1, 1, 0, 0, 0, 0).add(-1, DateTime::Minute), DateTime(1999, 12, 31, 23, 59, 0, 0), "Subtract 1 minute");
//  testDateTime(DateTime(2000, 1, 1, 0, 0, 0, 0).add(-1, DateTime::Hour), DateTime(1999, 12, 31, 23, 0, 0, 0), "Subtract 1 hour");
//  testDateTime(DateTime(2000, 1, 1, 0, 0, 0, 0).add(-1, DateTime::Day), DateTime(1999, 12, 31, 0, 0, 0, 0), "Subtract 1 day");
//  testDateTime(DateTime(2000, 1, 1, 0, 0, 0, 0).add(-1, DateTime::Month), DateTime(1999, 12, 1, 0, 0, 0, 0), "Subtract 1 month");
//  testDateTime(DateTime(2000, 1, 1, 0, 0, 0, 0).add(-1, DateTime::Year), DateTime(1999, 1, 1, 0, 0, 0, 0), "Subtract 1 year");

  // From last in (long) month date
//  testDateTime(DateTime(2000, 2, 1, 0, 0, 0, 0).add(-1, DateTime::Day), DateTime(2000, 1, 31, 0, 0, 0, 0), "Subtract 1 day");
//  testDateTime(DateTime(2000, 2, 29, 0, 0, 0, 0).add(-1, DateTime::Month), DateTime(2000, 1, 29, 0, 0, 0, 0), "Subtract 1 month");  // leap year
//  testDateTime(DateTime(2001, 2, 28, 0, 0, 0, 0).add(-1, DateTime::Month), DateTime(2001, 1, 28, 0, 0, 0, 0), "Subtract 1 month");  // non leap year
//  testDateTime(DateTime(2001, 1, 31, 0, 0, 0, 0).add(-1, DateTime::Year), DateTime(2000, 1, 31, 0, 0, 0, 0), "Subtract 1 year");
//
//  // Leap year testing
//  testDateTime(DateTime(2000, 2, 29, 0, 0, 0, 0).add(-1, DateTime::Millisecond), DateTime(2000, 2, 28, 23, 59, 59, 999), "Subtract 1 milli end of day before leap");
//  testDateTime(DateTime(2000, 3, 1, 0, 0, 0, 0).add(-1, DateTime::Millisecond), DateTime(2000, 2, 29, 23, 59, 59, 999), "Subtract 1 milli end of leap day");
//
//  testDateTime(DateTime(2000, 2, 28, 0, 0, 0, 0).add(-365, DateTime::Day), DateTime(1999, 2, 28, 0, 0, 0, 0), "Subtract 365 days");
//  testDateTime(DateTime(2001, 11, 24, 0, 0, 0, 0).add(-1000, DateTime::Day), DateTime(1999, 2, 28, 0, 0, 0, 0), "Subtract 1000 days");
//  testDateTime(DateTime(2155, 12, 30, 0, 0, 0, 0).add(-93500, DateTime::Day), DateTime(1900, 1, 1, 0, 0, 0, 0), "Subtract 93500 days");

//  testAddOneDay(DateTime(2000, 1, 1, 0, 0, 0, 0), DateTime(2000, 1, 2, 0, 0, 0, 0));
//  testAddOneDay(DateTime(2000, 1, 30, 0, 0, 0, 0), DateTime(2000, 1, 31, 0, 0, 0, 0));
//  testAddOneDay(DateTime(2000, 1, 31, 0, 0, 0, 0), DateTime(2000, 2, 1, 0, 0, 0, 0));
//  testAddOneDay(DateTime(2000, 2, 28, 0, 0, 0, 0), DateTime(2000, 2, 29, 0, 0, 0, 0));
//  testAddOneDay(DateTime(2000, 2, 29, 0, 0, 0, 0), DateTime(2000, 3, 1, 0, 0, 0, 0));
//  testAddOneDay(DateTime(2000, 12, 31, 0, 0, 0, 0), DateTime(2001, 1, 1, 0, 0, 0, 0));

//  DateTime alpha = DateTime(2001, 01, 01, 0, 0, 0, 0);
//  DateTime omega = DateTime(2001, 01, 01, 0, 0, 0, 0);
//  testDaysInRange(alpha, omega, 0);
//  omega = DateTime(2001, 01, 02, 0, 0, 0, 0);
//  testDaysInRange(alpha, omega, 1);
//  omega = DateTime(2001, 02, 01, 0, 0, 0, 0);
//  testDaysInRange(alpha, omega, 31);
//  omega = DateTime(2002, 01, 01, 0, 0, 0, 0);
//  testDaysInRange(alpha, omega, 365);
//  omega = DateTime(2005, 01, 01, 0, 0, 0, 0);
//  testDaysInRange(alpha, omega, 1461);
//  alpha = DateTime(1900, 01, 01, 0, 0, 0, 0);
//  omega = DateTime(1904, 01, 01, 0, 0, 0, 0);
//  testDaysInRange(alpha, omega, 1460);
//  alpha = DateTime(2000, 01, 01, 0, 0, 0, 0);
//  omega = DateTime(2004, 01, 01, 0, 0, 0, 0);
//  testDaysInRange(alpha, omega, 1461);
//  alpha = DateTime(1900, 01, 01, 0, 0, 0, 0);
//  omega = DateTime(2000, 01, 01, 0, 0, 0, 0);
//  testDaysInRange(alpha, omega, 36524);
//  alpha = DateTime(2000, 01, 01, 0, 0, 0, 0);
//  omega = DateTime(2100, 01, 01, 0, 0, 0, 0);
//  testDaysInRange(alpha, omega, 36525);



//  DateTime test;
//
//  // Tests appear in the order of dependency. Functions with no dependencies are tested first,
//  // then functions depending on already-tested functions.
//  // See blog post on arduinoetcetera.blogspot.com.au
//
//  printf("Testing: intToString()\n");
//  // In-range tests
//  testIntToString(0, "0");
//  testIntToString(1, "1");
//  testIntToString(-1, "-1");
//  testIntToString(32767, "32767");
//  testIntToString(-32768, "-32768");
//  // Out-of-range tests
//  testIntToString(40000, "-25536");  // wrap around expected
//  testIntToString(-40000, "25536");  // wrap around expected
//
//  printf("Testing: toString()\n");
//  // Tests must be in-range only as range checking will be added later.
//  testToString(DateTime(1900, 1, 1, 0, 0, 0, 0), "1900-01-01 00:00:00.000");  // Earliest possible
//  testToString(DateTime(2155, 12, 31, 23, 59, 59, 999), "2155-12-31 23:59:59.999");  // Latest possible
//  testToString(DateTime(2013, 7, 23, 11, 1, 34, 935), "2013-07-23 11:01:34.935");  // Random (today)
//
//  printf("Testing: Constructors plus year(), month(), day(), hour(), minute(), second(), millisecond()\n");
//  testDateTimeValues(1900, 1, 1, 0, 0, 0, 0, DateTime(), "Default, earliest");
//  testDateTimeValues(1900, 1, 1, 0, 0, 0, 0, DateTime(1900, 1, 1, 0, 0, 0, 0), "Earliest");
//  testDateTimeValues(2155, 12, 31, 23, 59, 59, 999, DateTime(2155, 12, 31, 23, 59, 59, 999), "Latest");
//  testDateTimeValues(1901, 2, 3, 4, 5, 6, 7, DateTime(1901, 2, 3, 4, 5, 6, 7), "Discrete values");
//
//  printf("Testing: isLeapYear()\n");
//  testLeapYear(1900, false);
//  testLeapYear(1901, false);
//  testLeapYear(1902, false);
//  testLeapYear(1903, false);
//  testLeapYear(1904, true);
//  testLeapYear(1905, false);
//  testLeapYear(1906, false);
//  testLeapYear(1907, false);
//  testLeapYear(1908, true);
//  testLeapYear(1909, false);
//  testLeapYear(1910, false);
//  testLeapYear(1911, false);
//  testLeapYear(1912, true);
//  testLeapYear(1913, false);
//  testLeapYear(1914, false);
//  testLeapYear(1915, false);
//  testLeapYear(1916, true);
//  testLeapYear(1917, false);
//  testLeapYear(1918, false);
//  testLeapYear(1919, false);
//  testLeapYear(1920, true);
//  testLeapYear(1921, false);
//  testLeapYear(1922, false);
//  testLeapYear(1923, false);
//  testLeapYear(1924, true);
//  testLeapYear(1925, false);
//  testLeapYear(1926, false);
//  testLeapYear(1927, false);
//  testLeapYear(1928, true);
//  testLeapYear(1929, false);
//  testLeapYear(1930, false);
//  testLeapYear(1931, false);
//  testLeapYear(1932, true);
//  testLeapYear(1933, false);
//  testLeapYear(1934, false);
//  testLeapYear(1935, false);
//  testLeapYear(1936, true);
//  testLeapYear(1937, false);
//  testLeapYear(1938, false);
//  testLeapYear(1939, false);
//  testLeapYear(1940, true);
//  testLeapYear(1941, false);
//  testLeapYear(1942, false);
//  testLeapYear(1943, false);
//  testLeapYear(1944, true);
//  testLeapYear(1945, false);
//  testLeapYear(1946, false);
//  testLeapYear(1947, false);
//  testLeapYear(1948, true);
//  testLeapYear(1949, false);
//  testLeapYear(1950, false);
//  testLeapYear(1951, false);
//  testLeapYear(1952, true);
//  testLeapYear(1953, false);
//  testLeapYear(1954, false);
//  testLeapYear(1955, false);
//  testLeapYear(1956, true);
//  testLeapYear(1957, false);
//  testLeapYear(1958, false);
//  testLeapYear(1959, false);
//  testLeapYear(1960, true);
//  testLeapYear(1961, false);
//  testLeapYear(1962, false);
//  testLeapYear(1963, false);
//  testLeapYear(1964, true);
//  testLeapYear(1965, false);
//  testLeapYear(1966, false);
//  testLeapYear(1967, false);
//  testLeapYear(1968, true);
//  testLeapYear(1969, false);
//  testLeapYear(1970, false);
//  testLeapYear(1971, false);
//  testLeapYear(1972, true);
//  testLeapYear(1973, false);
//  testLeapYear(1974, false);
//  testLeapYear(1975, false);
//  testLeapYear(1976, true);
//  testLeapYear(1977, false);
//  testLeapYear(1978, false);
//  testLeapYear(1979, false);
//  testLeapYear(1980, true);
//  testLeapYear(1981, false);
//  testLeapYear(1982, false);
//  testLeapYear(1983, false);
//  testLeapYear(1984, true);
//  testLeapYear(1985, false);
//  testLeapYear(1986, false);
//  testLeapYear(1987, false);
//  testLeapYear(1988, true);
//  testLeapYear(1989, false);
//  testLeapYear(1990, false);
//  testLeapYear(1991, false);
//  testLeapYear(1992, true);
//  testLeapYear(1993, false);
//  testLeapYear(1994, false);
//  testLeapYear(1995, false);
//  testLeapYear(1996, true);
//  testLeapYear(1997, false);
//  testLeapYear(1998, false);
//  testLeapYear(1999, false);
//  testLeapYear(2000, true);
//  testLeapYear(2001, false);
//  testLeapYear(2002, false);
//  testLeapYear(2003, false);
//  testLeapYear(2004, true);
//  testLeapYear(2005, false);
//  testLeapYear(2006, false);
//  testLeapYear(2007, false);
//  testLeapYear(2008, true);
//  testLeapYear(2009, false);
//  testLeapYear(2010, false);
//  testLeapYear(2011, false);
//  testLeapYear(2012, true);
//  testLeapYear(2013, false);
//  testLeapYear(2014, false);
//  testLeapYear(2015, false);
//  testLeapYear(2016, true);
//  testLeapYear(2017, false);
//  testLeapYear(2018, false);
//  testLeapYear(2019, false);
//  testLeapYear(2020, true);
//  testLeapYear(2021, false);
//  testLeapYear(2022, false);
//  testLeapYear(2023, false);
//  testLeapYear(2024, true);
//  testLeapYear(2025, false);
//  testLeapYear(2026, false);
//  testLeapYear(2027, false);
//  testLeapYear(2028, true);
//  testLeapYear(2029, false);
//  testLeapYear(2030, false);
//  testLeapYear(2031, false);
//  testLeapYear(2032, true);
//  testLeapYear(2033, false);
//  testLeapYear(2034, false);
//  testLeapYear(2035, false);
//  testLeapYear(2036, true);
//  testLeapYear(2037, false);
//  testLeapYear(2038, false);
//  testLeapYear(2039, false);
//  testLeapYear(2040, true);
//  testLeapYear(2041, false);
//  testLeapYear(2042, false);
//  testLeapYear(2043, false);
//  testLeapYear(2044, true);
//  testLeapYear(2045, false);
//  testLeapYear(2046, false);
//  testLeapYear(2047, false);
//  testLeapYear(2048, true);
//  testLeapYear(2049, false);
//  testLeapYear(2050, false);
//  testLeapYear(2051, false);
//  testLeapYear(2052, true);
//  testLeapYear(2053, false);
//  testLeapYear(2054, false);
//  testLeapYear(2055, false);
//  testLeapYear(2056, true);
//  testLeapYear(2057, false);
//  testLeapYear(2058, false);
//  testLeapYear(2059, false);
//  testLeapYear(2060, true);
//  testLeapYear(2061, false);
//  testLeapYear(2062, false);
//  testLeapYear(2063, false);
//  testLeapYear(2064, true);
//  testLeapYear(2065, false);
//  testLeapYear(2066, false);
//  testLeapYear(2067, false);
//  testLeapYear(2068, true);
//  testLeapYear(2069, false);
//  testLeapYear(2070, false);
//  testLeapYear(2071, false);
//  testLeapYear(2072, true);
//  testLeapYear(2073, false);
//  testLeapYear(2074, false);
//  testLeapYear(2075, false);
//  testLeapYear(2076, true);
//  testLeapYear(2077, false);
//  testLeapYear(2078, false);
//  testLeapYear(2079, false);
//  testLeapYear(2080, true);
//  testLeapYear(2081, false);
//  testLeapYear(2082, false);
//  testLeapYear(2083, false);
//  testLeapYear(2084, true);
//  testLeapYear(2085, false);
//  testLeapYear(2086, false);
//  testLeapYear(2087, false);
//  testLeapYear(2088, true);
//  testLeapYear(2089, false);
//  testLeapYear(2090, false);
//  testLeapYear(2091, false);
//  testLeapYear(2092, true);
//  testLeapYear(2093, false);
//  testLeapYear(2094, false);
//  testLeapYear(2095, false);
//  testLeapYear(2096, true);
//  testLeapYear(2097, false);
//  testLeapYear(2098, false);
//  testLeapYear(2099, false);
//  testLeapYear(2100, false);
//  testLeapYear(2101, false);
//  testLeapYear(2102, false);
//  testLeapYear(2103, false);
//  testLeapYear(2104, true);
//  testLeapYear(2105, false);
//  testLeapYear(2106, false);
//  testLeapYear(2107, false);
//  testLeapYear(2108, true);
//  testLeapYear(2109, false);
//  testLeapYear(2110, false);
//  testLeapYear(2111, false);
//  testLeapYear(2112, true);
//  testLeapYear(2113, false);
//  testLeapYear(2114, false);
//  testLeapYear(2115, false);
//  testLeapYear(2116, true);
//  testLeapYear(2117, false);
//  testLeapYear(2118, false);
//  testLeapYear(2119, false);
//  testLeapYear(2120, true);
//  testLeapYear(2121, false);
//  testLeapYear(2122, false);
//  testLeapYear(2123, false);
//  testLeapYear(2124, true);
//  testLeapYear(2125, false);
//  testLeapYear(2126, false);
//  testLeapYear(2127, false);
//  testLeapYear(2128, true);
//  testLeapYear(2129, false);
//  testLeapYear(2130, false);
//  testLeapYear(2131, false);
//  testLeapYear(2132, true);
//  testLeapYear(2133, false);
//  testLeapYear(2134, false);
//  testLeapYear(2135, false);
//  testLeapYear(2136, true);
//  testLeapYear(2137, false);
//  testLeapYear(2138, false);
//  testLeapYear(2139, false);
//  testLeapYear(2140, true);
//  testLeapYear(2141, false);
//  testLeapYear(2142, false);
//  testLeapYear(2143, false);
//  testLeapYear(2144, true);
//  testLeapYear(2145, false);
//  testLeapYear(2146, false);
//  testLeapYear(2147, false);
//  testLeapYear(2148, true);
//  testLeapYear(2149, false);
//  testLeapYear(2150, false);
//  testLeapYear(2151, false);
//  testLeapYear(2152, true);
//  testLeapYear(2153, false);
//  testLeapYear(2154, false);
//  testLeapYear(2155, false);
//
//  printf("Testing: daysInMonth()\n");
//  testDaysInMonth(1, 1999, 31);
//  testDaysInMonth(2, 1999, 28); // non leap year
//  testDaysInMonth(2, 1996, 29); // normal leap year
//  testDaysInMonth(2, 1900, 28); // century non leap year
//  testDaysInMonth(2, 2000, 29); // century leap year
//  testDaysInMonth(3, 1999, 31);
//  testDaysInMonth(4, 1999, 30);
//  testDaysInMonth(5, 1999, 31);
//  testDaysInMonth(6, 1999, 30);
//  testDaysInMonth(7, 1999, 31);
//  testDaysInMonth(8, 1999, 31);
//  testDaysInMonth(9, 1999, 30);
//  testDaysInMonth(10, 1999, 31);
//  testDaysInMonth(11, 1999, 30);
//  testDaysInMonth(12, 1999, 31);
//
//  printf("Testing: getStatus() & setStatus()\n");
//  test = DateTime();  // default is valid
//  testGetStatus(test, DateTime::Valid, true);
//  testGetStatus(test, DateTime::Overflow, false);
//  test.add(300, DateTime::Year);  // will cause year overflow
//  testGetStatus(test, DateTime::Valid, false);
//  testGetStatus(test, DateTime::Overflow, true);
//
//  printf("Testing: leapDaysInRange()\n");
//  DateTime alpha;
//  DateTime omega;
//  alpha = DateTime(2004, 1, 1, 0, 0, 0, 0);
//  omega = DateTime(2004, 1, 1, 0, 0, 0, 0);
//  testLeapDaysInRange(alpha, omega, 0); // Zero day range
//  omega = DateTime(2004, 3, 1, 0, 0, 0, 0);
//  testLeapDaysInRange(alpha, omega, 1); // Only 2004 counts
//  omega = DateTime(2008, 3, 1, 0, 0, 0, 0);
//  testLeapDaysInRange(alpha, omega, 2); // Counts 2004, 2008
//  alpha = DateTime(2004, 2, 29, 0, 0, 0, 0);
//  testLeapDaysInRange(alpha, omega, 2); // Counts 2004, 2008
//  alpha = DateTime(1900, 1, 1, 0, 0, 0, 0);
//  omega = DateTime(1904, 1, 1, 0, 0, 0, 0);
//  testLeapDaysInRange(alpha, omega, 0); // 1900 does not count
//  alpha = DateTime(1904, 2, 29, 0, 0, 0, 0);
//  omega = DateTime(1904, 3, 1, 0, 0, 0, 0);
//  testLeapDaysInRange(alpha, omega, 1); // Exactly one whole leap day
//  alpha = DateTime(1900, 1, 1, 0, 0, 0, 0);
//  omega = DateTime(2000, 12, 31, 0, 0, 0, 0);
//  testLeapDaysInRange(alpha, omega, 25);  // Leap years 1904-2000 (25)
//  alpha = DateTime(1904, 2, 29, 12, 0, 0, 0);
//  omega = DateTime(1912, 2, 29, 12, 0, 0, 0);
//  testLeapDaysInRange(alpha, omega, 1); // Only 1908 counts
//
//  printf("Testing: getAdjustment() & setAdjustment()\n"); // TODO: Write tests
//
//  printf("Testing: add()\n"); // TODO: Complete tests
//  test = DateTime(2000, 2, 29, 0, 0, 0, 0);
//  test.add(1, DateTime::Year);
//  testDateTimeValues(2001, 2, 28, 0, 0, 0, 0, test, "1 year from leap day");
//  testGetAdjustment(test, 1);
//  test = DateTime(2000, 1, 31, 0, 0, 0, 0);
//  test.add(1, DateTime::Month);
//  testDateTimeValues(2000, 2, 29, 0, 0, 0, 0, test, "1 month from Jan 31 on leap year");
//  testGetAdjustment(test, 2);
//  test = DateTime(2001, 1, 31, 0, 0, 0, 0);
//  test.add(1, DateTime::Month);
//  testDateTimeValues(2001, 2, 28, 0, 0, 0, 0, test, "1 month from Jan 31 on non leap year");
//  testGetAdjustment(test, 3);

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
