// bulls_and_cows.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "std_lib_facilities.h"

// Still left to do. When you have the "guess" vector, clear it out before getting the new guess.

void welcome()
{
    // Simply greet the user, and display the rules of bulls and cows.
    // Enter h at any time to see this again.
    cout << "Welcome to the bulls and cows game.\n";
    cout << "Guess a secret code made up of 4 unique digits. After each guess, you'll receive clues:\n";
    cout << "Bull: A digit is correct and in the correct position.\n";
    cout << "Cow: A digit is correct but in the wrong position\n";
    cout << "Guess all four to win! Good luck.\n";
    cout << "Enter h or 'help' during gameplay to see this message again.\n";
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
        cout << n;
    }

    cout << "\n";
}

bool is_digit(int digit)
{
    // Self explan
    if (digit < 0 || digit > 9)
    {
        return false;
    }
}

bool is_unique(int digit, vector<int> number)
{
    // verify the given digit is unique in the vector
    for (int n : number)
    {
        if (n == digit)
        {
            return false;
        }
    }
    return true;
}

int get_digit()
{   
    // Continuously repeats randint(10)
    // Until a valid digit is obtained.
    int digit = randint(10);
    while (!is_digit(digit))
    {
        digit = randint(10);
    }
    return digit;

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
    int first = get_digit();
    number.push_back(first);

    // Loop through the remaining 3 digits.
    // Each time creating a new random digit.
    for (int i = 1; i < max_size; ++i)
    {
        int new_digit = get_digit();

        while (!is_unique(new_digit, number))
            // If this digit is not unique (matches a previous digit).
            // Calculate a new random digit and try again.
            // It seems statistically rare this would occur, but its an important failsafe. 
        {   
            cout << "Calculating new seed digit.\n";
            new_digit = get_digit();
        }
        number.push_back(new_digit);
    }

    cout << "Number loaded succesfully: ";
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

int char_to_int(char c)
{   
    // Uses the fact that '0' in ASCII is '48';
    // Converts to a correct digit.
    // Pre condition: Any valid char.
    // Post condition an integer value.
    return (int{ c } - '0');
}

bool try_digit(int& digit)
{
    // Obtain a valid guess digit.
    // PreCondition: an int of any form.
    // Post condition: true or false. True if user entered quit or false to continue.
    bool quit = false;
    char guess = ' ';

    clear_cin();

    while (!quit)
    {
        // if its a digit 0-9 its valid.
       // if its q or quit its quit.
       // if its h display help.
        cout << "Enter digit to guess\n";
        cin >> guess;

        if (guess == 'q')
        {
            quit = true;
            return true;
        }
        else if (guess == 'h')
        {
            welcome();
            clear_cin();
        }
        else if (char_to_int(guess) < 0 || char_to_int(guess) > 9)
        {
            cout << "Invalid entry: " << char_to_int(guess) << "\nDigits must range from (0-9):\n";
            clear_cin();
        }
        else
        {
            cout << "Success.\n";
            digit = char_to_int(guess);
            return false;
        }
    }

}
bool get_guess(vector<int>& guess)
{
    // Loop through continously, prompting for a guess and calculating accordingly.
    // Pre-Condition: A valid vector of ints, passed by reference. 
    // Post-condition: A bool determing whether we should quit main loop. True to quit.
    bool quit = false;

    for (int i = 0; i < 4; ++i)
    {   
        // Try to get a digit from the user.
        int digit = 0;
        quit = try_digit(digit);
     
        if (quit)
        // If they want to quit, simply return at this point.
        {   
            cout << "Exiting Game!";
            return true;
        }

        // Push back the valid digit into the guess.
        guess.push_back(digit);
        cout << "Loading " << digit << "\n";
    }
    return false;

}

bool play_again()
{   
    // Return a char prompted from the user.
    // Post Cond: A bool which determines if the user wants to play again. (true for yes)
    char input = ' ';
    bool play = true;

    clear_cin();
    cout << "Press any key to play again, or q to quit. h for help.\n";
    cin >> input;
    clear_cin();

    if (input == 'q')
    {
        play = false;
    }

    return play;
}

vector<int> check_score(vector<int>& number, vector<int>& guess)
{
    // PreCondition, the two vectors of ints passed as reference, the current number, and the users full valid guess.
    int bulls = 0;
    int cows = 0;

    vector<int> score;

    for (int i = 0; i < number.size(); ++i)
    {
        if (number[i] == guess[i])
        {   
            // Check if the immediate corresponding element matches (a bull).
            ++bulls;
        }
        else
        {
            for (int j = 0; j < number.size(); ++j)
            {
                if (number[i] == guess[j])
                {
                    ++cows;
                }
            }
        }
    } // end for

    cout << "You guessed ";
    display_number(guess);
    cout << "\nThat's " << bulls << " bulls and " << cows << " cows!\n";
    score.push_back(bulls);
    score.push_back(cows);
    return score;
}

void loop_game(vector<int>& number, vector<int>& guess)
{   
    // Pre condition: The vector containing a valid number to guess.
    // Another vector containing the users now valid guess.
    // Use these in a loop to determine if the user a) wants to quit. 
    // b) Has won or c) Should continue making guesses. 
    bool quit = false;
    vector<int> score;

    while (!quit)
    {   
        // Get the guess, and also determine if we should quit.
        quit = get_guess(guess);

        if (quit) 
        {   
            // If the user chose to quit, there is no need to check the score.
            break; 
        }

        score = check_score(number, guess);

        if (score[0] == 4)
        {   
            if (!play_again())
            {
                quit = true;
                break;
            }
            else
            {
                cout << "You Won!\n";
            }
        }

        guess.clear(); // try to clear the vector here
    }
}

void start_game()
{
    // Variable definitions.
    int n = 0;
    vector<int> number;
    vector<int> guess;

    // Load the number which the user must guess.
    load_game(n, number);
    // Get the users guess;
    loop_game(number, guess);
}



int main()
// Implement the bulls and cows game. 
{
    try
    {
        // Variable definitions.
        int n = 0;
        vector<int> number;
        vector<int> guess;

        // Load the number which the user must guess.
        load_game(n, number);
        // Get the users guess;
        loop_game(number, guess);
    }
    catch (exception e)
    {
        cerr << e.what();
        return 1;
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
