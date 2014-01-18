#include "Date.h"

using namespace std;

char Date::text[11] = "XXXX-XX-XX";

Date::Date()
{
    year = 1;
    month = 1;
    day = 1;
}

Date::Date(short day, short month, short year)
{
    this->year = year;
    this->month = month;
    this->day = day;
}

Date::~Date()
{
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

void Date::increment(Period period) {
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

void Date::decrement(Period period) {
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

bool Date::isLeapYear(short year) {
    return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}

bool Date::isLeapYear() {
    return isLeapYear(year);
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

int Date::moduloArithBaseZero(short& value, int addend, short modulo) {
    int inter = value + addend;
    int carry = inter / modulo;
    value = inter % modulo;
    if (value < 0) {
        carry--;
        value += modulo;
    }
    return carry;
}

int Date::moduloArithBaseOne(short& value, int addend, short modulo) {
    value--;
    int carry = moduloArithBaseZero(value, addend, modulo);
    value++;
    return carry;
}

short Date::adjust(Period period, int value) {
    switch (period) {
    case Year:
        moduloArithBaseOne(year, value, Year_Modulo);
        correct();
        break;
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
