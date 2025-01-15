// Days.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// Change the representation of a Date to be the number of says since January 1, 1970, represented as next_workday();
// Reimplement the functions from 9.8

#include "std_lib_facilities.h"
#include "Chrono.h"
using namespace Chrono;

void verbose_print(Date& d)
{
    cout << "Today is " << d << " and that is " << d.days_since() << " days since January 1st 1970\n The day of the week is " << day_of_week(d);
    cout << "\n The next sunday falls on " << next_Sunday(d) << "\n";
    cout << "The next weekday is on " << next_weekday(d) << " which is a " << day_of_week(next_weekday(d)) << "\n";
}

int main()
{
    Date today{ 2026, Month::jan, 14 }; 

    verbose_print(today);
}