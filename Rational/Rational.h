#pragma once
#include "std_lib_facilities.h"
// Design and implement a rational number class, Rational.

// Addition, subtraction, , multiplication, division, equality, and output done. 

class Rational
{
public:
	Rational();
	Rational(int num, int den);
	~Rational();
	void valid() const; 
	int numerator() const { return n; }
	int denominator() const { return d; } 
	void simplify(); 

private:
	int n; // numerator
	int d; // denominator

};

// Helper. 
int gcd(int a, int b);
double r_to_d(Rational r);

// Operator overloads
ostream& operator<<(ostream& os, const Rational& r); 

// Change to pass by value not reference. 
Rational operator+(Rational l, Rational r);
Rational operator-(Rational l, Rational r);
Rational operator*(Rational l, Rational r);
Rational operator/(Rational l, Rational r);
bool operator==(Rational l, Rational r);
bool operator!=(Rational l, Rational r);

void print_tests();