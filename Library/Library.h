#pragma once
#include "std_lib_facilities.h"
#include "Chrono.h"
#include "Patron.h"
#include "Book.h"

class Library
// Create a library class
{
public:
	void add_book(Book book);
	void add_patron(const Patron patron);
	void check_out(Book book, Patron patron, Chrono::Date date); 
	vector<Patron> list_debts();

private:
	struct Transaction
	{
		// Include a struct called Transaction
		// Have it onclude a Book, a Patron and a Date from the chapter.
		Book book;
		Patron patron;
		Chrono::Date date;
	};

	vector<Book> books;
	vector<Patron> patrons;
	vector<Transaction> transactions;
};