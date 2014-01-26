/**
 * @file    DateTime.h
 * @author  Chris Murphy <prawnhead@gmail.com>
 * @version 1.0
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details at
 * http://www.gnu.org/copyleft/gpl.html
 *
 * @section DESCRIPTION
 *
 * The DateTime class represents an instant of time with
 * millisecond resolution using the Gregorian calendar. This class
 * utilises the Date and Time classes and also contains functions
 * shared by the Date and Time classes.
 */

#ifndef DATETIME_H
#define DATETIME_H

#ifndef ARDUINO
	#include <cstdio>
	#include <iostream>
    #define int short
#endif

class DateTime {

private:

protected:

public:

//  /\ Untested
// ==========================================================================
//  \/ Tested

private:

protected:

public:
    static int moduloArithBaseZero(int& value, int addend, int modulo);
    static int moduloArithBaseOne(int& value, int addend, int modulo);

};

#endif // DATETIME_H

/*
class DateTime {
private:
	static const int mod_milliseconds = 1000;
	static const int mod_seconds = 60;
	static const int mod_minutes = 60;
	static const int mod_hours = 24;

    int millisecond, second, minute, hour, day, month, year;
	static char line[24];
	static int add(int& addendMinuend, int addendSubtrahend, int rangeModulo);
	static int daysInMonth(int month, int year);
	static bool isLeapYear(int year);
	void addDay(int value);
	int addMonth(int value);
	int addYear(int value);
	int adjust();
protected:
public:
    enum Period { Year, Month, Day, Hour, Minute, Second, Millisecond };
    DateTime();
    DateTime(int year, int month, int day, int hour, int minute, int second, int millisecond);
    int getMillisecond() { return millisecond; }
    int getSecond() { return second; }
    int getMinute() { return minute; }
    int getHour() { return hour; }
    int getDay() { return day; }
    int getMonth() { return month; }
    int getYear() { return year; }
	char* toString();
	int adjust(int value, Period period);
};

#endif // DATETIME_H
*/

/*
#ifndef DATETIME_H
#define DATETIME_H
// http://www.nongnu.org/avr-libc/user-manual/group__avr__stduint16_t.html


#ifndef ARDUINO
	#include <iostream>
//	#include <string>
	#include <cstdio>
//	#define F(X) X
//	#define PROGMEM
//	typedef string String;
//	typedef bool boolean;
    typedef uint8_t uint8_t;
#else
	#include <Arduino.h>
	#define int8_t_max 127
	#define uint8_t_max 255
	#define INT16_MAX 32767
	#define UINT16_MAX 65535
#endif

#define MIN_YEAR 1900

#define NO_STRING "8888-88-88 88:88:88.888"

class DateTime {

	private:
		// All instances of this class will share a single character
		// array for storage of string representations. This will
		static char _line[24];

		static const uint8_t uint8_t_max = 255;
		static const uint16_t uint16_t_max = 32767;

		static const uint8_t mod_year = 255;
		static const uint8_t floor_year = 0;
		static const uint8_t mod_month = 12;
		static const uint8_t floor_month = 1;
		// day by function
		static const uint8_t mod_hour = 24;
		static const uint8_t floor_hour = 0;
		static const uint8_t mod_minute = 60;
		static const uint8_t floor_minute = 0;
		static const uint8_t mod_second = 60;
		static const uint8_t floor_second = 0;
		static const uint16_t mod_millisecond = 1000;
		static const uint16_t floor_millisecond = 0;

	protected:
		uint8_t _year; // 0-255 represents 1900-2155
		uint8_t _month, _day, _hour, _minute, _second;
		uint16_t _millisecond;

	public:
		DateTime();
		uint16_t year() const;
		static int16_t modAddSub8(uint8_t& addendMinuend, int16_t addendSubtrahend, uint8_t rangeModulo);
		static int16_t modAddSub16(uint16_t& addendMinuend, int16_t addendSubtrahend, uint16_t rangeModulo);
//		static uint16_t modAddSub(uint8_t& addendMinuend, uint16_t addendSubtrahend, uint8_t rangeModulo, uint8_t rangeStart);
//		static uint16_t modAddSub(uint16_t& addendMinuend, uint16_t addendSubtrahend, uint16_t rangeModulo, uint16_t rangeStart);
//		uint8_t month() const;
//		uint8_t day() const;
//		uint8_t hour() const;
//		uint8_t minute() const;
//		uint8_t second() const;
//		uint16_t millisecond() const;
//
		char* toString();
////		String& getString();
//		char* getLine();
};

#endif // DATETIME_H
*/

//#define MILLISECONDS_PER_SECOND 1000
//#define SECONDS_PER_MINUTE 60
//#define MINUTES_PER_HOUR 60
//#define HOURS_PER_DAY 24
//#define DAYS_PER_400_YEARS 146097
//#define DAYS_PER_100_YEARS_MIN 36524
//#define MONTHS_PER_YEAR 12
////#define DAYS_PER_NORMAL_YEAR 365
//#define MAX_YEAR 2155
//#define ADJUSTMENT_MASK 0x03
//
///* Notes:
// * A month is defined as a calendar month.
// * Normal example:
// * DateTime(2001, 1, 15, 0, 0, 0, 0).add(1, DateTime::Month) == DateTime(2001, 2, 15, 0, 0, 0, 0)
// * Adjusted example:
// * DateTime(2001, 1, 31, 0, 0, 0, 0).add(1, DateTime::Month) == DateTime(2001, 2, 28, 0, 0, 0, 0)
// * When the day of the month is adjusted so as to not exceed the length of the month,
// * the getAdjustment() value is set; this indicates the number of days that were subtracted.
// * This occurs when moving by Months or Years from a month with more days to onw with less.
// */
//class DateTime {
//public:
//	enum Period { Year, Month, Day, Hour, Minute, Second, Millisecond };
//	enum Status { AdjustedBit0 = 1, AdjustedBit1 = 2, Valid = 4, Overflow = 8};
//	//enum DayOfWeek { Error, Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday };
//	//enum TimeSource { Compiler, NMEA };
//
//	/* TESTED */	DateTime();
//	/* TESTED */	DateTime(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second, uint16_t millisecond);
//
//	/* TESTED */	void setEpoch(); // reset to default date/time
//
//	/* TESTED */	uint16_t year() const;
//	/* TESTED */	uint8_t month() const;
//	/* TESTED */	uint8_t day() const;
//	/* TESTED */	uint8_t hour() const;
//	/* TESTED */	uint8_t minute() const;
//	/* TESTED */	uint8_t second() const;
//	/* TESTED */	uint16_t millisecond() const;
//
//	/* TESTED */	static boolean isLeapYear(uint16_t year);
//	/* TESTED */	boolean isLeapYear() const;
//	/* TESTED */	static uint8_t daysInMonth(uint8_t month, uint16_t year);
//	/* TESTED */	uint8_t daysInMonth() const;
//
//	/* TESTED */	void setStatus(DateTime::Status status, boolean state);
//	/* TESTED */	boolean getStatus(DateTime::Status status) const;
//	/* ASSUMED */	boolean isValid() const;
//	/* TESTED */	void setAdjustment(uint8_t value);
//	/* TESTED */	uint8_t getAdjustment() const;
//
//	/* TESTED */	static uint16_t daysInYear(uint16_t year);
//	/* TESTED */	uint16_t daysInYear() const;
//	/* TESTED */	DateTime& addOneDay();
//	/* TESTED */	DateTime& addOneMonth();
//	/* TESTED */	DateTime& addOneYear();
//	/* TESTED */	DateTime& subtractOneDay();
//	/* TESTED */	DateTime& subtractOneMonth();
//	/* TESTED */	DateTime& subtractOneYear();
//	/* TESTED */	static uint16_t monthCarryBorrow(uint16_t& month);
//	long uint16_tervalTo(DateTime other, DateTime::Period period);
//
//	/* TESTED */	static void add(uint8_t& attribute, long& uint16_terval, uint16_t limit);
//	/* ASSUMED */	DateTime& add(long uint16_terval, Period period);
//#ifndef ARDUINO
//	/* TESTED */	static char* uint16_tToString(uint16_t value);
//#endif
//	/* TESTED */	String& toString();
//
//	/* ASSUMED */	boolean isBefore(const DateTime &other) const;
//	/* ASSUMED */	boolean isEqualTo(const DateTime &other) const;
//	/* ASSUMED */	boolean operator == (const DateTime &other) const;
//	/* ASSUMED */	boolean operator != (const DateTime &other) const;
//	/* ASSUMED */	boolean operator <  (const DateTime &other) const;
//	/* ASSUMED */	boolean operator <= (const DateTime &other) const;
//	/* ASSUMED */	boolean operator >  (const DateTime &other) const;
//	/* ASSUMED */	boolean operator >= (const DateTime &other) const;
//
//protected:
//	uint8_t _year; // 0-255 represents 1900-2155
//	uint8_t _month, _day, _hour, _minute, _second, _status;
//	uint16_t _millisecond;
//	String* _string;
//
//private:
//	/* TESTED */	boolean checkValid();
//	/* TESTED */	void overflowed();
//};
//
//#endif // DATETIME_H
//
