/**
 * @file    Time.h
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
 * The Time class represents an instant of clock time with
 * millisecond resolution. It uses standard 24 hours per day time.
 */

#ifndef TIME_H
#define TIME_H

#include <stdio.h>
#include "DateTime.h"

#ifndef ARDUINO
    #define int short
#endif

class Time
{

public:

protected:

private:

//  /\ Untested
// ==========================================================================
//  \/ Tested

private:

    // Constants
    static const int Hour_Min = 0;
    static const int Hour_Max = 23;
    static const int Hour_Modulus = 24;
    static const int Minute_Min = 0;
    static const int Minute_Max = 59;
    static const int Minute_Modulus = 60;
    static const int Second_Min = 0;
    static const int Second_Max = 59;
    static const int Second_Modulus = 60;
    static const int Millisecond_Min = 0;
    static const int Millisecond_Max = 999;
    static const int Millisecond_Modulus = 1000;

    // Properties
    int hour, minute, second, millisecond;
    static char text[13];

protected:

public:

    // Enumerations
    enum Period { Hour, Minute, Second, Millisecond };

    // Constructors and destructor
    Time();
    Time(int hour, int minute, int second, int millisecond);

    // Property getters
    int getHour();
    int getMinute();
    int getSecond();
    int getMillisecond();
    char* toString();

    bool isEqual(Time other);
    bool isEqual(Time* other);
    bool isBefore(Time other);
    bool isBefore(Time* other);

};

#endif // TIME_H
