#include "Date.h"

using namespace std;

char Date::text[11] = "XXXX-XX-XX";

Date::Date() {
    year = 1;   // Year:    0001
    month = 1;  // Month:   January
    day = 1;    // Day:     1st
    printf("sizeof(int) = %d\n", sizeof(int));
}

Date::Date(int year, int month, int day) {
    this->year = year;
    this->month = month;
    this->day = day;
}

int Date::getDay() {
    return day;
}

int Date::getMonth() {
    return month;
}

int Date::getYear() {
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

bool Date::isLeapYear(int year) {
    return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}

bool Date::isLeapYear() {
    return isLeapYear(year);
}

void Date::incrementUnsafe(Period period) {
    switch (period) {
    case Year:
        if (year == Year_Max)
            year = Year_Min;
        else
            year++;
        break;
    case Month:
        if (month == Month_Max) {
            increment(Date::Year);
            month = Month_Min;
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

int Date::increment(Period period) {
    incrementUnsafe(period);
    if (period == Date::Day)
        return 0;
    else
        return correct();
}

void Date::decrementUnsafe(Period period) {
    switch (period) {
    case Year:
        if (year == Year_Min)
            year = Year_Max;
        else
            year--;
        break;
    case Month:
        if (month == Month_Min) {
            decrement(Date::Year);
            month = Month_Max;
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

int Date::decrement(Period period) {
    decrementUnsafe(period);
    if (period == Date::Day)
        return 0;
    else
        return correct();
}

int Date::daysInMonth(int month, int year) {
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

int Date::daysInMonth() {
    return daysInMonth(month, year);
}

int Date::adjust(Period period, int value) {
    if (value == 0) return 0;
    int days = daysInMonth() - day;
    switch (period) {
    case Year:
        // Years will wrap-around with no carry/borrow.
        DateTime::moduloArithBaseOne(year, value, Year_Modulus);
        return correct();
    case Month:
        // Months will carry/borrow years.
        return adjust(Date::Year, DateTime::moduloArithBaseOne(month, value, Month_Modulus));
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

int Date::correct() {
    int days = daysInMonth();
    int adjust = 0;
    if(day > days) {
        adjust = day - days; // want negative value
        day = days;
    }
    return adjust;
}
