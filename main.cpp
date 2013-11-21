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

void testIsLeapYear(int year, boolean expected) {
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

void testDaysInYear(int year, int expected) {
	tests++;
	if (DateTime(year, 1, 1, 0, 0, 0, 0).daysInYear() != expected) {
		fails++;
		printf("FAILURE of daysInYear() for %d.\n\tExpected: %d\n\tActual:   %d\n", year, expected, DateTime(year, 1, 1, 0, 0, 0, 0).daysInYear());
	}
}

//void testGetStatus(DateTime test, DateTime::Status status, boolean expected) {
//  tests++;
//  if (test.getStatus(status) != expected) {
//    fails++;
//    printf("FAILURE of getStatus() for %s\n", test.toString().c_str());
//  }
//}
//
//void testGetAdjustment(DateTime test, byte expected) {
//  tests++;
//  if (test.getAdjustment() != expected) {
//    fails++;
//    printf("FAILURE of getAdjustment() for %s. Expected: %d. Actual: %d.\n", test.toString().c_str(), expected, test.getAdjustment());
//  }
//}

//void testDaysInRange(DateTime alpha, DateTime omega, long expected) {
//	tests++;
//	long days = DateTime::daysInRange(alpha, omega);
//	if (days != expected) {
//		fails++;
//		printf("FAILURE of daysInRange() for %s to %s.\n\tExpected: %d. Actual: %d.\n", alpha.toString().c_str(), omega.toString().c_str(), expected, days);
//	}
//}

void testDateTime(DateTime test, DateTime expected, String identifier) {
	tests++;
	if (test != expected || !test.isValid() || test.getStatus(DateTime::Overflow)) {
		fails++;
		printf("FAILURE of %s.\n\tExpected: %s.\n\tActual:   %s.\n", identifier.c_str(), expected.toString().c_str(), test.toString().c_str());
	}
}

void testInvalidDateTime(DateTime test, boolean expectedOverflow) {
	DateTime epoch = DateTime(1900, 1, 1, 0, 0, 0, 0);
	tests++;
	if (test != epoch || test.getStatus(DateTime::Overflow) != expectedOverflow) {
		fails++;
		if (expectedOverflow == test.getStatus(DateTime::Overflow)) printf("FAILURE of %s.\n\tExpected epoch DateTime.\n", test.toString().c_str());
		else printf("FAILURE of %s.\n\tExpected epoch DateTime with overflow.\n", test.toString().c_str());
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

void testAddByte(byte value, long interval, int limit, byte expectedValue, long expectedInterval) {
	tests++;
	byte actualValue = value;
	long actualInterval = interval;
	DateTime::add(actualValue, actualInterval, (int16_t)limit);
	if (actualValue != expectedValue || actualInterval != expectedInterval) {
		fails++;
		printf("FAILURE of add(%d, %ld, %d).\n\tValue expected:    %d.\n\t      Actual:      %d\n\tInterval expected: %ld.\n\t      Actual:      %ld\n", \
				value, interval, limit, expectedValue, actualValue, expectedInterval, actualInterval);
	}
}

void testGetAdjustment(DateTime value, byte expectedAdjustment) {
	tests++;
	if (value.getAdjustment() != expectedAdjustment) {
		fails++;
		printf("FAILURE of getAdjustment() for %s.\n\tExpected: %d.\n\t  Actual: %d\n", value.toString().c_str(), expectedAdjustment, value.getAdjustment());
	}
}

int main() {

//  TESTING FUNCTIONS WITH NO DEPENDENCIES
	printf("Testing: isLeapYear()\n");
	testIsLeapYear(1900, false);
	testIsLeapYear(1901, false);
	testIsLeapYear(1902, false);
	testIsLeapYear(1903, false);
	testIsLeapYear(1904, true);
	testIsLeapYear(1905, false);
	testIsLeapYear(1906, false);
	testIsLeapYear(1907, false);
	testIsLeapYear(1908, true);
	testIsLeapYear(1909, false);
	testIsLeapYear(1910, false);
	testIsLeapYear(1911, false);
	testIsLeapYear(1912, true);
	testIsLeapYear(1913, false);
	testIsLeapYear(1914, false);
	testIsLeapYear(1915, false);
	testIsLeapYear(1916, true);
	testIsLeapYear(1917, false);
	testIsLeapYear(1918, false);
	testIsLeapYear(1919, false);
	testIsLeapYear(1920, true);
	testIsLeapYear(1921, false);
	testIsLeapYear(1922, false);
	testIsLeapYear(1923, false);
	testIsLeapYear(1924, true);
	testIsLeapYear(1925, false);
	testIsLeapYear(1926, false);
	testIsLeapYear(1927, false);
	testIsLeapYear(1928, true);
	testIsLeapYear(1929, false);
	testIsLeapYear(1930, false);
	testIsLeapYear(1931, false);
	testIsLeapYear(1932, true);
	testIsLeapYear(1933, false);
	testIsLeapYear(1934, false);
	testIsLeapYear(1935, false);
	testIsLeapYear(1936, true);
	testIsLeapYear(1937, false);
	testIsLeapYear(1938, false);
	testIsLeapYear(1939, false);
	testIsLeapYear(1940, true);
	testIsLeapYear(1941, false);
	testIsLeapYear(1942, false);
	testIsLeapYear(1943, false);
	testIsLeapYear(1944, true);
	testIsLeapYear(1945, false);
	testIsLeapYear(1946, false);
	testIsLeapYear(1947, false);
	testIsLeapYear(1948, true);
	testIsLeapYear(1949, false);
	testIsLeapYear(1950, false);
	testIsLeapYear(1951, false);
	testIsLeapYear(1952, true);
	testIsLeapYear(1953, false);
	testIsLeapYear(1954, false);
	testIsLeapYear(1955, false);
	testIsLeapYear(1956, true);
	testIsLeapYear(1957, false);
	testIsLeapYear(1958, false);
	testIsLeapYear(1959, false);
	testIsLeapYear(1960, true);
	testIsLeapYear(1961, false);
	testIsLeapYear(1962, false);
	testIsLeapYear(1963, false);
	testIsLeapYear(1964, true);
	testIsLeapYear(1965, false);
	testIsLeapYear(1966, false);
	testIsLeapYear(1967, false);
	testIsLeapYear(1968, true);
	testIsLeapYear(1969, false);
	testIsLeapYear(1970, false);
	testIsLeapYear(1971, false);
	testIsLeapYear(1972, true);
	testIsLeapYear(1973, false);
	testIsLeapYear(1974, false);
	testIsLeapYear(1975, false);
	testIsLeapYear(1976, true);
	testIsLeapYear(1977, false);
	testIsLeapYear(1978, false);
	testIsLeapYear(1979, false);
	testIsLeapYear(1980, true);
	testIsLeapYear(1981, false);
	testIsLeapYear(1982, false);
	testIsLeapYear(1983, false);
	testIsLeapYear(1984, true);
	testIsLeapYear(1985, false);
	testIsLeapYear(1986, false);
	testIsLeapYear(1987, false);
	testIsLeapYear(1988, true);
	testIsLeapYear(1989, false);
	testIsLeapYear(1990, false);
	testIsLeapYear(1991, false);
	testIsLeapYear(1992, true);
	testIsLeapYear(1993, false);
	testIsLeapYear(1994, false);
	testIsLeapYear(1995, false);
	testIsLeapYear(1996, true);
	testIsLeapYear(1997, false);
	testIsLeapYear(1998, false);
	testIsLeapYear(1999, false);
	testIsLeapYear(2000, true);
	testIsLeapYear(2001, false);
	testIsLeapYear(2002, false);
	testIsLeapYear(2003, false);
	testIsLeapYear(2004, true);
	testIsLeapYear(2005, false);
	testIsLeapYear(2006, false);
	testIsLeapYear(2007, false);
	testIsLeapYear(2008, true);
	testIsLeapYear(2009, false);
	testIsLeapYear(2010, false);
	testIsLeapYear(2011, false);
	testIsLeapYear(2012, true);
	testIsLeapYear(2013, false);
	testIsLeapYear(2014, false);
	testIsLeapYear(2015, false);
	testIsLeapYear(2016, true);
	testIsLeapYear(2017, false);
	testIsLeapYear(2018, false);
	testIsLeapYear(2019, false);
	testIsLeapYear(2020, true);
	testIsLeapYear(2021, false);
	testIsLeapYear(2022, false);
	testIsLeapYear(2023, false);
	testIsLeapYear(2024, true);
	testIsLeapYear(2025, false);
	testIsLeapYear(2026, false);
	testIsLeapYear(2027, false);
	testIsLeapYear(2028, true);
	testIsLeapYear(2029, false);
	testIsLeapYear(2030, false);
	testIsLeapYear(2031, false);
	testIsLeapYear(2032, true);
	testIsLeapYear(2033, false);
	testIsLeapYear(2034, false);
	testIsLeapYear(2035, false);
	testIsLeapYear(2036, true);
	testIsLeapYear(2037, false);
	testIsLeapYear(2038, false);
	testIsLeapYear(2039, false);
	testIsLeapYear(2040, true);
	testIsLeapYear(2041, false);
	testIsLeapYear(2042, false);
	testIsLeapYear(2043, false);
	testIsLeapYear(2044, true);
	testIsLeapYear(2045, false);
	testIsLeapYear(2046, false);
	testIsLeapYear(2047, false);
	testIsLeapYear(2048, true);
	testIsLeapYear(2049, false);
	testIsLeapYear(2050, false);
	testIsLeapYear(2051, false);
	testIsLeapYear(2052, true);
	testIsLeapYear(2053, false);
	testIsLeapYear(2054, false);
	testIsLeapYear(2055, false);
	testIsLeapYear(2056, true);
	testIsLeapYear(2057, false);
	testIsLeapYear(2058, false);
	testIsLeapYear(2059, false);
	testIsLeapYear(2060, true);
	testIsLeapYear(2061, false);
	testIsLeapYear(2062, false);
	testIsLeapYear(2063, false);
	testIsLeapYear(2064, true);
	testIsLeapYear(2065, false);
	testIsLeapYear(2066, false);
	testIsLeapYear(2067, false);
	testIsLeapYear(2068, true);
	testIsLeapYear(2069, false);
	testIsLeapYear(2070, false);
	testIsLeapYear(2071, false);
	testIsLeapYear(2072, true);
	testIsLeapYear(2073, false);
	testIsLeapYear(2074, false);
	testIsLeapYear(2075, false);
	testIsLeapYear(2076, true);
	testIsLeapYear(2077, false);
	testIsLeapYear(2078, false);
	testIsLeapYear(2079, false);
	testIsLeapYear(2080, true);
	testIsLeapYear(2081, false);
	testIsLeapYear(2082, false);
	testIsLeapYear(2083, false);
	testIsLeapYear(2084, true);
	testIsLeapYear(2085, false);
	testIsLeapYear(2086, false);
	testIsLeapYear(2087, false);
	testIsLeapYear(2088, true);
	testIsLeapYear(2089, false);
	testIsLeapYear(2090, false);
	testIsLeapYear(2091, false);
	testIsLeapYear(2092, true);
	testIsLeapYear(2093, false);
	testIsLeapYear(2094, false);
	testIsLeapYear(2095, false);
	testIsLeapYear(2096, true);
	testIsLeapYear(2097, false);
	testIsLeapYear(2098, false);
	testIsLeapYear(2099, false);
	testIsLeapYear(2100, false);
	testIsLeapYear(2101, false);
	testIsLeapYear(2102, false);
	testIsLeapYear(2103, false);
	testIsLeapYear(2104, true);
	testIsLeapYear(2105, false);
	testIsLeapYear(2106, false);
	testIsLeapYear(2107, false);
	testIsLeapYear(2108, true);
	testIsLeapYear(2109, false);
	testIsLeapYear(2110, false);
	testIsLeapYear(2111, false);
	testIsLeapYear(2112, true);
	testIsLeapYear(2113, false);
	testIsLeapYear(2114, false);
	testIsLeapYear(2115, false);
	testIsLeapYear(2116, true);
	testIsLeapYear(2117, false);
	testIsLeapYear(2118, false);
	testIsLeapYear(2119, false);
	testIsLeapYear(2120, true);
	testIsLeapYear(2121, false);
	testIsLeapYear(2122, false);
	testIsLeapYear(2123, false);
	testIsLeapYear(2124, true);
	testIsLeapYear(2125, false);
	testIsLeapYear(2126, false);
	testIsLeapYear(2127, false);
	testIsLeapYear(2128, true);
	testIsLeapYear(2129, false);
	testIsLeapYear(2130, false);
	testIsLeapYear(2131, false);
	testIsLeapYear(2132, true);
	testIsLeapYear(2133, false);
	testIsLeapYear(2134, false);
	testIsLeapYear(2135, false);
	testIsLeapYear(2136, true);
	testIsLeapYear(2137, false);
	testIsLeapYear(2138, false);
	testIsLeapYear(2139, false);
	testIsLeapYear(2140, true);
	testIsLeapYear(2141, false);
	testIsLeapYear(2142, false);
	testIsLeapYear(2143, false);
	testIsLeapYear(2144, true);
	testIsLeapYear(2145, false);
	testIsLeapYear(2146, false);
	testIsLeapYear(2147, false);
	testIsLeapYear(2148, true);
	testIsLeapYear(2149, false);
	testIsLeapYear(2150, false);
	testIsLeapYear(2151, false);
	testIsLeapYear(2152, true);
	testIsLeapYear(2153, false);
	testIsLeapYear(2154, false);
	testIsLeapYear(2155, false);
	printf("Testing: daysInMonth()\n");
	testDaysInMonth(1, 1999, 31);
	testDaysInMonth(2, 1999, 28); // non leap year
	testDaysInMonth(2, 1996, 29); // normal leap year
	testDaysInMonth(2, 1900, 28); // century non leap year
	testDaysInMonth(2, 2000, 29); // century leap year
	testDaysInMonth(3, 1999, 31);
	testDaysInMonth(4, 1999, 30);
	testDaysInMonth(5, 1999, 31);
	testDaysInMonth(6, 1999, 30);
	testDaysInMonth(7, 1999, 31);
	testDaysInMonth(8, 1999, 31);
	testDaysInMonth(9, 1999, 30);
	testDaysInMonth(10, 1999, 31);
	testDaysInMonth(11, 1999, 30);
	testDaysInMonth(12, 1999, 31);
	printf("Testing: daysInYear()\n");
	testDaysInYear(1900, 365);
	testDaysInYear(1901, 365);
	testDaysInYear(1904, 366);
	testDaysInYear(1999, 365);
	testDaysInYear(2000, 366);
	testDaysInYear(2100, 365);

	printf("Testing: intToString()\n");
	// In-range tests
	testIntToString(0, "0");
	testIntToString(1, "1");
	testIntToString(-1, "-1");
	testIntToString(32767, "32767");
	testIntToString(-32768, "-32768");
	// Out-of-range tests
	testIntToString(40000, "-25536");  // wrap around expected
	testIntToString(-40000, "25536");  // wrap around expected

	printf("Testing: toString()\n");
	// Tests must be in-range only as range checking will be added later.
	testToString(DateTime(1900, 1, 1, 0, 0, 0, 0), "1900-01-01 00:00:00.000");  // Earliest possible
	testToString(DateTime(2155, 12, 31, 23, 59, 59, 999), "2155-12-31 23:59:59.999");  // Latest possible
	testToString(DateTime(2013, 7, 23, 11, 1, 34, 935), "2013-07-23 11:01:34.935");  // Random (today)
	testToString(DateTime(1000, 0, 0, 100, 100, 100, 10000), "8888-88-88 88:88:88.888");  // Invalid date

	printf("Testing: add()\n");
	testAddByte(0, 0, 24, 0, 0);
	testAddByte(23, 0, 24, 23, 0);
	testAddByte(0, 23, 24, 23, 0);
	testAddByte(10, 13, 24, 23, 0);
	testAddByte(10, 14, 24, 0, 1);
	testAddByte(100, 0, 24, 4, 4);
	testAddByte(0, 100, 24, 4, 4);
	testAddByte(100, 100, 24, 8, 8);

	testAddByte(0, -1, 24, 23, -1);
	testAddByte(0, -23, 24, 1, -1);
	testAddByte(0, -100, 24, 20, -5);

	printf("Testing: monthCarryBorrow()\n");
	testMonthCarryBorrow(1, 1, 0);
	testMonthCarryBorrow(2, 2, 0);
	testMonthCarryBorrow(3, 3, 0);
	testMonthCarryBorrow(4, 4, 0);
	testMonthCarryBorrow(5, 5, 0);
	testMonthCarryBorrow(6, 6, 0);
	testMonthCarryBorrow(7, 7, 0);
	testMonthCarryBorrow(8, 8, 0);
	testMonthCarryBorrow(9, 9, 0);
	testMonthCarryBorrow(10, 10, 0);
	testMonthCarryBorrow(11, 11, 0);
	testMonthCarryBorrow(12, 12, 0);
	testMonthCarryBorrow(13, 1, 1);
	testMonthCarryBorrow(14, 2, 1);
	testMonthCarryBorrow(15, 3, 1);
	testMonthCarryBorrow(16, 4, 1);
	testMonthCarryBorrow(17, 5, 1);
	testMonthCarryBorrow(18, 6, 1);
	testMonthCarryBorrow(19, 7, 1);
	testMonthCarryBorrow(20, 8, 1);
	testMonthCarryBorrow(21, 9, 1);
	testMonthCarryBorrow(22, 10, 1);
	testMonthCarryBorrow(23, 11, 1);
	testMonthCarryBorrow(24, 12, 1);
	testMonthCarryBorrow(25, 1,2);
	testMonthCarryBorrow(0, 12, -1);
	testMonthCarryBorrow(-1, 11, -1);
	testMonthCarryBorrow(-2, 10, -1);
	testMonthCarryBorrow(-3, 9, -1);
	testMonthCarryBorrow(-4, 8, -1);
	testMonthCarryBorrow(-5, 7, -1);
	testMonthCarryBorrow(-6, 6, -1);
	testMonthCarryBorrow(-7, 5, -1);
	testMonthCarryBorrow(-8, 4, -1);
	testMonthCarryBorrow(-9, 3, -1);
	testMonthCarryBorrow(-10, 2, -1);
	testMonthCarryBorrow(-11, 1, -1);

// TESTING CONSTRUCTORS
	printf("Testing: Constructors plus setEpoch(), setStatus(), getStatus(), checkValid(), overflowed()\n year(), month(), day(), hour(), minute(), second(), millisecond()\n");
	// Test create valid with default constructor
	testDateTimeValues(1900, 1, 1, 0, 0, 0, 0, DateTime(), "Default, earliest");
	// Test create valid with constructor
	testDateTimeValues(1900, 1, 1, 0, 0, 0, 0, DateTime(1900, 1, 1, 0, 0, 0, 0), "Earliest");
	testDateTimeValues(2155, 12, 31, 23, 59, 59, 999, DateTime(2155, 12, 31, 23, 59, 59, 999), "Latest");
	testDateTimeValues(1901, 2, 3, 4, 5, 6, 7, DateTime(1901, 2, 3, 4, 5, 6, 7), "Discrete values");
	// Test create invalid with constructor
	testInvalidDateTime(DateTime(1899, 12, 31, 23, 59, 59, 999), true); // just below earliest valid
	testInvalidDateTime(DateTime(2156, 1, 1, 0, 0, 0, 0), true);        // just after last valid
	testInvalidDateTime(DateTime(10000, 1, 1, 0, 0, 0, 0), true);       // bad year
	testInvalidDateTime(DateTime(2000, 0, 1, 0, 0, 0, 0), false);       // bad month
	testInvalidDateTime(DateTime(2000, 13, 1, 0, 0, 0, 0), false);      // bad month
	testInvalidDateTime(DateTime(2000, 1, 0, 0, 0, 0, 0), false);       // bad day
	testInvalidDateTime(DateTime(2000, 1, 32, 0, 0, 0, 0), false);      // bad day
	testInvalidDateTime(DateTime(2000, 1, 1, 24, 0, 0, 0), false);      // bad hour
	testInvalidDateTime(DateTime(2000, 1, 1, 0, 60, 0, 0), false);      // bad minute
	testInvalidDateTime(DateTime(2000, 1, 1, 0, 0, 60, 0), false);      // bad second
	testInvalidDateTime(DateTime(2000, 1, 1, 0, 0, 0, 1000), false);    // bad millisecond
	// Create valid leap days
	testDateTime(DateTime(1904, 2, 29, 0, 0, 0, 0), DateTime(1904, 2, 29, 0, 0, 0, 0), "1904 leap day");
	testDateTime(DateTime(1996, 2, 29, 0, 0, 0, 0), DateTime(1996, 2, 29, 0, 0, 0, 0), "1996 leap day");
	testDateTime(DateTime(2000, 2, 29, 0, 0, 0, 0), DateTime(2000, 2, 29, 0, 0, 0, 0), "2000 leap day");
	// Test create invalid leap days
	testInvalidDateTime(DateTime(1900, 2, 29, 0, 0, 0, 0), false);
	testInvalidDateTime(DateTime(1901, 2, 29, 0, 0, 0, 0), false);
	testInvalidDateTime(DateTime(2100, 2, 29, 0, 0, 0, 0), false);
// TESING add()
	// Test overflow invalidates DateTime objects, overflow by only 1ms in each case
	testInvalidDateTime(DateTime(2155, 1, 1, 0, 0, 0, 0).add(1, DateTime::Year), true);
	testInvalidDateTime(DateTime(2155, 12, 1, 0, 0, 0, 0).add(1, DateTime::Month), true);
	testInvalidDateTime(DateTime(2155, 12, 31, 0, 0, 0, 0).add(1, DateTime::Day), true);
	testInvalidDateTime(DateTime(2155, 12, 31, 23, 0, 0, 0).add(1, DateTime::Hour), true);
	testInvalidDateTime(DateTime(2155, 12, 31, 23, 59, 0, 0).add(1, DateTime::Minute), true);
	testInvalidDateTime(DateTime(2155, 12, 31, 23, 59, 59, 0).add(1, DateTime::Second), true);
	testInvalidDateTime(DateTime(2155, 12, 31, 23, 59, 59, 999).add(1, DateTime::Millisecond), true);
	testInvalidDateTime(DateTime(1900, 12, 31, 23, 59, 59, 999).add(-1, DateTime::Year), true);
	testInvalidDateTime(DateTime(1900, 1, 31, 23, 59, 59, 999).add(-1, DateTime::Month), true);
	testInvalidDateTime(DateTime(1900, 1, 1, 23, 59, 59, 999).add(-1, DateTime::Day), true);
	testInvalidDateTime(DateTime(1900, 1, 1, 0, 59, 59, 999).add(-1, DateTime::Hour), true);
	testInvalidDateTime(DateTime(1900, 1, 1, 0, 0, 59, 999).add(-1, DateTime::Minute), true);
	testInvalidDateTime(DateTime(1900, 1, 1, 0, 0, 0, 999).add(-1, DateTime::Second), true);
	testInvalidDateTime(DateTime(1900, 1, 1, 0, 0, 0, 0).add(-1, DateTime::Millisecond), true);
	// Add zero to all periods, use random in-range dates
	testDateTime(DateTime(2113, 7, 12, 15, 56, 34, 364).add(0, DateTime::Millisecond), DateTime(2113, 7, 12, 15, 56, 34, 364), "Add 0 milliseconds");
	testDateTime(DateTime(1933, 3, 9, 9, 56, 33, 125).add(0, DateTime::Second), DateTime(1933, 3, 9, 9, 56, 33, 125), "Add 0 seconds");
	testDateTime(DateTime(1952, 12, 3, 4, 42, 36, 936).add(0, DateTime::Minute), DateTime(1952, 12, 3, 4, 42, 36, 936), "Add 0 minutes");
	testDateTime(DateTime(2017, 4, 3, 6, 30, 15, 906).add(0, DateTime::Hour), DateTime(2017, 4, 3, 6, 30, 15, 906), "Add 0 hours");
	testDateTime(DateTime(2046, 9, 31, 4, 2, 28, 495).add(0, DateTime::Day), DateTime(2046, 9, 31, 4, 2, 28, 495), "Add 0 days");
	testDateTime(DateTime(2105, 8, 5, 0, 57, 59, 253).add(0, DateTime::Month), DateTime(2105, 8, 5, 0, 57, 59, 253), "Add 0 months");
	testDateTime(DateTime(2110, 4, 6, 17, 50, 54, 599).add(0, DateTime::Year), DateTime(2110, 4, 6, 17, 50, 54, 599), "Add 0 years");
	// Increment individual periods
	testDateTime(DateTime(2016, 6, 14, 11, 33, 26, 884).add(1, DateTime::Millisecond), DateTime(2016, 6, 14, 11, 33, 26, 885), "Increment milliseconds");
	testDateTime(DateTime(2043, 8, 29, 4, 46, 0, 674).add(1, DateTime::Second), DateTime(2043, 8, 29, 4, 46, 1, 674), "Increment seconds");
	testDateTime(DateTime(2018, 5, 1, 20, 16, 14, 5).add(1, DateTime::Minute), DateTime(2018, 5, 1, 20, 17, 14, 5), "Increment minutes");
	testDateTime(DateTime(1927, 12, 20, 10, 23, 53, 293).add(1, DateTime::Hour), DateTime(1927, 12, 20, 11, 23, 53, 293), "Increment hours");
	testDateTime(DateTime(2021, 3, 6, 22, 39, 4, 4).add(1, DateTime::Day), DateTime(2021, 3, 7, 22, 39, 4, 4), "Increment days");
	testDateTime(DateTime(1987, 6, 25, 2, 25, 7, 106).add(1, DateTime::Month), DateTime(1987, 7, 25, 2, 25, 7, 106), "Increment months");
	testDateTime(DateTime(2010, 10, 15, 2, 22, 10, 915).add(1, DateTime::Year), DateTime(2011, 10, 15, 2, 22, 10, 915), "Increment years");
	// Decrement individual periods
	testDateTime(DateTime(2042, 2, 10, 6, 23, 55, 72).add(-1, DateTime::Millisecond), DateTime(2042, 2, 10, 6, 23, 55, 71), "Decrement milliseconds");
	testDateTime(DateTime(2142, 2, 19, 17, 53, 1, 440).add(-1, DateTime::Second), DateTime(2142, 2, 19, 17, 53, 0, 440), "Decrement seconds");
	testDateTime(DateTime(2104, 2, 21, 19, 26, 19, 514).add(-1, DateTime::Minute), DateTime(2104, 2, 21, 19, 25, 19, 514), "Decrement minutes");
	testDateTime(DateTime(2115, 10, 26, 7, 22, 8, 375).add(-1, DateTime::Hour), DateTime(2115, 10, 26, 6, 22, 8, 375), "Decrement hours");
	testDateTime(DateTime(1922, 2, 25, 6, 57, 58, 462).add(-1, DateTime::Day), DateTime(1922, 2, 24, 6, 57, 58, 462), "Decrement days");
	testDateTime(DateTime(2071, 10, 9, 5, 4, 37, 247).add(-1, DateTime::Month), DateTime(2071, 9, 9, 5, 4, 37, 247), "Decrement months");
	testDateTime(DateTime(2100, 8, 9, 16, 48, 24, 386).add(-1, DateTime::Year), DateTime(2099, 8, 9, 16, 48, 24, 386), "Decrement years");
	// +10 individual periods
	testDateTime(DateTime(1932, 10, 23, 12, 25, 15, 576).add(10, DateTime::Millisecond), DateTime(1932, 10, 23, 12, 25, 15, 586), "+10 milliseconds");
	testDateTime(DateTime(2038, 11, 4, 4, 36, 6, 902).add(10, DateTime::Second), DateTime(2038, 11, 4, 4, 36, 16, 902), "+10 seconds");
	testDateTime(DateTime(1935, 9, 30, 7, 58, 34, 860).add(10, DateTime::Minute), DateTime(1935, 9, 30, 8, 8, 34, 860), "+10 minutes");
	testDateTime(DateTime(2130, 6, 12, 8, 35, 55, 527).add(10, DateTime::Hour), DateTime(2130, 6, 12, 18, 35, 55, 527), "+10 hours");
	testDateTime(DateTime(1917, 7, 29, 2, 19, 0, 196).add(10, DateTime::Day), DateTime(1917, 8, 8, 2, 19, 0, 196), "+10 days");
	testDateTime(DateTime(1949, 11, 8, 9, 16, 4, 973).add(10, DateTime::Month), DateTime(1950, 9, 8, 9, 16, 4, 973), "+10 months");
	testDateTime(DateTime(2137, 10, 8, 6, 27, 16, 769).add(10, DateTime::Year), DateTime(2147, 10, 8, 6, 27, 16, 769), "+10 years");
	// -10 individual periods
	testDateTime(DateTime(2122, 2, 6, 7, 9, 3, 911).add(-10, DateTime::Millisecond), DateTime(2122, 2, 6, 7, 9, 3, 901), "-10 milliseconds");
	testDateTime(DateTime(2028, 2, 8, 13, 54, 46, 890).add(-10, DateTime::Second), DateTime(2028, 2, 8, 13, 54, 36, 890), "-10 seconds");
	testDateTime(DateTime(1977, 12, 10, 10, 48, 46, 33).add(-10, DateTime::Minute), DateTime(1977, 12, 10, 10, 38, 46, 33), "-10 minutes");
	testDateTime(DateTime(1930, 1, 31, 7, 36, 59, 134).add(-10, DateTime::Hour), DateTime(1930, 1, 30, 21, 36, 59, 134), "-10 hours");
	testDateTime(DateTime(2046, 2, 3, 22, 21, 21, 230).add(-10, DateTime::Day), DateTime(2046, 1, 24, 22, 21, 21, 230), "-10 days");
	testDateTime(DateTime(1925, 7, 4, 3, 34, 53, 720).add(-10, DateTime::Month), DateTime(1924, 9, 4, 3, 34, 53, 720), "-10 months");
	testDateTime(DateTime(1995, 6, 21, 16, 39, 33, 555).add(-10, DateTime::Year), DateTime(1985, 6, 21, 16, 39, 33, 555), "-10 years");
	// +100 individual periods
	testDateTime(DateTime(1979, 2, 9, 21, 26, 31, 147).add(100, DateTime::Millisecond), DateTime(1979, 2, 9, 21, 26, 31, 247), "+100 milliseconds");
	testDateTime(DateTime(1977, 6, 21, 18, 32, 25, 112).add(100, DateTime::Second), DateTime(1977, 6, 21, 18, 34, 5, 112), "+100 seconds");
	testDateTime(DateTime(1914, 5, 29, 7, 58, 46, 476).add(100, DateTime::Minute), DateTime(1914, 5, 29, 9, 38, 46, 476), "+100 minutes");
	testDateTime(DateTime(1901, 6, 24, 3, 42, 48, 667).add(100, DateTime::Hour), DateTime(1901, 6, 28, 7, 42, 48, 667), "+100 hours");
	testDateTime(DateTime(1905, 9, 17, 15, 3, 24, 159).add(100, DateTime::Day), DateTime(1905, 12, 26, 15, 3, 24, 159), "+100 days");
	testDateTime(DateTime(2110, 12, 19, 16, 7, 6, 468).add(100, DateTime::Month), DateTime(2119, 4, 19, 16, 7, 6, 468), "+100 months");
	testDateTime(DateTime(1974, 5, 15, 10, 33, 9, 134).add(100, DateTime::Year), DateTime(2074, 5, 15, 10, 33, 9, 134), "+100 years");
	// -100 individual periods
	testDateTime(DateTime(2148, 9, 14, 10, 52, 19, 104).add(-100, DateTime::Millisecond), DateTime(2148, 9, 14, 10, 52, 19, 4), "-100 milliseconds");
	testDateTime(DateTime(2103, 8, 12, 6, 52, 1, 699).add(-100, DateTime::Second), DateTime(2103, 8, 12, 6, 50, 21, 699), "-100 seconds");
	testDateTime(DateTime(2013, 3, 22, 14, 53, 55, 225).add(-100, DateTime::Minute), DateTime(2013, 3, 22, 13, 13, 55, 225), "-100 minutes");
	testDateTime(DateTime(2029, 7, 12, 11, 31, 54, 816).add(-100, DateTime::Hour), DateTime(2029, 7, 8, 7, 31, 54, 816), "-100 hours");
	testDateTime(DateTime(2034, 8, 20, 21, 58, 8, 597).add(-100, DateTime::Day), DateTime(2034, 5, 12, 21, 58, 8, 597), "-100 days");
	testDateTime(DateTime(2031, 5, 10, 2, 54, 24, 225).add(-100, DateTime::Month), DateTime(2023, 1, 10, 2, 54, 24, 225), "-100 months");
	testDateTime(DateTime(2050, 4, 1, 15, 12, 0, 441).add(-100, DateTime::Year), DateTime(1950, 4, 1, 15, 12, 0, 441), "-100 years");
	// +1000 individual periods
	testDateTime(DateTime(2005, 10, 28, 4, 35, 48, 509).add(1000, DateTime::Millisecond), DateTime(2005, 10, 28, 4, 35, 49, 509), "+1000 milliseconds");
	testDateTime(DateTime(1997, 3, 29, 14, 43, 25, 105).add(1000, DateTime::Second), DateTime(1997, 3, 29, 15, 0, 5, 105), "+1000 seconds");
	testDateTime(DateTime(2009, 3, 11, 21, 36, 8, 46).add(1000, DateTime::Minute), DateTime(2009, 3, 12, 14, 16, 8, 46), "+1000 minutes");
	testDateTime(DateTime(1992, 5, 29, 9, 46, 42, 371).add(1000, DateTime::Hour), DateTime(1992, 7, 10, 1, 46, 42, 371), "+1000 hours");
	testDateTime(DateTime(1965, 6, 5, 19, 14, 39, 545).add(1000, DateTime::Day), DateTime(1968, 3, 1, 19, 14, 39, 545), "+1000 days");
	testDateTime(DateTime(1932, 7, 10, 10, 10, 53, 775).add(1000, DateTime::Month), DateTime(2015, 11, 10, 10, 10, 53, 775), "+1000 months");
	// -1000 individual periods
	testDateTime(DateTime(2151, 4, 14, 6, 53, 2, 450).add(-1000, DateTime::Millisecond), DateTime(2151, 4, 14, 6, 53, 1, 450), "-1000 milliseconds");
	testDateTime(DateTime(1972, 4, 15, 16, 22, 43, 238).add(-1000, DateTime::Second), DateTime(1972, 4, 15, 16, 6, 3, 238), "-1000 seconds");
	testDateTime(DateTime(1946, 7, 17, 17, 36, 54, 566).add(-1000, DateTime::Minute), DateTime(1946, 7, 17, 0, 56, 54, 566), "-1000 minutes");
	testDateTime(DateTime(2112, 12, 16, 16, 33, 51, 967).add(-1000, DateTime::Hour), DateTime(2112, 11, 5, 0, 33, 51, 967), "-1000 hours");
	testDateTime(DateTime(2055, 6, 24, 6, 29, 6, 412).add(-1000, DateTime::Day), DateTime(2053, 9, 28, 6, 29, 6, 412), "-1000 days");
	testDateTime(DateTime(2123, 9, 15, 8, 48, 14, 81).add(-1000, DateTime::Month), DateTime(2040, 5, 15, 8, 48, 14, 81), "-1000 months");
	// Rollover all periods
	testDateTime(DateTime(1934, 12, 31, 23, 59, 59, 999).add(1, DateTime::Millisecond), DateTime(1935, 1, 1, 0, 0, 0, 0), "Add forward 1 milliseconds");
	testDateTime(DateTime(2076, 1, 1, 0, 0, 0, 0).add(-1, DateTime::Millisecond), DateTime(2075, 12, 31, 23, 59, 59, 999), "Roll back 1 milliseconds");
	// Increment to valid leap days
	testDateTime(DateTime(1904, 2, 28, 0, 0, 0, 0).add(1, DateTime::Day), DateTime(1904, 2, 29, 0, 0, 0, 0), "1904 leap day");
	testDateTime(DateTime(2000, 2, 28, 0, 0, 0, 0).add(1, DateTime::Day), DateTime(2000, 2, 29, 0, 0, 0, 0), "2000 leap day");
	// Decrement to valid leap days
	testDateTime(DateTime(1904, 3, 1, 0, 0, 0, 0).add(-1, DateTime::Day), DateTime(1904, 2, 29, 0, 0, 0, 0), "1904 leap day");
	testDateTime(DateTime(2000, 3, 1, 0, 0, 0, 0).add(-1, DateTime::Day), DateTime(2000, 2, 29, 0, 0, 0, 0), "2000 leap day");
	// Increment over invalid leap days
	testDateTime(DateTime(1900, 2, 28, 0, 0, 0, 0).add(1, DateTime::Day), DateTime(1900, 3, 1, 0, 0, 0, 0), "1900 non leap day");
	testDateTime(DateTime(2100, 2, 28, 0, 0, 0, 0).add(1, DateTime::Day), DateTime(2100, 3, 1, 0, 0, 0, 0), "2100 non leap day");
	// Decrement over invalid leap days
	testDateTime(DateTime(1900, 3, 1, 0, 0, 0, 0).add(-1, DateTime::Day), DateTime(1900, 2, 28, 0, 0, 0, 0), "1900 non leap day");
	testDateTime(DateTime(2100, 3, 1, 0, 0, 0, 0).add(-1, DateTime::Day), DateTime(2100, 2, 28, 0, 0, 0, 0), "2100 non leap day");
	// Long interval tests
	testDateTime(DateTime(2000, 1, 1, 0, 0, 0, 0).add(90061001, DateTime::Millisecond), DateTime(2000, 1, 2, 1, 1, 1, 1), "Add 90,061,001 milliseconds");
	testDateTime(DateTime(2000, 1, 1, 0, 0, 0, 0).add(900610010, DateTime::Millisecond), DateTime(2000, 1, 11, 10, 10, 10, 10), "Add 900,610,010 milliseconds");
	testDateTime(DateTime(2000, 1, 1, 0, 0, 0, 0).add(0, DateTime::Millisecond), DateTime(2000, 1, 1, 0, 0, 0, 0), "Add 0 milliseconds");
	testDateTime(DateTime(2000, 1, 1, 0, 0, 0, 0).add(1, DateTime::Millisecond), DateTime(2000, 1, 1, 0, 0, 0, 1), "Add 1 millisecond");
	testDateTime(DateTime(2000, 1, 1, 0, 0, 0, 0).add(1500, DateTime::Millisecond), DateTime(2000, 1, 1, 0, 0, 1, 500), "Add 1500 milliseconds");
	testDateTime(DateTime(2000, 1, 1, 0, 0, 0, 0).add(60000, DateTime::Millisecond), DateTime(2000, 1, 1, 0, 1, 0, 0), "Add 60000 milliseconds");
	testDateTime(DateTime(2000, 1, 1, 0, 0, 0, 0).add(3600000, DateTime::Millisecond), DateTime(2000, 1, 1, 1, 0, 0, 0), "Add 3600000 milliseconds");
	testDateTime(DateTime(2000, 1, 1, 0, 0, 0, 0).add(36000000, DateTime::Millisecond), DateTime(2000, 1, 1, 10, 0, 0, 0), "Add 36000000 milliseconds");
	testDateTime(DateTime(2000, 1, 1, 23, 59, 59, 999).add(-1, DateTime::Millisecond), DateTime(2000, 1, 1, 23, 59, 59, 998), "Subtract 1 millisecond");
	testDateTime(DateTime(2000, 1, 1, 23, 59, 59, 999).add(-1500, DateTime::Millisecond), DateTime(2000, 1, 1, 23, 59, 58, 499), "Subtract 1500 milliseconds");
	testDateTime(DateTime(2000, 1, 1, 23, 59, 59, 999).add(-60000, DateTime::Millisecond), DateTime(2000, 1, 1, 23, 58, 59, 999), "Subtract 60000 milliseconds");
	testDateTime(DateTime(2000, 1, 1, 23, 59, 59, 999).add(-3600000, DateTime::Millisecond), DateTime(2000, 1, 1, 22, 59, 59, 999), "Subtract 3600000 milliseconds");
	testDateTime(DateTime(2000, 1, 1, 23, 59, 59, 999).add(-36000000, DateTime::Millisecond), DateTime(2000, 1, 1, 13, 59, 59, 999), "Subtract 36000000 milliseconds");
	testDateTime(DateTime(2000, 1, 1, 0, 0, 0, 0).add(0, DateTime::Second), DateTime(2000, 1, 1, 0, 0, 0, 0), "Add 0 seconds");
	testDateTime(DateTime(2000, 1, 1, 0, 0, 0, 0).add(1, DateTime::Second), DateTime(2000, 1, 1, 0, 0, 1, 0), "Add 1 second");
	testDateTime(DateTime(2000, 1, 1, 0, 0, 0, 0).add(100, DateTime::Second), DateTime(2000, 1, 1, 0, 1, 40, 0), "Add 100 seconds");
	testDateTime(DateTime(2000, 1, 1, 0, 0, 0, 0).add(3600, DateTime::Second), DateTime(2000, 1, 1, 1, 0, 0, 0), "Add 3600 seconds");
	testDateTime(DateTime(2000, 1, 1, 0, 0, 0, 0).add(36000, DateTime::Second), DateTime(2000, 1, 1, 10, 0, 0, 0), "Add 36000 seconds");
	testDateTime(DateTime(2000, 1, 1, 23, 59, 59, 999).add(-1, DateTime::Second), DateTime(2000, 1, 1, 23, 59, 58, 999), "Subtract 1 second");
	testDateTime(DateTime(2000, 1, 1, 23, 59, 59, 999).add(-100, DateTime::Second), DateTime(2000, 1, 1, 23, 58, 19, 999), "Subtract 100 seconds");
	testDateTime(DateTime(2000, 1, 1, 23, 59, 59, 999).add(-3600, DateTime::Second), DateTime(2000, 1, 1, 22, 59, 59, 999), "Subtract 3600 seconds");
	testDateTime(DateTime(2000, 1, 1, 23, 59, 59, 999).add(-36000, DateTime::Second), DateTime(2000, 1, 1, 13, 59, 59, 999), "Subtract 36000 seconds");
	testDateTime(DateTime(1999, 2, 28, 0, 0, 0, 0).add(365, DateTime::Day), DateTime(2000, 2, 28, 0, 0, 0, 0), "Add 365 days");
	testDateTime(DateTime(1999, 2, 28, 0, 0, 0, 0).add(1000, DateTime::Day), DateTime(2001, 11, 24, 0, 0, 0, 0), "Add 1000 days");
	testDateTime(DateTime(1900, 1, 1, 0, 0, 0, 0).add(93501, DateTime::Day), DateTime(2155, 12, 31, 0, 0, 0, 0), "Add 93501 days"); // Full range
	testDateTime(DateTime(2000, 2, 28, 0, 0, 0, 0).add(-365, DateTime::Day), DateTime(1999, 2, 28, 0, 0, 0, 0), "Subtract 365 days");
	testDateTime(DateTime(2001, 11, 24, 0, 0, 0, 0).add(-1000, DateTime::Day), DateTime(1999, 2, 28, 0, 0, 0, 0), "Subtract 1000 days");
	testDateTime(DateTime(2155, 12, 31, 0, 0, 0, 0).add(-93501, DateTime::Day), DateTime(1900, 1, 1, 0, 0, 0, 0), "Subtract 93501 days"); // Full range
	// addOneDay()
	testDateTime(DateTime(1900, 1, 1, 0, 0, 0, 0).addOneDay(), DateTime(1900, 1, 2, 0, 0, 0, 0), "addOneDay()");
	testDateTime(DateTime(1900, 12, 31, 0, 0, 0, 0).addOneDay(), DateTime(1901, 1, 1, 0, 0, 0, 0), "addOneDay() rollover");
	testInvalidDateTime(DateTime(2155, 12, 31, 0, 0, 0, 0).addOneDay(), true);
	// addOneMonth()
	testDateTime(DateTime(1900, 1, 1, 0, 0, 0, 0).addOneMonth(), DateTime(1900, 2, 1, 0, 0, 0, 0), "addOneMonth()");
	testDateTime(DateTime(1900, 12, 1, 0, 0, 0, 0).addOneMonth(), DateTime(1901, 1, 1, 0, 0, 0, 0), "addOneMonth() rollover");
	testInvalidDateTime(DateTime(2155, 12, 1, 0, 0, 0, 0).addOneMonth(), true);
	// addOneYear()
	testDateTime(DateTime(1900, 1, 1, 0, 0, 0, 0).addOneYear(), DateTime(1901, 1, 1, 0, 0, 0, 0), "addOneYear()");
	testInvalidDateTime(DateTime(2155, 1, 1, 0, 0, 0, 0).addOneYear(), true);
	// subtractOneDay()
	testDateTime(DateTime(1900, 1, 2, 0, 0, 0, 0).subtractOneDay(), DateTime(1900, 1, 1, 0, 0, 0, 0), "subtractOneDay()");
	testDateTime(DateTime(1901, 1, 1, 0, 0, 0, 0).subtractOneDay(), DateTime(1900, 12, 31, 0, 0, 0, 0), "subtractOneDay() rollover");
	testInvalidDateTime(DateTime(1900, 1, 1, 0, 0, 0, 0).subtractOneDay(), true);
	// subtractOneMonth()
	testDateTime(DateTime(1900, 2, 1, 0, 0, 0, 0).subtractOneMonth(), DateTime(1900, 1, 1, 0, 0, 0, 0), "subtractOneMonth()");
	testDateTime(DateTime(1900, 2, 1, 0, 0, 0, 0).subtractOneMonth(), DateTime(1900, 1, 1, 0, 0, 0, 0), "subtractOneMonth() rollover");
	testInvalidDateTime(DateTime(1900, 1, 31, 0, 0, 0, 0).subtractOneMonth(), true);
	// subtractOneYear()
	testDateTime(DateTime(1901, 1, 1, 0, 0, 0, 0).subtractOneYear(), DateTime(1900, 1, 1, 0, 0, 0, 0), "subtractOneYear()");
	testInvalidDateTime(DateTime(1900, 12, 31, 0, 0, 0, 0).subtractOneYear(), true);

// TESTING setAdjustment() & getAdjustment()
	testGetAdjustment(DateTime(1900, 1, 1, 0, 0, 0, 0), 0);                           // 1900-01-01
	testGetAdjustment(DateTime(1900, 3, 31, 0, 0, 0, 0).add(1, DateTime::Month), 1);  // 1900-04-30
	testGetAdjustment(DateTime(1904, 1, 31, 0, 0, 0, 0).add(1, DateTime::Month), 2);  // 1904-02-29
	testGetAdjustment(DateTime(1900, 1, 31, 0, 0, 0, 0).add(1, DateTime::Month), 3);  // 1900-02-28
	testGetAdjustment(DateTime(2096, 2, 29, 0, 0, 0, 0).add(4, DateTime::Year), 1);   // 2100-02-28
	testGetAdjustment(DateTime(1900, 1, 1, 0, 0, 0, 0).add(255, DateTime::Year), 0);   // 2100-02-28
	testGetAdjustment(DateTime(2155, 1, 1, 0, 0, 0, 0).add(-255, DateTime::Year), 0);   // 2100-02-28

	// Test daysInRange()
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
		} else cout << "Pass." << endl;
	}
	return 0;
}
