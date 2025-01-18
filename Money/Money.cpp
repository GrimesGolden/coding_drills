#include "std_lib_facilities.h"
#include "Money.h"

Money::Money(long int numb) : 
	monetary_unit{ "USD" }, c {numb}
{
}

Money::Money(string curr, long int numb) :
	monetary_unit{curr}, c{numb}
{
}

Money::Money() : c{ 100 }
{
}

Money::~Money()
{

}

ostream& operator<<(ostream& os, const Money& m)
{

	os << m.currency() << m.cents() / 100;

	// Rounding logic (could use refactor)
	if (m.cents() % 100 <= 0)
	{
		os << "." << 0 << 0;
	}
	else if (m.cents() % 100 <= 9)
	{
		os << "." << 0 << m.cents() % 100;
	}
	else
	{
		os << "." << m.cents() % 100;
	}

	return os; 
}

Money operator+(Money l, Money r)
{
	long int result = l.cents() + r.cents();

	Money value{ result };

	return value; 
}


Money operator-(Money l, Money r)
{
	long int result = l.cents() - r.cents();

	Money value{ result };

	return value;
}

Money convert(Money m)
{	
	// COnversion tables
	const vector<string> currencies = { "EUR", "GBP", "JPY"};
	const vector<double> conversion_factors = { 1.02737, 1.21697, 0.00639729 };

	if (m.currency() == "USD")
	{
		// If USD, then no need to convert.
		return m;
	}
	else
	{
		// Search for for the currency in the list of possible conversion.
		for (int i = 0; i < currencies.size(); ++i)
		{
			// If a match is found. 
			if (m.currency() == currencies[i])
			{
				
				// Round off to whole dollars.
				double dollars = m.cents() / 100;
				// Multiply by the conversion factor.
				dollars *= conversion_factors[i];
				// Cast these converted whole units back into integers. 
				int result = static_cast<int>(dollars);
				//$1 == 100 cents, we must turn the result back into cents.
				result *= 100;
				result += truncate_cents(dollars);
				// Dont forget to collect the remaing cents (those which are not whole dollars)
				// We don't conver these, there arent really conversion factors for single cents. 
				result += m.cents() % 100;
				return Money{ "USD", result };
			}
		}
	}
	cout << "No conversion factor found.\n";
	return m; 
}

int truncate_cents(double d)
{	
	// This function removes the decimal portion from the double.
	int whole;
	double cents;
	double result = modf(d, &cents);
	// Multiply 100 to turn decimal portion (for example 0.36, int whole cents (36). 
	result *= 100; 
	// Here, the decimal portion is converted to a double (result).
	// This is now multipled by 100 and cast back to an int 
	// The entire effect is that of removing the cents portion from dollars variable in convert() function, and returning it as whole cents. 
	// This would be lost otherwise. 
	int final_value = static_cast<int>(result);
	return final_value;
}