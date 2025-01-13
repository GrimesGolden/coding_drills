// Library.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "std_lib_facilities.h"
#include "Chrono.h"
#include "Book.h"

int main()
{
    try
    {

        Chrono::Date today{2025, Chrono::Month::jan, 13};
        Book random_book{};
        Book other_book{ "1-3-3-A", "Chuck Fucklesons Guide to Hunting Rats", "Chuck Fuckleson", today, false , Genre::fiction };

        if (other_book.validate())
        {
            cout << other_book.get_ISBN();
            cout << "\nYeah it's valid\n";
        }
        else if (!other_book.validate())
        {
            cout << other_book.get_ISBN();
            cout << "\nNah it ain't valid.\n";
        }

        cout << random_book << "\n";
        cout << other_book;

        random_book.get_date().add_day(35); //You can add days all you want, but it won't effect the actual value, because get_date only returns a value. 

        cout << random_book;

    }
    catch (const std::exception& e)
    {
        cout << e.what() << "\n";
    }

}