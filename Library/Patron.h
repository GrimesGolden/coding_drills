#pragma once
#include "std_lib_facilities.h"
#include "Chrono.h"

class Patron
{
public:
	Patron();

	void set_fee(double f);
	string get_name() const;
	string get_card() const;
	double get_fee() const; 
	bool fee() const;

private:
	string name;
	string card_num;
	double fees; 
	bool has_fee; 
};

bool valid_card(string card);
