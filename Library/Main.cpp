// Library.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "std_lib_facilities.h"
#include "Chrono.h"
#include "Book.h"

int main()
{
    Chrono::Date today{2025, Chrono::Month::jan, 8};
    Book random_book{};
    Book other_book{ "1-2-3-3-F", "Chuck Fucklesons Guide to Hunting Rats", "Chuck Fuckleson", today, false , Genre::fiction};

    if (random_book.validate())
    {   
        cout << random_book.get_ISBN();
        cout << "\nYeah it's valid\n";
    }
    else if (!random_book.validate())
    {
        cout << random_book.get_ISBN();
        cout << "\nNah it ain't valid.\n";
    }
    
}