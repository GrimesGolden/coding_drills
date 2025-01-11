#pragma once
#include "std_lib_facilities.h";
#include "Chrono.h";

// Create a Patron class for the library
// The class will have a users name
// Library card #
// Library fees (if owed)
// Have function that access this data as well as a function to set the fee of the user.
// Have a helper function that returns a boolean depending on whether or not the user owes a fee. 
class Patron
{
public:
	Patron();

	void set_fee(double f);
	string get_name() const;
	string get_card() const;
	double get_fee() const; 

private:
	string name;
	string card_num;
	double fees; 
	bool has_fee; 
};

