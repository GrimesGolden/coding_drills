// error_drills.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "std_lib_facilities.h"

int area(int length, int width);
int framed_area(int x, int y);

void clear_cin() 
{
    // Clears the input buffer.
    // No pre-condition or post condition.
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
double ctok(double c)
{
    // Converts celsius to kelvin.
    // Pre-condition: c must be a double greater than absolute zero (-237.15C)
    // Post-condition: A double greater than zero. 
    constexpr double abs_zero = -273.15;
    constexpr double conv_factor = 273.15;

        if (c < abs_zero)
            // Pre-condition error check.
        {
            error("Celsius temperature must be greater than absolute zero.");
        }

    double k = c + conv_factor;
    return k;
}

double ktoc(double k)
{
    // Converts celsius to kelvin.
    // Pre-condition: k must be a double greater than absolute zero (0)
    // Post-condition: A double greater than -273.15. 
    constexpr double abs_zero = 0;
    constexpr double conv_factor = 273.15;

    if (k < abs_zero)
        // Pre-condition error check.
    {
        error("Kelvin temperature must be greater than absolute zero.");
    }

    double c = k - conv_factor;
    return c;
}

double ctof(double c)
{
    // Converts celsius to fahrenheit.
    // Pre condition: a double greater than absolute zero celsius.
    // Post condition: A double greater than -459.67 (abs zero fahrenheit)
    constexpr double abs_zero = -273.15;
    constexpr double conv_factor = (9.0 / 5);
    constexpr int add_factor = 32;

    if (c < abs_zero)
    {
        error("Celsius temperature must be greater than absolute zero.");
    }

    double f = (conv_factor * c) + add_factor;
    return f;
}

double ftoc(double f)
{
    // Converts celsius to fahrenheit.
    // Pre condition: a double greater than absolute zero fahrenheit
    // Post condition: A double greater than -273.15 (abs zero celsius)
    constexpr double abs_zero = -459.67;
    constexpr double conv_factor = (5.0 / 9);
    constexpr int sub_factor = 32;

    if (f < abs_zero)
    {
        error("Fahrenheit temperature must be greater than absolute zero.");
    }

    double c = (f - sub_factor) * conv_factor;
    return c;

}

double prompt_temp() 
{
    // Prompt the user for a temperature.
    // No pre condition.
    // Post condition, must return a valid temperature type.
    double temp = 0;
    bool valid = false;

    while (!valid) 
    {   
        cout << "Enter a temperature: ";

        if (cin >> temp) 
        {
            cout << "\nTemperature accepted.\n";
            valid = true;
            clear_cin();
        }
        else 
        {
            cout << "\nInvalid temperature, try again.\n";
            clear_cin();
        }
    }

    return temp; 

}

bool valid_unit(char unit)
// Verify the given character is a valid unit.
// Pre-condition, a char.
// Post-condition, a bool. 
{
    vector<char> units = { 'k', 'c', 'f' };
    bool valid = false;

    for (char u : units)
    {
        if (unit == u)
        {
            valid = true;
            break;
        }
    }

    return valid;

}

char prompt_unit()
{
    // Prompt the user for a unit type.
    // No pre condition.
    // Post condition, must return a valid unit type.
    char unit = ' ';
    bool valid = false;

    vector<char> units = { 'k', 'c', 'f' };

    while (!valid)
    {
        cout << "Enter a unit (k, c, f): Representing Kelvin, Celsius or Fahrenheit\n";

        if (cin >> unit && valid_unit(unit))
        {
            cout << "\nUnit accepted.\n";
            valid = true;
            clear_cin();
        }
        else
        {
            cout << "\nInvalid unit type, try again.\n";
            clear_cin();
        }
    }

    return unit;

}

void convert_temp(double temp, char unit)
{
    // Given a valid temperature, and a valid unit.
    // Perform and display the appropriate conversion.

    switch (unit)
    {
    case 'k':
        cout << temp << " kelvin converted to celsius is :" << ktoc(temp) << "c\n";
        break;
    case 'c':
        cout << temp << " celsius converted to kelvin is :" << ctok(temp) << "k\n";
        cout << temp << " celsius converted to fahrenheit is :" << ctof(temp) << "f\n";
        break;
    case 'f':
        cout << temp << " fahrenheit converted to celsius is :" << ftoc(temp) << "c\n";
        break;
    default:
        error("Invalid unit was entered into a conversion.\n");
        break;
    }
}

int main()
{   
    try {
        //Determine the temperature. 
        // Determine the unit.
        // Print the conversion accordingly.
        int i = 0;
        while (i < 5) 
        {
            double temp = prompt_temp();
            char unit = prompt_unit();
            convert_temp(temp, unit);
            ++i;
        }
        keep_window_open();
        return 0;
    }
    catch (exception& e) {
        cerr << "error: " << e.what() << '\n';
        keep_window_open();
        return 1;
    }
    catch (...) {
        cerr << "Oops: unknown exception!\n";
        keep_window_open();
        return 2;
    }
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
