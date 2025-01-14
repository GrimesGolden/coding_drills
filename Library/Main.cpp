// Library.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Chrono.h"
#include "Book.h"
#include "Library.h"

int main()
{
    try
    {

        Chrono::Date today{2025, Chrono::Month::jan, 13};
        Book default_book{};
        Book other_book{ "1-3-3-A", "Chuck Fucklesons Guide to Hunting Rats", "Chuck Fuckleson", today, false , Genre::fiction };
        Book another_book{ "1-2-3-A", "A Skeptics Guide to Skepticism", "Lord Bigglesworth", today, false , Genre::fiction };
        Book a_book{ "1-2-3-B", "Gysops Fables", "Count Frack", today, false , Genre::fiction };

        Library library; 
        Patron some_guy; 

        library.add_book(default_book); // Adding books to library
        library.add_book(other_book);
        library.add_book(another_book);
        library.add_book(a_book);
        library.add_patron(some_guy); // Adding patron to library

        library.check_out(default_book, some_guy, today); // Checking out book from the library. 
    }

    catch (const std::exception& e)
    {
        cout << e.what() << "\n";
    }

}