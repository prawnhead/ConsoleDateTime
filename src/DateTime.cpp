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

/** \brief Core function for performing zero-based modular arithmetic.
 *
 * Choice of correct data types is critical to the operation of this function. As its
 * intended use is for Arduino, it needs to have the smallest possible memory footprint
 * and yet calculate correct values.
 * Use of a zero modulus will cause divide-by-zero errors.
 * Overflow will cause incorrect results if (addendMinuend + addendSubtrahend) > (max(int) - rangeModulus)
 * and likewise for subtraction.
 * This version of the function for manipulation of uint8_t values (modulo <= 255).
 * addendMinuend and rangeModulo can contain values in the range 0 to 255.
 *
 * \param addendMinuend the value being added to or subtracted from. Also the return value.
 * \param addendSubtrahend the value being added or subtracted.
 * \param rangeModulo the modulus for the arithmetic operation.
 * \return the carry/borrow of the result.
 *
 */
int16_t DateTime::modAddSub8(uint8_t& addendMinuend, int16_t addendSubtrahend, uint8_t rangeModulo) {

    int16_t intermediate = addendMinuend + addendSubtrahend;
        // addendMinuend can only be positive.
        // Rolls over when intermediate > MAX(int16_t)
        // Deliberately chosen not to be int32_t, which
        // would fix rollover, but upgrades the operation
        // to 4-byte values, causing performance hit.

    int16_t carry = intermediate / rangeModulo;
        // Cannot rollover.

    intermediate = intermediate % rangeModulo;
        // intermediate range: -(rangeModulo - 1) to (rangeModulo - 1)

    if (intermediate < 0) {
        carry--;
        intermediate += rangeModulo;
    }   // intermediate range: 0 to (rangeModulo - 1)

    addendMinuend = (uint8_t)intermediate;
    return carry;
}

/** \brief Core function for performing zero-based modular arithmetic.
 *
 * Choice of correct data types is critical to the operation of this function. As its
 * intended use is for Arduino, it needs to have the smallest possible memory footprint
 * and yet calculate correct values.
 * Use of a zero modulus will cause divide-by-zero errors.
 * Overflow will cause incorrect results if (addendMinuend + addendSubtrahend) > (max(int) - rangeModulus)
 * and likewise for subtraction.
 * This version of the function for manipulation of uint16_t values (modulo <= 65535).
 * addendMinuend and rangeModulo can contain values in the range 0 to 65535.
 *
 * \param addendMinuend the value being added to or subtracted from. Also the return value.
 * \param addendSubtrahend the value being added or subtracted.
 * \param rangeModulo the modulus for the arithmetic operation.
 * \return the carry/borrow of the result.
 *
 */
int16_t DateTime::modAddSub16(uint16_t& addendMinuend, int16_t addendSubtrahend, uint16_t rangeModulo) {

    int16_t intermediate = addendMinuend + addendSubtrahend;
        // addendMinuend can only be positive.
        // Rolls over when intermediate > MAX(int16_t)
        // Deliberately chosen not to be int32_t, which
        // would fix rollover, but upgrades the operation
        // to 4-byte values, causing performance hit.

    int16_t carry = intermediate / rangeModulo;
        // Cannot rollover.

    intermediate = intermediate % rangeModulo;
        // intermediate range: -(rangeModulo - 1) to (rangeModulo - 1)

    if (intermediate < 0) {
        carry--;
        intermediate += rangeModulo;
    }   // intermediate range: 0 to (rangeModulo - 1)

    addendMinuend = (uint16_t)intermediate;
    return carry;

}

//int8_t DateTime::modAddSub(uint8_t& addendMinuend, int8_t addendSubtrahend, uint8_t modulo) {
//	// Range(addendMinuend)		0 to 255
//	// Range(addendSubtrahend)	-128 to 127
//	// Range(modulo)			0 to 255
//
//	// Range(sum): -128 to 382 (doesn't fit int8_t or uint8_t and is signed)
//	int16_t sum = addendMinuend + addendSubtrahend;
//
//	// Range(intermediate): -128 (sum <= -modulo) to 254 (modulo = 255)
//	int16_t intermediate = sum % modulo;
//
//	if (intermediate < 0) {	// if -addendSubtrahend > addendMinuend
//		// Range(addendMinuend): 1 to (modulo - 1) can be case to uint8_t
//		addendMinuend = (uint8_t)(intermediate + modulo);
//		// Range(return): if sum = 382, modulo = 2, then return = 191. Requires int16_t.
//		// Range(return): if sum = 382, modulo = 3, then return = 127. Requires int8_t.
//		return sum / modulo - 1;
//	//} else if (intermediate > uint8_t_max) {	// Can't happen
//	//	// Range(return): if sum 382, modulo >
//	//	addendMinuend = (uint8_t)(intermediate - modulo);
//	//	return sum / modulo + 1;
//	} else {
//		return sum / modulo;
//		addendMinuend = (uint8_t)intermediate;
//	}
//}

//uint8_t DateTime::modAddSub(uint8_t& addendMinuend, int8_t addendSubtrahend, uint8_t rangeModulo, uint8_t rangeStart) {
//
//	// Data ranges:
//	// addendMinuend	0 to 255
//	// addendSubtrahend -128 to 127
//	// rangeModulo		0 to 255
//	// rangeStart		0 to 255
//
//	// Range of allowable addendMinuend values is:
//	// rangeStart ... rangeStart + rangeModulo - 1
//
//	// Range: zeroOffsetSum -383 (0 - 128 - 255) to 382 (255 + 127 - 0)
//	uint16_t zeroOffsetSum = addendMinuend + addendSubtrahend - rangeStart;
//
//	uint16_t intermediate = zeroOffsetSum % rangeModulo + rangeStart;
//
//	if (intermediate < rangeStart) {	// Fix underflow of uint8_t data type
//		addendMinuend = (uint8_t)(intermediate + rangeModulo);
//		return zeroOffsetSum / rangeModulo - 1;
//	} else if (intermediate > uint8_t_max) {
//		addendMinuend = (uint8_t)(intermediate - rangeModulo);
//		return zeroOffsetSum / rangeModulo + 1;
//	} else {
//		addendMinuend = (uint8_t)intermediate;
//		return zeroOffsetSum / rangeModulo;
//	}
//
//}

//uint16_t DateTime::modAddSub(uint16_t& addendMinuend, uint16_t addendSubtrahend, uint16_t rangeModulo, uint16_t rangeStart) {
//
//	// Range of allowable addendMinuend values is:
//	// rangeStart ... rangeStart + rangeModulo - 1
//
//	uint16_t zeroOffsetSum = addendMinuend + addendSubtrahend - rangeStart;
//	uint16_t intermediate = zeroOffsetSum % rangeModulo + rangeStart;
//
//	if (intermediate < rangeStart) {	// Fix underflow of uint8_t data type
//		addendMinuend = (uint8_t)(intermediate + rangeModulo);
//		return zeroOffsetSum / rangeModulo - 1;
//	} else if (intermediate > uint16_t_max) {
//		addendMinuend = (uint8_t)(intermediate - rangeModulo);
//		return zeroOffsetSum / rangeModulo + 1;
//	} else {
//		addendMinuend = (uint8_t)intermediate;
//		return zeroOffsetSum / rangeModulo;
//	}
//
//}

//uint8_t DateTime::subtract(uint8_t &minuendDifference, uint8_t subtrahend, uint8_t modulo, uint8_t floor) {
//
//	uint8_t zeroOffsetSum =
//}

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
uint16_t DateTime::year() const {
	return MIN_YEAR + _year;
}

//uint8_t DateTime::month() const {
//	return _month;
//}
//
//uint8_t DateTime::day() const {
//	return _day;
//}
//
//uint8_t DateTime::hour() const {
//	return _hour;
//}
//
//uint8_t DateTime::minute() const {
//	return _minute;
//}
//
//uint8_t DateTime::second() const {
//	return _second;
//}
//
//uint16_t DateTime::millisecond() const {
//	return _millisecond;
//}
//
//char* DateTime::toString() {
//	//http://arduino.cc/en/Reference/StringObject
//	String* output;
//	char* line;
//	//char* two;
////	output = new String();
//	//spruint16_tf(line, "%d", _year);	// WORKS
//	//_line = "Hello";
//	spruint16_tf(line, "%d", _year);	// No WORKS
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
//DateTime::DateTime(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second, uint16_t millisecond) {
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
//uint16_t DateTime::year() const {
//	return MIN_YEAR + _year;
//}
//
//uint8_t DateTime::month() const {
//	return _month;
//}
//
//uint8_t DateTime::day() const {
//	return _day;
//}
//
//uint8_t DateTime::hour() const {
//	return _hour;
//}
//
//uint8_t DateTime::minute() const {
//	return _minute;
//}
//
//uint8_t DateTime::second() const {
//	return _second;
//}
//
//uint16_t DateTime::millisecond() const {
//	return _millisecond;
//}
//
//boolean DateTime::isLeapYear(uint16_t year) {
//	//http://en.wikipedia.org/wiki/Leap_year
//	return (year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0));
//}
//
//boolean DateTime::isLeapYear() const {
//	return isLeapYear(year());
//}
//
//uint8_t DateTime::daysInMonth() const {
//	return daysInMonth(_month, year());
//}
//
//uint8_t DateTime::daysInMonth(uint8_t month, uint16_t year) {
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
//void DateTime::setAdjustment(uint8_t value) {
//	if (value > ADJUSTMENT_MASK) return;
//	_status &= ~ADJUSTMENT_MASK;
//	_status |= value;
//}
//
//uint8_t DateTime::getAdjustment() const {
//	return _status & ADJUSTMENT_MASK;
//}
//
//void DateTime::overflowed() {
//	setEpoch();
//	setStatus(Valid, false);
//	setStatus(Overflow, true);
//}
//
//uint16_t DateTime::daysInYear(uint16_t year) {
//	if (isLeapYear(year)) return 366;
//	return 365;
//}
//
//uint16_t DateTime::daysInYear() const {
//	return daysInYear(year());
//}
//
//DateTime& DateTime::addOneDay() {
//	if (_day < daysInMonth()) _day++;
//	else {
//		_day = 1;
//		addOneMonth();
//	}
//	return *this;
//}
//
//DateTime& DateTime::addOneMonth() {
//	// Precondition: Must not be used on days after 28th of any month
//	if (_month < MONTHS_PER_YEAR) _month++;
//	else {
//		_month = 1;
//		addOneYear();
//	}
//	return *this;
//}
//
//DateTime& DateTime::addOneYear() {
//	// Precondition: Must not be used on days after 28th of any month
//	if (year() < MAX_YEAR)
//		_year++;
//	else
//		overflowed();
//	return *this;
//}
//
//DateTime& DateTime::subtractOneDay() {
//	if (_day > 1) _day--;
//	else {
//		subtractOneMonth();
//		if(isValid()) _day = daysInMonth();
//	}
//	return *this;
//}
//
//DateTime& DateTime::subtractOneMonth() {
//	// Precondition: Must not be used on days after 28th of any month
//	if (_month > 1) _month--;
//	else {
//		subtractOneYear();
//		if(isValid()) _month = MONTHS_PER_YEAR;
//	}
//	return *this;
//}
//
//DateTime& DateTime::subtractOneYear() {
//	// Precondition: Must not be used on days after 28th of any month
//	if (year() > MIN_YEAR)
//		_year--;
//	else
//		overflowed();
//	return *this;
//}
//
//uint16_t DateTime::monthCarryBorrow(uint16_t& month) {
//	// Accepts a month of any positive or negative value.
//	// Restores 'month' to a number between 1 and 12
//	// Returns the number of years to carry/borrow.
//	uint16_t carryBorrow = 0;
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
//void DateTime::add(uint8_t& attribute, long& uint16_terval, uint16_t limit) {
//	// For attributes having a range 0 to (LIMIT - 1);
//	long magnitude = attribute + uint16_terval;
//	if (magnitude < 0) {
//		uint16_terval = magnitude / limit - 1;
//		magnitude -= uint16_terval * limit;
//	} else {
//		uint16_terval = magnitude / limit;
//	}
//	attribute = magnitude % limit;
//}
//
//DateTime& DateTime::add(long uint16_terval, Period period) {
//	if (!uint16_terval) return *this;
//	if (period == Millisecond) {
//		long magnitude = _millisecond + uint16_terval;
//		uint16_terval = magnitude / MILLISECONDS_PER_SECOND;
//		uint16_t newValue = magnitude % MILLISECONDS_PER_SECOND;
//		if (newValue < 0) {
//			_millisecond = newValue + MILLISECONDS_PER_SECOND;
//			uint16_terval -= 1;
//		} else {
//			_millisecond = newValue;
//		}
//		if (uint16_terval) period = Second;  // Milliseconds cascade to Seconds
//	}
//	if (period == Second) {
//		add(_second, uint16_terval, SECONDS_PER_MINUTE);
//		if (uint16_terval) period = Minute;  // Seconds cascade to Minutes
//	}
//	if (period == Minute) {
//		add(_minute, uint16_terval, MINUTES_PER_HOUR);
//		if (uint16_terval) period = Hour;    // Minutes cascade to Hours
//	}
//	if (period == Hour) {
//		add(_hour, uint16_terval, HOURS_PER_DAY);
//		if (uint16_terval) period = Day;     // Hours cascade to Days
//	}
//
//	// DAYS
//	if (period == Day) {
//		if (uint16_terval < 0) { // go backwards
//			// 1. Get back to the first of the month if you can
//			while (_day > 1) {
//				uint16_terval++;
//				subtractOneDay();
//				if (!isValid()) uint16_terval = 0; // Underflow.
//				if (!uint16_terval) break;
//			}
//			// 2. Jump by months to January
//			while (uint16_terval && _month > 1) {
//				uint16_t priorMonth = _month - 1;
//				uint16_t priorYear = year() + monthCarryBorrow(priorMonth);
//				if (daysInMonth(priorMonth, priorYear) <= -uint16_terval) {
//					subtractOneMonth();
//					uint16_terval += daysInMonth();
//					if (!isValid()) uint16_terval = 0; // Underflow.
//				} else break;
//			}
//			// 3. Jump by years if you can
//			uint16_t daysPriorYear = daysInYear(year() - 1);
//			while (-uint16_terval >= daysPriorYear) {
//				uint16_terval += daysPriorYear;
//				subtractOneYear();
//				if (!isValid()) uint16_terval = 0; // blew it. Overflowed.
//				daysPriorYear = daysInYear(year() - 1);
//			}
//			// 4. Jump by months if you can
//			while (-uint16_terval >= daysInMonth()) {
//				subtractOneMonth();
//				uint16_terval += daysInMonth();
//				if (!isValid()) uint16_terval = 0; // blew it. Overflowed.
//			}
//			// 5. Jump by days to finish off
//			while (uint16_terval) {
//				uint16_terval++;
//				subtractOneDay();
//				if (!isValid()) uint16_terval = 0; // blew it. Overflowed.
//			}
//		} else {  // go forward
//			// 1. Get to the first of next month if you can
//			while (_day > 1) {
//				uint16_terval--;
//				addOneDay();
//				if (!isValid()) uint16_terval = 0; // blew it. Overflowed.
//				if (!uint16_terval) break;
//			}
//			// 2. Jump by months to January
//			while (uint16_terval && _month > 1) {
//				if (uint16_terval >= daysInMonth()) {
//					uint16_terval -= daysInMonth();
//					addOneMonth();
//					if (!isValid()) uint16_terval = 0; // blew it. Overflowed.
//				} else {
//					_day += uint16_terval;
//					uint16_terval = 0;
//					break;
//				}
//			}
//			// 3. Jump by years if you can
//			while (uint16_terval >= daysInYear()) {
//				uint16_terval -= daysInYear();
//				addOneYear();
//				if (!isValid()) uint16_terval = 0; // blew it. Overflowed.
//			}
//			// 4. Jump by months if you can
//			while (uint16_terval >= daysInMonth()) {
//				uint16_terval -= daysInMonth();
//				addOneMonth();
//				if (!isValid()) uint16_terval = 0; // blew it. Overflowed.
//			}
//			// 5. Jump by days to finish off
//			while (uint16_terval) {
//				uint16_terval--;
//				addOneDay();
//				if (!isValid()) uint16_terval = 0; // blew it. Overflowed.
//			}
//		}
//	}
//
//	if (period == Month) { // Days DON'T cascade uint16_to Months
//		add(_month, uint16_terval, MONTHS_PER_YEAR);  // TODO: Doesn't work for months 1-12
//		if (uint16_terval != 0) period = Year;
//	}
//
//	if (period == Year) { // Months cascade uint16_to years
//		long testYear = uint16_terval + year();
//		if (testYear > MAX_YEAR || testYear < MIN_YEAR) overflowed();
//		else _year += uint16_terval;
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
//char* DateTime::uint16_tToString(uint16_t value) {
//	static char ramBuffer[10];
//	spruint16_tf(ramBuffer, "%d", value);
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
//		*output += uint16_tToString(year());
//		*output += '-';
//		if (_month < 10) *output += '0';
//		*output += uint16_tToString(_month);
//		*output += '-';
//		if (_day < 10) *output += '0';
//		*output += uint16_tToString(_day);
//		*output += ' ';
//		if (_hour < 10) *output += '0';
//		*output += uint16_tToString(_hour);
//		*output += ':';
//		if (_minute < 10) *output += '0';
//		*output += uint16_tToString(_minute);
//		*output += ':';
//		if (_second < 10) *output += '0';
//		*output += uint16_tToString(_second);
//		*output += '.';
//		if (_millisecond < 100) *output += '0';
//		if (_millisecond < 10) *output += '0';
//		*output += uint16_tToString(_millisecond);
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
