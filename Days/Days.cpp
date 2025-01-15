// Days.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// Change the representation of a Date to be the number of says since January 1, 1970, represented as next_workday();
// Reimplement the functions from 9.8

#include "std_lib_facilities.h"
#include "Chrono.h"
using namespace Chrono;

int main()
{
    Date today{ 2006, Month::mar, 27 }; 

    cout << "Today is " << today << " and that is " << today.days_since() << " days since January 1st 1970\n The day of the week is " << day_of_week(today);

}