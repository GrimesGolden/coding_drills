// bulls_and_cows.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "std_lib_facilities.h"

void welcome()
{
    // Simply greet the user, and display the rules of bulls and cows.
    // Enter h at any time to see this again.
    cout << "Welcome to the bulls and cows game.\n";
    cout << "Guess a secret code made up of 4 unique digits. After each guess, you'll receive clues:\n";
    cout << "Bull: A digit is correct and in the correct position.\n";
    cout << "Cow: A digit is correct but in the wrong position\n";
    cout << "Guess all four to win! Good luck.\n";
    cout << "Enter h or 'help' during gameplay to see this message again.";
}

void clear_cin()
{
    // Clear the cin buffer, in case of error.
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool validate_seed(int& seed)
{
    // Obtain a valid seed.
    // Pre condition: a double (0).
    // Post condition: must return a bool, representing if valid input was obtained.
    int input = 0;

    if (cin >> input)
    {
        cout << "Seed accepted.\n";
        seed = input;
        return true;
    }
    else
    {
        cout << "Invalid number. Try again.\n";
        clear_cin();
        return false;
    }
}

int return_seed()
{
    // Prompt the user to enter a valid seed.
    // Pre-condition: a valid number.
    // Post-condition: the same valid number.
    cout << "\n\nPlease enter any whole number, this will simply load the game with a given seed.\n";
    int n = 0;
    bool valid = false; 
    while (!valid)
    {
        valid = validate_seed(n);
    }
    cout << "Seed obtained " << n << "\n";
    return n;
}

void display_number(vector<int>& number)
{
    // Given a pre condition of valid integer array (passed by reference to save memory).
    // Simply displays the given number using a range for loop.
    for (int n : number)
    {
        cout << "*";
    }
    cout << "\n";
}

vector<int> load_number(int& seed)
{
    // Given a valid seed.
    // This function loads a vector with 4 individually unique integers in the range 0-9.
    // Pre Condition: A valid integer seed, obtained from return_seed().
    // Post Condition: A valid vector of size 4. Containg unique integer digits. (0-9 range).

    // Variables to store.
    vector<int> number;
    constexpr int max_size = 4;

    // Seed rand.
    seed_randint(seed);

    // Load the first int.
    number.push_back(randint(10));

    // Loop through the remaining 3 digits.
    // Each time creating a new random digit.
    for (int i = 1; i < max_size; ++i)
    {
        int new_digit = randint(10);

        while (new_digit == number[i - 1])
            // If this digit is not unique (matches a previous digit).
            // Calculate a new random digit and try again.
            // It seems statistically rare this would occur, but its an important failsafe. 
        {   
            cout << "Calculating new seed digit.\n";
            new_digit = randint(10);
        }

        number.push_back(new_digit);
    }

    cout << "Number obtained succesfully: ";
    display_number(number);
    return number;
}

void load_game(int& seed, vector<int>& number)
{
    // Given the core variables of the game.
    // (That is the users seed and the vector)
    // Load them with the proper data and continue.

    // PreConditions: An integer of any form, and a vector<int> of any valid form.
    // No post conditions due to pass by ref.
    welcome();
    seed = return_seed();
    number = load_number(seed);
    cout << "Game loaded succesfully.\n";
}




int main()
// Implement the bulls and cows game. 
{   
    // Variable definitions.
    int n = 0;
    vector<int> number;
    
    // Load the number which the user must guess.
    load_game(n, number);
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
