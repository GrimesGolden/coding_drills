// Days.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// Change the representation of a Date to be the number of says since January 1, 1970, represented as next_workday();
// Reimplement the functions from 9.8

#include "std_lib_facilities.h"
#include "Chrono.h"
using namespace Chrono;

int main()
{
    Date today{ 2025, Month::jan, 14 };

    cout << today; 
    cout << "adding 3246 days\n";
    today.add_day(7);
    cout << "success" << today;
}