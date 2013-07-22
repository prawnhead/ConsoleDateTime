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

void testLeapYear(int year, boolean expected) {
  tests++;
  if (DateTime::isLeapYear(year) != expected) {
    fails++;
    printf("isLeapYear() failed for %d.\n", year);
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
    printf("FAIL \t%s\n\tExpected: %d-%02d-%02d %02d:%02d:%02d.%03d\n\tActual:   %s\n", message.c_str(), year, month, day, hour, minute, second, millisecond, actual.toString().c_str());
  }
}

void testDateTime(DateTime expected, DateTime actual, String message) {
  tests++;
  if (!expected.isEqualTo(actual)) {
    fails++;
    printf("FAIL \t%s\n\tExpected: %s\n\tActual:   %s\n", message.c_str(), expected.toString().c_str(), actual.toString().c_str());
  }
}

//String getPeriod(DateTime::Period period) {
//  switch (period) {
//  case DateTime::Millisecond:
//    return "Millisecond";
//    break;
//  case DateTime::Second:
//    return "Second";
//    break;
//  case DateTime::Minute:
//    return "Minute";
//    break;
//  case DateTime::Hour:
//    return "Hour";
//    break;
//  case DateTime::Day:
//    return "Day";
//    break;
//  case DateTime::Month:
//    return "Month";
//    break;
//  case DateTime::Year:
//    return "Year";
//    break;
//  default:
//    return "Error";
//  }
//}
//
//void testIntervalTo(DateTime alpha, DateTime omega, DateTime::Period period, long expected) {
//  tests++;
//  long actual = alpha.intervalTo(omega, period);
//  if (actual != expected) {
//    fails++;
//    printf("FAIL \t%s intervals from %s to %s.\n\tExpected: %ld\n\tActual:   %ld\n", getPeriod(period).c_str(), alpha.toString().c_str(), omega.toString().c_str(), expected, actual);
//  }
//}
//
//void testLeapDaysInRange(DateTime alpha, DateTime omega, byte expected) {
//  tests++;
//  byte actual = DateTime::leapDaysInRange(alpha, omega);
//  if (actual != expected) {
//    fails++;
//    printf("FAIL \tLeap days from %s to %s.\n\tExpected: %d\n\tActual:   %d\n", alpha.toString().c_str(), omega.toString().c_str(), expected, actual);
//  }
//}
//
//void testAdd(DateTime start, DateTime::Period period, int duration, DateTime expected) {
//  tests++;
//  DateTime actual = DateTime(start);
//  actual.add(duration, period);
//  if (actual != expected) {
//    fails++;
//    printf("FAIL \tAdd %d %s to %s\n\tExpected: %s\n\tActual:   %s\n", duration, getPeriod(period).c_str(), start.toString().c_str(), expected.toString().c_str(), actual.toString().c_str());
//  }
//}

int main()
{
  DateTime test;

//  cout << "TEST CONST ARRAYS" << endl;
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

  cout << "TEST CONSTRUCTORS" << endl;
//  cout << "Test default constructor" << endl;
//  testDateTimeValues(1900, 1, 1, 0, 0, 0, 0, DateTime(), "Default (epoch)");
//
//  cout << "Test explicit values constructor" << endl;
//  testDateTimeValues(1900, 1, 1, 0, 0, 0, 0, DateTime(1900, 1, 1, 0, 0, 0, 0), "Earliest date");
//  testDateTimeValues(2155, 12, 31, 23, 59, 59, 999, DateTime(2155, 12, 31, 23, 59, 59, 999), "Last date");
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
//  testDateTimeValues(1900, 1, 1, 0, 0, 0, 0, DateTime(1900, 2, 29, 0, 0, 0, 0), "Leap day in non leap turn of century");
//  testDateTimeValues(1900, 1, 1, 0, 0, 0, 0, DateTime(1901, 2, 29, 0, 0, 0, 0), "Leap day in non leap year");
//  testDateTimeValues(2000, 2, 29, 0, 0, 0, 0, DateTime(2000, 2, 29, 0, 0, 0, 0), "Leap day in leap turn of century");
//  testDateTimeValues(1900, 1, 1, 0, 0, 0, 0, DateTime(2100, 2, 29, 0, 0, 0, 0), "Leap day in non leap turn of century");

  cout << "Test string constructor" << endl;
  // __DATE__ format: Mar 12 2013
  // __TIME__ format: 23:17:51
  testDateTime(DateTime(1900, 1, 1, 0, 0, 0, 0), DateTime("Jan 01 1900", "00:00:00", DateTime::Compiler), "Earliest compiler __DATE__ and __TIME__");
  testDateTime(DateTime(2155, 12, 31, 23, 59, 59, 0), DateTime("Dec 31 2155", "23:59:59", DateTime::Compiler), "Latest compiler __DATE__ and __TIME__");
  testDateTime(DateTime(1900, 1, 1, 0, 0, 0, 0), DateTime("", "", DateTime::Compiler), "Empty strings");
  testDateTime(DateTime(1900, 1, 1, 0, 0, 0, 0), DateTime("Jan 01 1899", "00:00:00", DateTime::Compiler), "Invalid year");
  testDateTime(DateTime(1900, 1, 1, 0, 0, 0, 0), DateTime("Jan 01 2157", "00:00:00", DateTime::Compiler), "Invalid year");
  testDateTime(DateTime(1900, 1, 1, 0, 0, 0, 0), DateTime("Ben 01 1900", "00:00:00", DateTime::Compiler), "Invalid month");
  testDateTime(DateTime(1900, 1, 1, 0, 0, 0, 0), DateTime("Jan 00 1900", "00:00:00", DateTime::Compiler), "Invalid day");
  testDateTime(DateTime(1900, 1, 1, 0, 0, 0, 0), DateTime("Jan 32 1900", "00:00:00", DateTime::Compiler), "Invalid day");
  testDateTime(DateTime(1900, 1, 1, 0, 0, 0, 0), DateTime("Jan 01 1900", "24:00:00", DateTime::Compiler), "Invalid hour");
  testDateTime(DateTime(1900, 1, 1, 0, 0, 0, 0), DateTime("Jan 01 1900", "00:60:00", DateTime::Compiler), "Invalid minutes");
  testDateTime(DateTime(1900, 1, 1, 0, 0, 0, 0), DateTime("Jan 01 1900", "00:00:60", DateTime::Compiler), "Invalid seconds");

//  cout << "TEST FUNCTIONS" << endl;
//  cout << "Test isLeapYear()" << endl;
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

//  cout << "Test toString()" << endl;
//  testString(test.toString(), "1900-01-01 00:00:00.000");
//
//  // Test add()
//  testAdd(DateTime(1996, 2, 29, 0, 0, 0, 0), DateTime::Year, 4, DateTime(2000, 2, 29, 0, 0, 0, 0));

//  // Test DateTime::leapDaysInRange()
//  testLeapDaysInRange(DateTime(1900, 1, 1, 0, 0, 0, 0), DateTime(1900, 1, 1, 0, 0, 0, 0), 0);
//  testLeapDaysInRange(DateTime(1900, 1, 1, 0, 0, 0, 0), DateTime(1901, 1, 1, 0, 0, 0, 0), 0);
//  testLeapDaysInRange(DateTime(1904, 1, 1, 0, 0, 0, 0), DateTime(1904, 12, 31, 0, 0, 0, 0), 1);
//  testLeapDaysInRange(DateTime(1900, 1, 1, 0, 0, 0, 0), DateTime(2000, 1, 1, 0, 0, 0, 0), 24);
//  testLeapDaysInRange(DateTime(1900, 1, 1, 0, 0, 0, 0), DateTime(2155, 1, 1, 0, 0, 0, 0), 62);

//
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
//  // Days
//  // Century periods
//  testIntervalTo(DateTime(2000, 1, 1, 0, 0, 0, 0), DateTime(2000, 1, 1, 0, 0, 0, 0), DateTime::Day, 0);
//  testIntervalTo(DateTime(1900, 1, 1, 0, 0, 0, 0), DateTime(2000, 1, 1, 0, 0, 0, 0), DateTime::Day, 36524);
//  testIntervalTo(DateTime(2000, 1, 1, 0, 0, 0, 0), DateTime(2100, 1, 1, 0, 0, 0, 0), DateTime::Day, 36525);
//  // Leap periods
//  testIntervalTo(DateTime(1900, 1, 1, 0, 0, 0, 0), DateTime(1904, 1, 1, 0, 0, 0, 0), DateTime::Day, 1460);  // 0 leap days
//  testIntervalTo(DateTime(1904, 1, 1, 0, 0, 0, 0), DateTime(1908, 1, 1, 0, 0, 0, 0), DateTime::Day, 1461);  // 1 leap day
//  testIntervalTo(DateTime(1900, 1, 1, 0, 0, 0, 0), DateTime(1912, 1, 1, 0, 0, 0, 0), DateTime::Day, 4382);  // 2 leap days
//  testIntervalTo(DateTime(1999, 1, 1, 0, 0, 0, 0), DateTime(2003, 1, 1, 0, 0, 0, 0), DateTime::Day, 1461);  // 1 millennial leap day
//  testIntervalTo(DateTime(2099, 1, 1, 0, 0, 0, 0), DateTime(2103, 1, 1, 0, 0, 0, 0), DateTime::Day, 1460);  // 0 millennial leap days
//  // Year periods
//  testIntervalTo(DateTime(1901, 1, 1, 0, 0, 0, 0), DateTime(1902, 1, 1, 0, 0, 0, 0), DateTime::Day, 365);  // 0 leap days normal year
//  testIntervalTo(DateTime(1904, 1, 1, 0, 0, 0, 0), DateTime(1905, 1, 1, 0, 0, 0, 0), DateTime::Day, 366);  // 1 leap day, leap year
//  testIntervalTo(DateTime(1900, 1, 1, 0, 0, 0, 0), DateTime(1901, 1, 1, 0, 0, 0, 0), DateTime::Day, 365);  // 0 leap days, century
//  testIntervalTo(DateTime(2000, 1, 1, 0, 0, 0, 0), DateTime(2001, 1, 1, 0, 0, 0, 0), DateTime::Day, 366);  // 1 leap day, century
//  testIntervalTo(DateTime(2100, 1, 1, 0, 0, 0, 0), DateTime(2101, 1, 1, 0, 0, 0, 0), DateTime::Day, 365);  // 0 leap days, century
//  // Partial days
//  testIntervalTo(DateTime(1901, 1, 1, 12, 0, 0, 0), DateTime(1902, 1, 1, 0, 0, 0, 0), DateTime::Day, 364);  // 0 leap days normal year
//  testIntervalTo(DateTime(1904, 1, 1, 12, 0, 0, 0), DateTime(1905, 1, 1, 0, 0, 0, 0), DateTime::Day, 365);  // 1 leap day, leap year
//  testIntervalTo(DateTime(1900, 1, 1, 12, 0, 0, 0), DateTime(1901, 1, 1, 0, 0, 0, 0), DateTime::Day, 364);  // 0 leap days, century
//  testIntervalTo(DateTime(2000, 1, 1, 12, 0, 0, 0), DateTime(2001, 1, 1, 0, 0, 0, 0), DateTime::Day, 365);  // 1 leap day, century
//  testIntervalTo(DateTime(2100, 1, 1, 12, 0, 0, 0), DateTime(2101, 1, 1, 0, 0, 0, 0), DateTime::Day, 364);  // 0 leap days, century

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
