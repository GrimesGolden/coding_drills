// Chrono.cpp
#include "Chrono.h"
#include <cmath>

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

			if (days_in_month(m, y) < d)
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

	int Date::days_in_month(Month m, int y) const
	{
		// Return the # of days in the current month. 
		// assume that y is valid

		int days_in_month = 31; // Most months have 31 days. 

		switch (m) {
		case Month::feb:  // the length of feb varies
			days_in_month = (leapyear(y)) ? 29 : 28;
			break;
		case Month::apr: case Month::jun: case Month::sep: case Month::nov:
			days_in_month = 30; // The rest have 30 days
			break;
		}

		return days_in_month;
	}


	void Date::add_month(int n)
	{
		// if the days in the next month we are switching to, are less than the days in the current month.
		// then offset it. Otherwise its fine just transition to next month. 

		while (n > 0)
		{
			Month next_month = nextMonth(m);
			int next_days = (next_month, y);


			if (next_days < d)
			{
				// if the days in the next month we are switching to, are less than the days in the current month.
			// then offset it.
				int offset = days_in_month(m, y) - d;
				d -= offset;
			}
			else if (m == Month::dec)
				// If it's december then it's a new year. 
			{
				++y;
			}

			m = next_month;
			--n; 
		}
	}

	void Date::add_year(int n)
	{
		if (m == Month::feb && d == 29 && !leapyear(y + n)) { // beware of leap years!
			m == Month::mar;
			d = 1;
		}

		y += n;
	}

	int Date::days_since() const
	{
		Date original{ 1970,Month::jan, 1 };
		Date copy = { y, m, d };
		int total_days = 0;

		if (y < 1970)
		{
			return 0;
		}

		while (original != copy && is_date(copy.year(), copy.month(), copy.day()) )
		{
			original.add_day(1);
			++total_days;
		}
		return total_days; 
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

	ostream& operator<<(ostream& os, const Day& d)
	{
		string day;

		switch (static_cast<int>(d))
		{
		case 0:
			day = "Sunday";
			break;
		case 1:
			day = "Monday";
			break;
		case 2:
			day = "Tuesday";
			break;
		case 3:
			day = "Wednesday";
			break;
		case 4:
			day = "Thursday";
			break;
		case 5:
			day = "Friday";
			break;
		case 6:
			day = "Saturday";
			break;
		default:
			day = "Error day.";
			break;
		}

		return os << day;
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
		int y = d.year();
		int m = static_cast<int>(d.month());
		int day = d.day();

		if (m == 1 || m == 2)
		{
			m += 12;
			y -= 1; 
		}

		int h = 0;
		int first = floor((13 * (m + 1)) / 5); 

		h = day + first + y + floor((y / 4)) - floor(y / 100) + floor(y / 400);
		h %= 7; 

		Day current_day; 

		switch (h)
		{
		case 0:
			current_day = Day::saturday;
			break;
		case 1:
			current_day = Day::sunday;
			break;
		case 2:
			current_day = Day::monday;
			break;
		case 3:
			current_day = Day::tuesday;
			break;
		case 4:
			current_day = Day::wednesday;
			break;
		case 5:
			current_day = Day::thursday;
			break;
		case 6:
			current_day = Day::friday;
			break;
		default:
			break;
		}

		return current_day; 
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