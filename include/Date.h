#ifndef DATE_H
#define DATE_H

#include <stdio.h>

class Date
{
private:

    // Constants
    const short Min_Year = 1;
    const short Max_Year = 9999;
    const short Min_Month = 1;
    const short Max_Month = 12;
    const short Min_Day = 1;
    const short Year_Modulus = 9999;
    const short Month_Modulus = 12;

    // Properties
    short year, month, day;
    static char text[11];

protected:

public:

    // Enumerations
    enum Period { Year, Month, Day };

    // Constructors and destructor
    Date();
    Date(short year, short month, short day);

    // Property Getters
    short getDay();
    short getMonth();
    short getYear();
    char* toString();
    bool isEqual(Date other);
    bool isEqual(Date* other);
    bool isBefore(Date other);
    bool isBefore(Date* other);
    bool isLeapYear();
    short daysInMonth();

    // Mutators
    short correct();
    short increment(Period period);
    short decrement(Period period);
    void incrementUnsafe(Period period);
    void decrementUnsafe(Period period);
    short adjust(Period period, int value);

    // Functions
    static bool isLeapYear(short year);
    static short daysInMonth(short month, short year);
    static short moduloArithBaseZero(short& value, short addend, short modulo);
    static short moduloArithBaseOne(short& value, short addend, short modulo);

//  /\ Tested
// ==========================================================================
//  \/ Untested

public:

protected:

private:

};

#endif // DATE_H
