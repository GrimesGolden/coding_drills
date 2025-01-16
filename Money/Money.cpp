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
	const vector<string> currencies = { "EUR" };
	const vector<double> conversion_factors = { 1.03012 };

	if (m.currency() == "USD")
	{
		return m;
	}
	else
	{
		for (int i = 0; i < currencies.size(); ++i)
		{
			if (m.currency() == currencies[i])
			{
				double dollars = m.cents() / 100;
				cout << "This many euros " << dollars << "\n";
				dollars *= conversion_factors[i];
				cout << "Converts to " << dollars << " dollars\n";
				int result = static_cast<int>(dollars);
				cout << "Now the result is " << result << "\n"; // The result in whole USD.
				result *= 100; // $1 == 100 cents, we must turn the result back into cents. 
				result += truncate_cents(dollars);
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
	int whole;
	double cents;
	double result = modf(d, &cents);
	result *= 100;
	int final_value = static_cast<int>(result);
	cout << "Returning " << final_value << " cents\n";
	return final_value;
}