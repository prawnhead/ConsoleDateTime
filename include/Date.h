#ifndef DATE_H
#define DATE_H

#include <stdio.h>

class Date
{
    public:
        // Enumerations
        enum Period { Year, Month, Day };

        // Constructors & Destructor
        Date();
        Date(short day, short month, short year);
        virtual ~Date();

        // Property Getters
        short getDay();
        short getMonth();
        short getYear();
        char* toString();
        bool isLeapYear();
        short daysInMonth();

        // Mutators
        void increment(Period period);
        void decrement(Period period);
        short adjust(Period period, int value);
        short correct();

        // Functions
        static bool isLeapYear(short year);
        static short daysInMonth(short month, short year);
        static int moduloArithBaseZero(short& value, int addend, short modulo);
        static int moduloArithBaseOne(short& value, int addend, short modulo);

    protected:

    private:

        // Constants
        const short Min_Year = 1;
        const short Max_Year = 9999;
        const short Min_Month = 1;
        const short Max_Month = 12;
        const short Min_Day = 1;
        const short Year_Modulo = 9999;

        // Properties
        short year, month, day;
        static char text[11];

};

#endif // DATE_H
