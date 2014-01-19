#ifndef DATE_H
#define DATE_H

#include <stdio.h>


/**
 * @file    Date.h
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
 * The Date class implements a Gregorian calendar. Please note that
 * while this calendar has been implemented for the year range 0001
 * to 9999 the Gregorian calendar was not invented, nor implemented
 * in earlier years and will possibly not apply into the future as
 * far as the year 9999. It is, however, accurate and useful for
 * the 21st century and a few centuries either side of it.
 */

class Date
{

public:

protected:

private:

//  /\ Untested
// ==========================================================================
//  \/ Tested

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

};

#endif // DATE_H
