#include "std_lib_facilities.h"
#include "Chrono.h"

enum class Genre
{
	fiction, nonfiction, periodical, biography, children
};

class Book
{
	// Its a book class, like for a library software
	// Has members for the ISBN, title, author, and copyright date.
	// Also stores data on whether the book is checked out.
	// Create functions to return these values.
	// Also create functions to check them in and out. 
	// Perform simple validation such as ISBN can only be n-n-n-x where n is an integer and x is a digit or a letter.
	// ISBN is a string 

public:
	Book(string isbn, string t, string a, Chrono::Date d, bool checked, Genre g); // constructor 
	Book(); // Default constructor. 

	string get_ISBN() const;

	string get_title() const;

	string get_author() const;

	Chrono::Date get_date() const;

	bool checked() const;


	void check_in();

	void check_out();

	bool validate() const;

private:
	string ISBN;
	string title;
	string author;
	Chrono::Date copyright;
	bool checked_in;
	Genre genre; 

};

bool operator==(const Book& a, const Book& b);

bool operator!=(const Book& a, const Book& b);

ostream& operator<<(ostream& os, const Book& b);
