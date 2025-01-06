#include "Chrono.h"
using Chrono::Date;
using Chrono::Month; 

int main() {
	// Define a Date called today initialized to June 25, 1978
	// Then define a Date called tomorrow and give it a value by copying today into it and increasing its day by one using add_day()
	// Finally output today and tomorrow using a << defined as in 9.8
	
	Date today{ 1978, Month::jun, 25 }; 

	Date tomorrow = today;

	tomorrow.add_day(16);

	cout << today; 

	cout << tomorrow; 
}