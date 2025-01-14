// Chrono.cpp
#include "Chrono.h"

namespace Chrono {
	// member function definitions

	Month nextMonth(Month current) 
{
		// Convert to underlying integer, increment, and cast back to Month
		int next = static_cast<int>(current) + 1;

		// Wrap around if we reach beyond December (12)
		if (next > static_cast<int>(Month::dec)) {
			next = static_cast<int>(Month::jan); // Wrap back to January
		}

		return static_cast<Month>(next);
	}

	Date::Date(int yy, Month mm, int dd)
		: y{ yy }, m{ mm }, d{ dd }
	{
		if (!is_date(yy, mm, dd)) throw Invalid{};
	}

	const Date& default_date()
	{
		static Date dd {2001, Month::jan, 1}; // start of 21st century
		return dd;
	}

	Date::Date()
		:y{ default_date().year() },
		m{ default_date().month() },
		d{ default_date().day() }
	{
	}

	void Date::add_day(int n)
	{
		while (n > 0)
		{
			// Increment the days in the date
			// Decrement n
			++d;
			--n; 

			if (days_in_month(*this) < d)
			{
				// Transition to the next month if needed. 
				m = nextMonth(m);
				d = 1;
			}

			if (m == Month::jan && d == 1)
			{
				// Transition to the next year on January 1st. 
				++y;
			}
		}
	}

	void Date::add_month(int n)
	{
		// ...
	}

	void Date::add_year(int n)
	{
		if (m == Month::feb && d == 29 && !leapyear(y + n)) { // beware of leap years!
			m == Month::mar;
			d = 1;
		}

		y += n;
	}

	bool is_date(int y, Month m, int d)
	{
		// assume that y is valid

		if (d <= 0) return false;
		if (m < Month::jan || Month::dec < m) return false;

		int days_in_month = 31; // Most months have 31 days. 

		switch (m) {
		case Month::feb:  // the length of feb varies
			days_in_month = (leapyear(y)) ? 29 : 28;
			break;
		case Month::apr: case Month::jun: case Month::sep: case Month::nov:
			days_in_month = 30; // The rest have 30 days
			break;
		}

		if (days_in_month < d) return false;

		return true;
	}

	bool leapyear(int y)
	{
		// see exercise 10
		if (y % 4 != 0)
		{
			return false;
		}
		else if (y % 100 != 0)
		{
			return true;
		}
		else
		{
			return (y % 400 == 0);
		}
	}

	bool operator==(const Date& a, const Date& b)
	{
		return a.year() == b.year()
			&& a.month() == b.month()
			&& a.day() == b.day();
	}

	bool operator!=(const Date& a, const Date& b)
	{
		return !(a == b);
	}

	ostream& operator<<(ostream& os, const Date& d)
	{
		return os << '(' << d.year()
			<< ',' << int(d.month())
			<< ',' << d.day() << ')';
	}

	istream& operator>>(istream& is, Date& dd)
	{
		int y, m, d;
		char ch1, ch2, ch3, ch4;
		is >> ch1 >> y >> ch2 >> m >> ch3 >> d >> ch4;
		if (!is) return is;
		if (ch1 != '(' || ch2 != ',' || ch3 != ',' || ch4 != ')') { // oops: format error
			is.clear(ios_base::failbit); //  set the fail bit
			return is;
		}

		dd = Date(y, Month(m), d); // update dd

		return is;
	}

	// HELPER FUNCTIONS

	Day day_of_week(const Date& d)
	{
		return Day::saturday; // Placeholder
	}

	Date next_Sunday(const Date& d)
	{
		return Date(); // Placeholder just returns default day.
	}

	Date next_weekday(const Date& d)
	{
		return Date(); // Placeholder just returns default day. 
	}

	int days_in_month(const Date& d)
	{
		// assume that y is valid

		int days_in_month = 31; // Most months have 31 days. 

		switch (d.month()) {
		case Month::feb:  // the length of feb varies
			days_in_month = (leapyear(d.year())) ? 29 : 28;
			break;
		case Month::apr: case Month::jun: case Month::sep: case Month::nov:
			days_in_month = 30; // The rest have 30 days
			break;
		}

		return days_in_month;
	}
} // Chrono