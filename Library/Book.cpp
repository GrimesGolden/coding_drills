#include "Book.h"
#include "std_lib_facilities.h"
#include "Chrono.h"

string Book::get_ISBN() const
{
	return ISBN;
}

string Book::get_title() const
{
	return title;
}
string Book::get_author() const
{
	return author;
}

Chrono::Date Book::get_date() const
{
	return copyright;
}

bool Book::checked() const
{
	return checked_in;
}

void Book::check_in() 
{
	checked_in = true;
}

void Book::check_out()
{
	checked_in = false;
}

Book& const default_book()
// Create a default book in order to return values. 
{
	static Book db {"1-2-3-A", "A Default Book", "Default Author", Chrono::Date(), false, Genre::nonfiction}; // start of 21st century
	return db;
}

Book::Book()
// Utilizes the default book function to preload the Book class with default valyes. 
	: ISBN{ default_book().get_ISBN()}, title{ default_book().get_title() }, author{default_book().get_author()}, copyright{default_book().get_date()}, checked_in{default_book().checked()}
{
	//if (!is_date(yy, mm, dd)) throw Invalid{};
	// This should actually check for a valid ISBN and Date I believe. 
	if (!Chrono::is_date(copyright.year(), copyright.month(), copyright.day()) || !valid_isbn(ISBN))
	{
		error("Invalid date or isbn detected.\n");
	}
}

Book::Book(string isbn, string t, string a, Chrono::Date d, bool checked, Genre g)
	: ISBN{ isbn }, title{ t }, author{ a }, copyright{ d }, checked_in{ checked }, genre{ g }
// Utilizes user input to initalize the Book object. 
{
	if (!Chrono::is_date(copyright.year(), copyright.month(), copyright.day()) || !valid_isbn(ISBN))
	{
		error("Invalid date or isbn detected.\n");
	}
}

bool operator==(const Book& a, const Book& b)
{
	return (a.get_ISBN() == b.get_ISBN());
}

bool operator!=(const Book& a, const Book& b)
{
	return !(a==b);
}

ostream& operator<<(ostream& os, const Book& b)
{
	os << "Title: " << b.get_title() << "\n" << "Author: " << b.get_author() << "\nISBN: " << b.get_ISBN() << "\nCopyright: " << b.get_date() << "\n";
	return os; 
}

bool valid_isbn(const string isbn)
{
	if (isbn.size() != 7)
	{
		// Only valid ISBN are 7 chars
		// If the last index is not alphanumeric, return false. 
		return false;
	}

	for (int i = 0; i < 6; ++i)
	{
		if (i % 2 == 0 && !isdigit(isbn[i]) || i % 2 != 0 && isbn[i] != '-')
			// If even and not a digit or odd and not a dash, then its false by definition of format. 
		{
			return false;
		}
	}

	// If we made it this far, then there can only be the last digit remaining.
	if (isdigit(isbn[isbn.size() - 1]) || isalpha(isbn[isbn.size() - 1]))
	{
		return true;
	}
	else
	{
		return false;
	}
}