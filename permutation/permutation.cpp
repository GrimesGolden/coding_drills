// permutation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "std_lib_facilities.h";

void clear_buffer()
{
    // Clears and ignores buffer.
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int get_int()
{
    // Receive a valid int from the user then return it.
    int number = 0;
    bool valid = false;
    cout << "Input an int >>";

    while (!valid)
    {
        if (cin >> number)
        {
            cout << "Good job input accepted: " << number << "\n";
            clear_buffer();
            valid = true;
        }
        else
        {
            cout << "Error invalid input, try again.\n";
            clear_buffer();
        }
    }

    return number;
}

int factorial(int input)
{
    // Working factorial function.
    // Pre Condition: Must take an integer between 0 and 16.
    // Post Condition: An integer value. 
    if (input == 0 || input == 1)
    {
        return 1;
    }
    else if (input < 0)
    {
        error("negative factorial detected.");
    }
    else if (input >= 17)
    {
        error("factorial is too large (max is 16!)");
    }
    else
    {
        int result = input;
        while (input > 1)
        {
            result *= (input - 1);
            --input;
        }
        return result;
    }
}

int main()
{   
    try
    {
        while (true)
        {
            int number = get_int();

            cout << number << " factorial == " << factorial(number) << "\n\n";
        }
    }
    catch (exception e)
    {
        cerr << "Error caught >> destroying hardrive: " << e.what() << "\n";
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
