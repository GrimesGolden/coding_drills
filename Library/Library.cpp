#include "Patron.h"
#include "Library.h"
#include "Chrono.h"
#include "Book.h"
void Library::add_book(Book book)
{
	if (valid_isbn(book.get_ISBN()))
	{
		books.push_back(book);
	}
	else
	{
		error("Invalid ISBN");
	}
}
void Library::add_patron(const Patron patron)
{
	if (valid_card(patron.get_card()))
	{
		patrons.push_back(patron);
	}
	else
	{
		error("Invalid library card number.");
	}
}
void Library::check_out(Book book, Patron patron, Chrono::Date date)
{
	// We need to look through the library, see if the patron is in the list of patrons. 
	// Then we need to look through the list of books and see if they are in there. 

	bool valid_patron = false;
	bool valid_book = false;

	for (const Patron& p : patrons)
	{
		if (patron.get_card() == p.get_card())
		{
			valid_patron = true;
			break;
		}
	}

	for (const Book& b : books)
	{
		if (b == book)
		{
			valid_book = true;
			break;
		}
	}

	if (!valid_patron || !valid_book)
	{
		error("Invalid book or patron in check_out.\n");
	}

	if (patron.fee())
	{
		error("Patron owes a fee.");
	}

	Transaction new_transaction;
	new_transaction.book = book;
	new_transaction.date = date; 
	new_transaction.patron = patron;

	transactions.push_back(new_transaction); 
	patron.set_fee(5);
}

vector<Patron> Library::list_debts()
{
	vector<Patron> debts;

	for (int i = 0; i < patrons.size(); ++i)
	{
		if (patrons[i].fee())
		{
			debts.push_back(patrons[i]);
		}
	}

	return debts; 
}
