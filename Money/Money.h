#pragma once
#include "std_lib_facilities.h"
// Represent a monetary amount as a number of cents in a long int. 
// But input and output as dollars and cents. 
class Money
{
public:
	Money();
	Money(long int numb);
	Money(string curr, long int numb);
	~Money();
	long int cents() const { return c; }
	string currency() const { return monetary_unit; }
private:
	long int c; 
	string monetary_unit; 
};

// Operator overloads
ostream& operator<<(ostream& os, const Money& m);
Money operator+(Money l, Money r);
Money operator-(Money l, Money r);

// Helper functions
Money convert(Money m);
int truncate_cents(double d);