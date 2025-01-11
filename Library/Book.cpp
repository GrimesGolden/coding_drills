#include "std_lib_facilities.h"
#include "Chrono.h"
#include "Book.h"

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

bool Book::validate() const
{
	//Perform simple validation such as ISBN can only be n - n - n - x where n is an integer and x is a digit or a letter. 
	bool valid = true;

	if (ISBN.size() != 7 || !isalpha(ISBN[ISBN.size() - 1]))
	{
		// Only valid ISBN are 7 chars
		// If the last index is not alphanumeric, return false. 
		return false;
	}

	for (int i = 0; i < 6; ++i)
	{
		if (i % 2 == 0 && !isdigit(ISBN[i]) || i % 2 != 0 && ISBN[i] != '-')
		{ 
			return false; 
		}
	}

	return true;
}

Book::Book(string isbn, string t, string a, Chrono::Date d, bool checked, Genre g)
	: ISBN{ isbn }, title{ t }, author{ a }, copyright{ d }, checked_in { checked }, genre{ g }
{
	//if (!is_date(yy, mm, dd)) throw Invalid{};
}

Book& const default_book()
// Create a default book in order to return values. 
{
	static Book db {"1-2-3-A", "A Default Book", "John Smith", Chrono::Date(), false, Genre::nonfiction}; // start of 21st century
	return db;
}

Book::Book()
	: ISBN{ default_book().get_ISBN()}, title{ default_book().get_title() }, author{default_book().get_author()}, copyright{default_book().get_date()}, checked_in{default_book().checked()}
{
	//if (!is_date(yy, mm, dd)) throw Invalid{};
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