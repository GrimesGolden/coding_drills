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
    }
}

int one(string& digits, int& number, int& max_size)
{
    //Purpose: converts the given strings tenth digit into an integer and text display
    // Pre Condition: A string of digits, and the number to continue converting, as well as max_size, all passed by reference 
    // Post Condition: Returns the final number, as the last in the chain of calling functions. 
    // Calling function: Ten
    int digit = 0;


    if (valid_string(digits) && digits.size() == max_size)
    {
        digit = char_to_int(digits[0]);
        cout << digit << " ones.\n"; // print message
        digit *= max_size;
        number += digit;
    }

    pop_front(digits);

    return number;

}

int ten(string& digits, int& number, int& max_size)
{
    //Purpose: converts the given strings tenth digit into an integer and text display. Also calls ones function.
    // Pre Condition: A string of digits, and the number to continue converting, and max_size, passed by reference 
    // Post Condition: int
    // Calling function: Hundred
    int digit = 0;
    constexpr int tenth = 10;

    if (valid_string(digits) && digits.size() == max_size)
    {
        digit = char_to_int(digits[0]);
        cout << digit << " tens and "; // print message
        digit *= tenth;
        number += digit;
        --max_size;

        pop_front(digits);
        one(digits, number, max_size);
    }

    pop_front(digits);
    return one(digits, number, max_size);

}

int hundred(string& digits, int& number, int& max_size)
{
    //Purpose: converts the given strings hundredth digit into an integer and text display. Also calls tens function.
    // Pre Condition: A string of digits, and the number to continue converting, and max_size passed by reference 
    // Post Condition: int
    // Calling function: Thousand
    int digit = 0;
    constexpr int h = 100;

    if (valid_string(digits) && digits.size() == max_size)
    {
        digit = char_to_int(digits[0]);
        cout << digit << " hundredths and "; // print message
        digit *= h;
        number += digit;
        --max_size;

        pop_front(digits);
        return ten(digits, number, max_size);
    }
}

int thousand(string& digits)
{   
    // Converts the given strings first digit into thousandths, and then accurately calls upon the hundreds function to finish the task of conversion. 
    // Pre Condition: A string of digits with size == 4, passed by reference for modification.
    // Post Condition: int

    int number = 0;
    constexpr int t = 1000;
    int max_size = 4;

    if (valid_string(digits) && digits.size() == max_size)
    {
        number = char_to_int(digits[0]);
        cout << " is " << number << " thousands and "; // print message
        number *= t;
        --max_size;

        pop_front(digits);
        return hundred(digits, number, max_size);
    }
}

void convert_string(string& digits)
{   
    // Purpose: Converts the given string into a valid integer, while calling out the individual unit values.
    // Pre Condition: Any string passed by ref. (Only valid strings will pass)
    // Post Condition: None, simply converts and prints. But could be modifed to return an int if needed. 
    int size = digits.size();
    int naught = 0;
    // Without thousands calling the other functions, simply pass a zero and the size of the input for accurate results. 

    if (valid_string(digits))
    {
        switch (size)
        {
        case 4:
            cout << "Value is: " << thousand(digits);
            break;
        case 3:
            cout << "Value is: " << hundred(digits, naught, size);
            break;
        case 2:
            cout << "Value is : " << ten(digits, naught, size);
            break;
        case 1:
            cout << "Value is : " << one(digits, naught, size);
            break;
        default:
            cout << "Error, fell through switch statement.\n";
            break;
        }
    }
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
            convert_string(input);
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
