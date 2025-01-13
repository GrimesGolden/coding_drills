#include "Patron.h";
#include "std_lib_facilities.h"

// Still need a function to validate the library card (it should be all numbers with length 6)
// Also need a default constructor, similar to what we have with the book class. 

void Patron::set_fee(double f)
{
	fees == f;
}

string Patron::get_name() const
{
	return name;
}

string Patron::get_card() const
{
	return card_num;
}

double Patron::get_fee() const
{
	if (has_fee)
	{
		return fees;
	}
	else
	{
		return 0; 
	}
}

bool valid_card(string card)
{
	// Only valid card numbers have 6 numbers.
	// No letters or special symbols. 
	if (card.size() != 6)
	{
		return false;
	}

	for (char c : card)
	{
		if (!isdigit(c))
		{
			return false;
		}
	}

	return true;
}

Patron::Patron()
	:name{"Default Patron"}, card_num{"123456"}, fees{0}, has_fee{false}
{
	if (!valid_card(card_num))
	{
		error(" Invalid card number.");
	}
}