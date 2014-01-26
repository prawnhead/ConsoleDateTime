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

#ifndef DATE_H
#define DATE_H

#include <stdio.h>
#include "DateTime.h"

#ifndef ARDUINO
    #define int short
#endif

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
    static const int Year_Min = 1;
    static const int Year_Max = 9999;
    static const int Year_Modulus = 9999;
    static const int Month_Min = 1;
    static const int Month_Max = 12;
    static const int Month_Modulus = 12;
    static const int Min_Day = 1;

    // Properties
    int year, month, day;
    static char text[11];

protected:

public:

    // Enumerations
    enum Period { Year, Month, Day };

    // Constructors and destructor
    Date();
    Date(int year, int month, int day);

    // Property getters
    int getDay();
    int getMonth();
    int getYear();
    char* toString();

    bool isEqual(Date other);
    bool isEqual(Date* other);
    bool isBefore(Date other);
    bool isBefore(Date* other);
    bool isLeapYear();
    int daysInMonth();

    // Mutators
    int correct();
    int increment(Period period);
    int decrement(Period period);
    void incrementUnsafe(Period period);
    void decrementUnsafe(Period period);
    int adjust(Period period, int value);

    // Functions
    static bool isLeapYear(int year);
    static int daysInMonth(int month, int year);

};

#endif // DATE_H
