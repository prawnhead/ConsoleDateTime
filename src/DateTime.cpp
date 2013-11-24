#include "DateTime.h"

#ifndef ARDUINO
	using namespace std;
#endif

char DateTime::_line[24] = "";

DateTime::DateTime() {
	_year = 0;
	_month = 0;
	_day = 0;
	_hour = 0;
	_minute = 0;
	_second = 0;
	_millisecond = 0;
}

char* DateTime::toString() {
	sprintf(DateTime::_line, "%d-%02d-%02d %02d:%02d:%02d.%03d", year(), _month, _day, _hour, _minute, _second, _millisecond);
	return DateTime::_line;
}

//DateTime::DateTime() {
//DateTime::DateTime() {
//	_year = 0;
//	_month = 0;
//	_day = 0;
//	_hour = 0;
//	_minute = 0;
//	_second = 0;
//	//_line = "Six";
//}
//
int DateTime::year() const {
	return MIN_YEAR + _year;
}

//byte DateTime::month() const {
//	return _month;
//}
//
//byte DateTime::day() const {
//	return _day;
//}
//
//byte DateTime::hour() const {
//	return _hour;
//}
//
//byte DateTime::minute() const {
//	return _minute;
//}
//
//byte DateTime::second() const {
//	return _second;
//}
//
//int DateTime::millisecond() const {
//	return _millisecond;
//}
//
//char* DateTime::toString() {
//	//http://arduino.cc/en/Reference/StringObject
//	String* output;
//	char* line;
//	//char* two;
////	output = new String();
//	//sprintf(line, "%d", _year);	// WORKS
//	//_line = "Hello";
//	sprintf(line, "%d", _year);	// No WORKS
//	//cout << "Line: " << line << endl;
//	_line = line;
//	//delete(_string);
//	//_string = output;
//	return line;
//}
//
////String& DateTime::getString() {
////	return *_string;
////}
//
//char* DateTime::getLine() {
//	return _line;
//}

//// PUBLIC FUNCTIONS
//
//DateTime::DateTime() {
//	setEpoch();
//}
//
//DateTime::DateTime(int year, byte month, byte day, byte hour, byte minute, byte second, int millisecond) {
//	if (year < MIN_YEAR || year > MAX_YEAR) {
//		setEpoch();
//		setStatus(Valid, false);
//		setStatus(Overflow, true);
//	} else {
//		_year = year - MIN_YEAR;
//		_month = month;
//		_day = day;
//		_hour = hour;
//		_minute = minute;
//		_second = second;
//		_millisecond = millisecond;
//		_string = 0;
//		_status = Valid;
//		if (!checkValid()) setEpoch();
//	}
//}
//
//void DateTime::setEpoch() {
//	_year = 0;
//	_month = 1;
//	_day = 1;
//	_hour = 0;
//	_minute = 0;
//	_second = 0;
//	_millisecond = 0;
//	_string = 0;
//	_status = Valid;
//}
//
//int DateTime::year() const {
//	return MIN_YEAR + _year;
//}
//
//byte DateTime::month() const {
//	return _month;
//}
//
//byte DateTime::day() const {
//	return _day;
//}
//
//byte DateTime::hour() const {
//	return _hour;
//}
//
//byte DateTime::minute() const {
//	return _minute;
//}
//
//byte DateTime::second() const {
//	return _second;
//}
//
//int DateTime::millisecond() const {
//	return _millisecond;
//}
//
//boolean DateTime::isLeapYear(int year) {
//	//http://en.wikipedia.org/wiki/Leap_year
//	return (year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0));
//}
//
//boolean DateTime::isLeapYear() const {
//	return isLeapYear(year());
//}
//
//byte DateTime::daysInMonth() const {
//	return daysInMonth(_month, year());
//}
//
//byte DateTime::daysInMonth(byte month, int year) {
//// http://en.wikipedia.org/wiki/Month
//	switch (month) {
//	case 1:
//		return 31;
//		break;
//	case 2:
//		return DateTime::isLeapYear(year) ? 29 : 28;
//		break;
//	case 3:
//		return 31;
//		break;
//	case 4:
//		return 30;
//		break;
//	case 5:
//		return 31;
//		break;
//	case 6:
//		return 30;
//		break;
//	case 7:
//		return 31;
//		break;
//	case 8:
//		return 31;
//		break;
//	case 9:
//		return 30;
//		break;
//	case 10:
//		return 31;
//		break;
//	case 11:
//		return 30;
//		break;
//	case 12:
//		return 31;
//		break;
//	}
//	return 0;
//}
//
//void DateTime::setStatus(DateTime::Status status, boolean state) {
//	if (state) _status |= status;
//	else _status &= ~status;
//}
//
//boolean DateTime::getStatus(DateTime::Status status) const {
//	return (_status & status);
//}
//
//boolean DateTime::isValid() const {
//	return (_status & Valid);
//}
//
//void DateTime::setAdjustment(byte value) {
//	if (value > ADJUSTMENT_MASK) return;
//	_status &= ~ADJUSTMENT_MASK;
//	_status |= value;
//}
//
//byte DateTime::getAdjustment() const {
//	return _status & ADJUSTMENT_MASK;
//}
//
//void DateTime::overflowed() {
//	setEpoch();
//	setStatus(Valid, false);
//	setStatus(Overflow, true);
//}
//
//int DateTime::daysInYear(int year) {
//	if (isLeapYear(year)) return 366;
//	return 365;
//}
//
//int DateTime::daysInYear() const {
//	return daysInYear(year());
//}
//
//DateTime& DateTime::addOneDay() { // TODO: Fold in with add()
//	if (_day < daysInMonth()) _day++;
//	else {
//		_day = 1;
//		addOneMonth();
//	}
//	return *this;
//}
//
//DateTime& DateTime::addOneMonth() { // TODO: Fold in with add()
//	// Precondition: Must not be used on days after 28th of any month
//	if (_month < MONTHS_PER_YEAR) _month++;
//	else {
//		_month = 1;
//		addOneYear();
//	}
//	return *this;
//}
//
//DateTime& DateTime::addOneYear() { // TODO: Fold in with add()
//	// Precondition: Must not be used on days after 28th of any month
//	if (year() < MAX_YEAR)
//		_year++;
//	else
//		overflowed();
//	return *this;
//}
//
//DateTime& DateTime::subtractOneDay() { // TODO: Fold in with add()
//	if (_day > 1) _day--;
//	else {
//		subtractOneMonth();
//		if(isValid()) _day = daysInMonth();
//	}
//	return *this;
//}
//
//DateTime& DateTime::subtractOneMonth() { // TODO: Fold in with add()
//	// Precondition: Must not be used on days after 28th of any month
//	if (_month > 1) _month--;
//	else {
//		subtractOneYear();
//		if(isValid()) _month = MONTHS_PER_YEAR;
//	}
//	return *this;
//}
//
//DateTime& DateTime::subtractOneYear() { // TODO: Fold in with add()
//	// Precondition: Must not be used on days after 28th of any month
//	if (year() > MIN_YEAR)
//		_year--;
//	else
//		overflowed();
//	return *this;
//}
//
//int DateTime::monthCarryBorrow(int& month) {
//	// Accepts a month of any positive or negative value.
//	// Restores 'month' to a number between 1 and 12
//	// Returns the number of years to carry/borrow.
//	int carryBorrow = 0;
//	while (month < 1) {
//		month += MONTHS_PER_YEAR;
//		carryBorrow--;
//	}
//	month--;
//	carryBorrow += month / MONTHS_PER_YEAR;
//	month %= MONTHS_PER_YEAR;
//	month++;
//	return carryBorrow;
//}
//
//void DateTime::add(byte& attribute, long& interval, int limit) {
//	// For attributes having a range 0 to (LIMIT - 1);
//	long magnitude = attribute + interval;
//	if (magnitude < 0) {
//		interval = magnitude / limit - 1;
//		magnitude -= interval * limit;
//	} else {
//		interval = magnitude / limit;
//	}
//	attribute = magnitude % limit;
//}
//
//DateTime& DateTime::add(long interval, Period period) {
//	if (!interval) return *this;
//	if (period == Millisecond) {
//		long magnitude = _millisecond + interval;
//		interval = magnitude / MILLISECONDS_PER_SECOND;
//		int newValue = magnitude % MILLISECONDS_PER_SECOND;
//		if (newValue < 0) {
//			_millisecond = newValue + MILLISECONDS_PER_SECOND;
//			interval -= 1;
//		} else {
//			_millisecond = newValue;
//		}
//		if (interval) period = Second;  // Milliseconds cascade to Seconds
//	}
//	if (period == Second) {
//		add(_second, interval, SECONDS_PER_MINUTE);
//		if (interval) period = Minute;  // Seconds cascade to Minutes
//	}
//	if (period == Minute) {
//		add(_minute, interval, MINUTES_PER_HOUR);
//		if (interval) period = Hour;    // Minutes cascade to Hours
//	}
//	if (period == Hour) {
//		add(_hour, interval, HOURS_PER_DAY);
//		if (interval) period = Day;     // Hours cascade to Days
//	}
//
//	// DAYS
//	if (period == Day) {
//		if (interval < 0) { // go backwards
//			// 1. Get back to the first of the month if you can
//			while (_day > 1) {
//				interval++;
//				subtractOneDay();
//				if (!isValid()) interval = 0; // Underflow.
//				if (!interval) break;
//			}
//			// 2. Jump by months to January
//			while (interval && _month > 1) {
//				int priorMonth = _month - 1;
//				int priorYear = year() + monthCarryBorrow(priorMonth);
//				if (daysInMonth(priorMonth, priorYear) <= -interval) {
//					subtractOneMonth();
//					interval += daysInMonth();
//					if (!isValid()) interval = 0; // Underflow.
//				} else break;
//			}
//			// 3. Jump by years if you can
//			int daysPriorYear = daysInYear(year() - 1);
//			while (-interval >= daysPriorYear) {
//				interval += daysPriorYear;
//				subtractOneYear();
//				if (!isValid()) interval = 0; // blew it. Overflowed.
//				daysPriorYear = daysInYear(year() - 1);
//			}
//			// 4. Jump by months if you can
//			while (-interval >= daysInMonth()) {
//				subtractOneMonth();
//				interval += daysInMonth();
//				if (!isValid()) interval = 0; // blew it. Overflowed.
//			}
//			// 5. Jump by days to finish off
//			while (interval) {
//				interval++;
//				subtractOneDay();
//				if (!isValid()) interval = 0; // blew it. Overflowed.
//			}
//		} else {  // go forward
//			// 1. Get to the first of next month if you can
//			while (_day > 1) {
//				interval--;
//				addOneDay();
//				if (!isValid()) interval = 0; // blew it. Overflowed.
//				if (!interval) break;
//			}
//			// 2. Jump by months to January
//			while (interval && _month > 1) {
//				if (interval >= daysInMonth()) {
//					interval -= daysInMonth();
//					addOneMonth();
//					if (!isValid()) interval = 0; // blew it. Overflowed.
//				} else {
//					_day += interval;
//					interval = 0;
//					break;
//				}
//			}
//			// 3. Jump by years if you can
//			while (interval >= daysInYear()) {
//				interval -= daysInYear();
//				addOneYear();
//				if (!isValid()) interval = 0; // blew it. Overflowed.
//			}
//			// 4. Jump by months if you can
//			while (interval >= daysInMonth()) {
//				interval -= daysInMonth();
//				addOneMonth();
//				if (!isValid()) interval = 0; // blew it. Overflowed.
//			}
//			// 5. Jump by days to finish off
//			while (interval) {
//				interval--;
//				addOneDay();
//				if (!isValid()) interval = 0; // blew it. Overflowed.
//			}
//		}
//	}
//
//	if (period == Month) { // Days DON'T cascade into Months
//		add(_month, interval, MONTHS_PER_YEAR);  // TODO: Doesn't work for months 1-12
//		if (interval != 0) period = Year;
//	}
//
//	if (period == Year) { // Months cascade into years
//		long testYear = interval + year();
//		if (testYear > MAX_YEAR || testYear < MIN_YEAR) overflowed();
//		else _year += interval;
//	}
//
//	// Correct for different month lengths, if required.
//	if (_day > daysInMonth()) {
//		setAdjustment(_day - daysInMonth());
//		_day = daysInMonth();
//	}
//
//	return *this;
//}
//
//#ifndef ARDUINO
//char* DateTime::intToString(int value) {
//	static char ramBuffer[10];
//	sprintf(ramBuffer, "%d", value);
//	return ramBuffer;
//}
//#endif
//
//String& DateTime::toString() {
//	//http://arduino.cc/en/Reference/StringObject
//	String* output;
//	if (!isValid()) {
//		output = new String("8888-88-88 88:88:88.888");
//	} else {
//		output = new String();
//		*output += intToString(year());
//		*output += '-';
//		if (_month < 10) *output += '0';
//		*output += intToString(_month);
//		*output += '-';
//		if (_day < 10) *output += '0';
//		*output += intToString(_day);
//		*output += ' ';
//		if (_hour < 10) *output += '0';
//		*output += intToString(_hour);
//		*output += ':';
//		if (_minute < 10) *output += '0';
//		*output += intToString(_minute);
//		*output += ':';
//		if (_second < 10) *output += '0';
//		*output += intToString(_second);
//		*output += '.';
//		if (_millisecond < 100) *output += '0';
//		if (_millisecond < 10) *output += '0';
//		*output += intToString(_millisecond);
//	}
//
//	delete(_string);
//	_string = output;
//	return *_string;
//}
//
//boolean DateTime::isBefore(const DateTime &other) const {
//	if (this->year() < other.year()) return true;
//	if (this->year() > other.year()) return false;
//	if (this->month() < other.month()) return true;
//	if (this->month() > other.month()) return false;
//	if (this->day() < other.day()) return true;
//	if (this->day() > other.day()) return false;
//	if (this->hour() < other.hour()) return true;
//	if (this->hour() > other.hour()) return false;
//	if (this->minute() < other.minute()) return true;
//	if (this->minute() > other.minute()) return false;
//	if (this->second() < other.second()) return true;
//	if (this->second() > other.second()) return false;
//	if (this->millisecond() < other.millisecond()) return true;
//	if (this->millisecond() > other.millisecond()) return false;
//	return false;
//}
//
//boolean DateTime::isEqualTo(const DateTime &other) const {
//	return (this->year() == other.year() &&
//			this->month() == other.month() &&
//			this->day() == other.day() &&
//			this->hour() == other.hour() &&
//			this->minute() == other.minute() &&
//			this->second() == other.second() &&
//			this->millisecond() == other.millisecond());
//}
//
//boolean DateTime::operator == (const DateTime &other) const {
//	return this->isEqualTo(other);
//}
//
//boolean DateTime::operator != (const DateTime &other) const {
//	return !this->isEqualTo(other);
//}
//
//boolean DateTime::operator < (const DateTime &other) const {
//	return this->isBefore(other);
//}
//
//boolean DateTime::operator <= (const DateTime &other) const {
//	return this->isBefore(other) || this->isEqualTo(other);
//}
//
//boolean DateTime::operator > (const DateTime &other) const {
//	return other.isBefore(*this);
//}
//
//boolean DateTime::operator >= (const DateTime &other) const {
//	return other.isBefore(*this) || other.isEqualTo(*this);
//}
//
//// PRIVATE FUNCTIONS
//
//boolean DateTime::checkValid() {
//	boolean validity = true;
//	// all years are valid (0 - 255) = (1900 - 2155)
//	if (_month == 0) validity = false;
//	else if (_month > MONTHS_PER_YEAR) validity = false;
//	else if (_day == 0) validity = false;
//	else if (_day > daysInMonth()) validity = false; // month must be checked prior to calling daysInMonth()
//	else if (_hour > (HOURS_PER_DAY - 1)) validity = false;
//	else if (_minute > (MINUTES_PER_HOUR - 1)) validity = false;
//	else if (_second > (SECONDS_PER_MINUTE - 1)) validity = false;
//	else if (_millisecond < 0) validity = false;
//	else if (_millisecond > (MILLISECONDS_PER_SECOND - 1)) validity = false;
//	if (!validity) setStatus(Valid, false);
//	return validity;
//}
