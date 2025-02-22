// Chrono.cpp
#include "Chrono.h"

namespace Chrono {
	// member function definitions

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
		d += n; // Should wrap around. 

		// I.E if the day gets past 31. We should increment the month, and turn the day to the first.
		// Unless it's a leap year or one of the other months. Damn it's complicated. 
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
		return true; // placeholder for now, just returns true. 
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

} // Chrono