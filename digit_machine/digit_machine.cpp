// digit_machine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "std_lib_facilities.h"

int char_to_int(char c)
{
    // Purpose: convert a character to an integer.
    // Pre Cond: A valid char (a copy is fine its so small).
    // Post Cond: A valid int which properly reflects the char value.

    char naught = '0';
    char post_val = c - naught;
    return post_val;
}

bool is_digit(char c)
{   
    // Purpose: Determine if the given character (copy) is representitive of a digit.
    // Pre Condition: A char passed by copy.
    // Post Condition: A bool which correctly return T if char represents a digit. 
    vector<char> digits = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
    bool valid_digit = false;

    for (char digit : digits)
    {
        if (c == digit)
        {
            valid_digit = true;
        }
    }

    return valid_digit;
}

bool all_digits(string& digits)
{   
    // Purpose: Determine the given string consists of all digits.
    // Pre Cond: Any string passed by reference for memory.
    // Post Cond: A bool accurately designating T for all digits. 
    bool valid = true;
    for (char digit : digits)
    {
        if (!is_digit(digit))
        {
            valid = false;
            return valid;
        }
    }
    return valid; 
}

bool valid_string(string& digits)
{
    //Purpose: verifies that the given string is valid for use in the program. 
    // Pre Condition: Any string, passed by reference to save memory.
    // Post Condition: A bool (T) accurately designates a valid string.

    bool valid = false;

    if (digits.size() <= 0 || digits.size() > 4)
    {   
        // This program only handles from 1-4 digits.
        return valid;
    }
    else
    {   
        // If the size is accurate, then determine every character is a valid digit.
        valid = all_digits(digits);
    }
    return valid;
}

void pop_front(string& digits)
{   
    // Simply pops the front element of the string passed by reference.
    // Pre Condition: Assumes string is > 0.
    // No return value. 
    if (!digits.empty())
    {
        digits.erase(digits.begin());
        cout << "Popped from digits now contains: " << digits << "\n";
    }
}

void thousand(string& digits)
{   
    // Converts the given strings first digit into thousandths, and then accurately calls upon the hundreds function to finish the task of conversion. 
    // Pre Condition: A string of digits with size == 4, passed by reference for modification.
    // Post Condition: NONE

    int number = 0;
    constexpr int t = 1000;

    if (valid_string(digits))
    {
        number = char_to_int(digits[0]);
        cout << " is " << number << " thousands and "; // print message
        number *= t;
    }

    pop_front(digits);
}

int main()
{   
    while (true)
    {
        cout << "Enter a string: ";
        string input;
        cin >> input;
        cout << "\n " << input;

        if (valid_string(input))
        {
            cout << " is VALID.\n";
            if (input.length() == 4)
            {
                thousand(input);
            }
        }
        else
        {
            cout << "is INVALID. \n";
        }
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
