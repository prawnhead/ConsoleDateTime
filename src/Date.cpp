#include "Date.h"

using namespace std;

char Date::text[11] = "XXXX-XX-XX";

Date::Date()
{
    year = 1;   // Year:    0001
    month = 1;  // Month:   January
    day = 1;    // Day:     1st
}

Date::Date(short year, short month, short day)
{
    this->year = year;
    this->month = month;
    this->day = day;
}

short Date::getDay() {
    return day;
}

short Date::getMonth() {
    return month;
}

short Date::getYear() {
    return year;
}

char* Date::toString() {
    sprintf(Date::text, "%04d-%02d-%02d", year, month, day);
    return text;
}

bool Date::isEqual(Date other) {
    return year == other.getYear() && month == other.getMonth() && day == other.getDay();
}

bool Date::isEqual(Date* other) {
    return isEqual(*other);
}

bool Date::isBefore(Date other) {
    if (year < other.getYear()) return true;
    if (month < other.getMonth()) return true;
    if (day < other.getDay()) return true;
    return false;
}

bool Date::isBefore(Date* other) {
    return isBefore(*other);
}

bool Date::isLeapYear(short year) {
    return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}

bool Date::isLeapYear() {
    return isLeapYear(year);
}

void Date::incrementUnsafe(Period period) {
    switch (period) {
    case Year:
        if (year == Max_Year)
            year = Min_Year;
        else
            year++;
        break;
    case Month:
        if (month == Max_Month) {
            increment(Date::Year);
            month = Min_Month;
        } else
            month++;
        break;
    case Day:
        if (day == daysInMonth()) {
            increment(Date::Month);
            day = Min_Day;
        } else
            day++;
        break;
    }
}

short Date::increment(Period period) {
    incrementUnsafe(period);
    if (period == Date::Day)
        return 0;
    else
        return correct();
}

void Date::decrementUnsafe(Period period) {
    switch (period) {
    case Year:
        if (year == Min_Year)
            year = Max_Year;
        else
            year--;
        break;
    case Month:
        if (month == Min_Month) {
            decrement(Date::Year);
            month = Max_Month;
        } else
            month--;
        break;
    case Day:
        if (day == Min_Day) {
            decrement(Date::Month);
            day = daysInMonth();
        } else
            day--;
        break;
    }
}

short Date::decrement(Period period) {
    decrementUnsafe(period);
    if (period == Date::Day)
        return 0;
    else
        return correct();
}

short Date::daysInMonth(short month, short year) {
    switch (month) {
        case 1: return 31;
        case 2: return Date::isLeapYear(year) ? 29 : 28;
        case 3: return 31;
        case 4: return 30;
        case 5: return 31;
        case 6: return 30;
        case 7: return 31;
        case 8: return 31;
        case 9: return 30;
        case 10: return 31;
        case 11: return 30;
        case 12: return 31;
    }
    return 0;   // error
}

short Date::daysInMonth() {
    return daysInMonth(month, year);
}

short Date::moduloArithBaseZero(short& value, short addend, short modulo) {
    // Parameters - input
    // value  - if valid, value is between zero and (modulo - 1)
    //          Passed by reference and is an in/out parameter.
    // addend - can be any value
    // modulo - can be any value but large expected values are
    //          1000 for milliseconds and 9999 for years.
    // Parameter - output. Carry/borrow output from arithmetic operation.
    short inter = value + addend;
    // inter will over/underflow when (value + addend) exceeds short int limits.
    // This will give incorrect results, but is a known limitation.
    short carry = inter / modulo;
    // carry cannot overflow but can cause divide-by-zero error if modulo = 0.
    value = inter % modulo;
    // value cannot overflow. Produces value in range -(modulo - 1) to (modulo - 1)
    if (value < 0) {
        carry--;
        value += modulo;
    }
    // value now in the range zero to (modulo - 1)
    return carry;
}

short Date::moduloArithBaseOne(short& value, short addend, short modulo) {
    // Translates to/from zero based arithmetic.
    value--;
    short carry = moduloArithBaseZero(value, addend, modulo);
    value++;
    return carry;
}

short Date::adjust(Period period, int value) {
    if (value == 0) return 0;
    short days = daysInMonth() - day;
    switch (period) {
    case Year:
        // Years will wrap-around with no carry/borrow.
        moduloArithBaseOne(year, value, Year_Modulus);
        return correct();
    case Month:
        // Months will carry/borrow years.
        return adjust(Date::Year, moduloArithBaseOne(month, value, Month_Modulus));
    case Day:
        if (value > 0) {
            // Handle case where month is not incremented
            if (value <= days) {
                day += value;
                return 0;
            }
            // Get to first of next month
            value -= days + 1;
            day = 1;
            incrementUnsafe(Date::Month);
            // Step one month at a time.
            days = daysInMonth();
            while(value >= days) {
                value -= days;
                incrementUnsafe(Date::Month);
                days = daysInMonth();
            }
            day += value;
        } else {
            // Handle case where month is not decremented
            if (-value < day) {
                day += value;
                return 0;
            }
            // Step to last of prior month.
            value += day;
            day = 1;
            decrement(Date::Day);
            days = daysInMonth();
            while(-value >= days) {
                value += days;
                day = 1;
                decrement(Date::Day);
                days = daysInMonth();
            }
            day += value;
        }
        return 0;
    default:
        printf("Date::adjust() not implemented for that period\n");
    }
}

short Date::correct() {
    short days = daysInMonth();
    short adjust = 0;
    if(day > days) {
        adjust = day - days; // want negative value
        day = days;
    }
    return adjust;
}
