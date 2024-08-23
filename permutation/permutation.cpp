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
    cout << "Enter your input >>";

    while (!valid)
    {
        if (cin >> number && number <= 16 && number >= 1)
        {
            cout << "Input accepted: " << number << "\n";
            clear_buffer();
            valid = true;
        }
        else
        {
            cout << "Error invalid input, try again.\n >>";
            clear_buffer();
        }
    }

    return number;
}

void welcome() {
    cout << "**************************************************\n"
        "* Welcome to the Permutation and Combo Calculator *\n"
        "*                                                *\n"
        "* Please choose an option:                     *\n"
        "*                                                *\n"
        "* 1. Calculate a Permutation                    *\n"
        "* 2. Calculate a Combination                    *\n"
        "*                                                *\n"
        "**************************************************\n";
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

void get_values(int& a, int& b)
{
    cout << "Enter number of items in main set (for example possible numbers in a combo lock)\n";
    a = get_int();

    cout << "Next enter number of items in sub set (for example the amount of digits in the combo locks combo)\n";
    b = get_int();
}

void permutation()
{   
    int a = 0;
    int b = 0;

    get_values(a, b);

    cout << "Performing permutation with a == " << a << " and b == " << b << "\n";

}

void combo()
{
    int a = 0;
    int b = 0;

    get_values(a, b);

    cout << "Performing combination with a == " << a << " and b == " << b << "\n";

}

void control_path(int input)
{
    // Output a message regarding correct user selection.
    switch (input)
    {
    case 1:
        cout << "Permutation selected.\n";
        permutation();
        break;
    case 2:
        cout << "Combination selected.\n";
        combo();
        break;
    default:
        cout << "Error, incorrect selection.\n";
        break;
    }
}

void select_option()
{
    // Finalize correct user selection.
    int input = get_int();
    control_path(input);

    while (input != 1 && input != 2)
    {
        int input = get_int();
        control_path(input);
    }
}

int main()
{   
    try
    {   
        welcome();

        while (true)
        {
            select_option();
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
