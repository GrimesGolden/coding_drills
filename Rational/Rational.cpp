#include "Rational.h"
#include "std_lib_facilities.h"
#include <random>

Rational::Rational() : n{ 1 }, d{ 1 }
{
	// Default constructor.
}

Rational::Rational(int num, int den) : n{ num }, d{ den }
{
	valid();
}

Rational::~Rational()
{
	// deconstructor. 
}

void Rational::valid() const
{
	// Denominator cannot equal zero. 
	if (d == 0)
	{
		error("Undefined operation");
	}
}

// Helpers

void Rational::simplify()
{
    int factor = gcd(n, d);

    n /= factor;
    d /= factor; 
}

double r_to_d(Rational r)
{
    double result = (static_cast<double>(r.numerator())) / (r.denominator());
    return result;
}

// Operator overloads
ostream& operator<<(ostream& os, const Rational& r)
{   
    if (r.denominator() == 1)
    {
        os << r.numerator(); 
    } 
    else if (r.denominator() == -1)
    {
        os << r.numerator() * -1;
    }
    else
    {
        os << r.numerator() << "/" << r.denominator();
        
    }

    return os;
}

Rational operator+(Rational l, Rational r)
{
    int a = l.numerator();
    int b = l.denominator();
    int c = r.numerator();
    int d = r.denominator();

    int num = (a * d) + (c * b);
    int den = b * d;

    Rational result{ num, den };
    result.simplify();
    return result; 
}

Rational operator-(Rational l, Rational r)
{
    int a = l.numerator();
    int b = l.denominator();
    int c = r.numerator();
    int d = r.denominator();

    int num = (a * d) - (c * b);
    int den = b * d;

    Rational result{ num, den };
    result.simplify();
    return result;
}

Rational operator*(Rational l, Rational r)
{
    int a = l.numerator();
    int b = l.denominator();
    int c = r.numerator();
    int d = r.denominator();

    int num = a*c;
    int den = b*d;

    Rational result{ num, den };
    result.simplify();
    return result;
}

Rational operator/(Rational l, Rational r)
{
    int a = l.numerator();
    int b = l.denominator();
    int c = r.numerator();
    int d = r.denominator();

    int num = a * d;
    int den = b * c;

    if (den == 0)
    {
        cout << "Divide by zero error";
        den = 1; 
    }

    Rational result{ num, den };
    result.simplify();
    return result;
}

bool operator==(Rational l, Rational r)
{
    l.simplify();
    r.simplify(); 

    if (l.numerator() == r.numerator() && l.denominator() == r.denominator())
    {
        return true;
    }
    else
    {
        return false; 
    }
}

bool operator!=(Rational l, Rational r)
{
    return !(l == r);
}

int gcd(int a, int b)
{
    // Ensure inputs are non-negative
    a = abs(a);
    b = abs(b);

    // Handle edge cases
    if (a == 0) return b;
    if (b == 0) return a;

    // Euclidean algorithm
    while (b != 0)
    {
        int r = a % b; // Compute remainder
        a = b;         // Update a
        b = r;         // Update b
    }

    return a; // GCD is stored in variable a
}

void print_tests()
{   
    vector<Rational> rational_numbers;
    vector<Rational> test_case; 

    // Create a random number generator
    std::random_device rd;  // Seed for random number generator
    std::mt19937 gen(rd()); // Mersenne Twister random number generator

    // Define the range [-100, 100]
    std::uniform_int_distribution<int> dist(-10, 10);

    // Generate a random number in the range
    for (int i = 0; i < 25; ++i)
    {
        int n = dist(gen);
        int d = dist(gen);

        if (d == 0)
        {
            d = 1;
        }

        rational_numbers.push_back(Rational{ n, d });

        n = dist(gen);
        d = dist(gen); 

        if (d == 0)
        {
            d = 1;
        }

        test_case.push_back(Rational{ n, d });
    }

    for (int i = 0; i < rational_numbers.size(); ++i)
    {
        cout << "Test case " << i + 1 << " :\n";
        cout << rational_numbers[i] << "\n";
        cout << rational_numbers[i] << " + " << test_case[i] << " = " << rational_numbers[i] + test_case[i] << "\n";
        cout << rational_numbers[i] << " - " << test_case[i] << " = " << rational_numbers[i] - test_case[i] << "\n";
        cout << rational_numbers[i] << " * " << test_case[i] << " = " << rational_numbers[i] * test_case[i] << "\n";
        cout << rational_numbers[i] << " / " << test_case[i] << " = " << rational_numbers[i] / test_case[i] << "\n";

        rational_numbers[i].simplify();
        cout << "Simplifies to " << rational_numbers[i] << "\n";
        cout << "Converted to a double this is " << r_to_d(rational_numbers[i]) << "\n******************************************\n";
    }
}