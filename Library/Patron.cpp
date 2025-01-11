#include "Patron.h";

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