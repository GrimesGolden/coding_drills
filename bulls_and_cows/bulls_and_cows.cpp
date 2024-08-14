// bulls_and_cows.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "std_lib_facilities.h"

// Bulls and Cow drill implementation for Bjarne Stroustrup PPP. Chapter 4 exercises.

void welcome()
{
    // Simply greets the user, and display the rules of bulls and cows.
    // Performs double duty as both welcome message and help prompt. 
    cout << "Welcome to the bulls and cows game.\n\n";
    cout << "Guess a secret code made up of 4 unique digits. After each guess, you'll receive clues:\n";
    cout << "Bull: A digit is correct and in the correct position.\n";
    cout << "Cow: A digit is correct but in the wrong position\n";
    cout << "Guess all four to win! Good luck.\n";
    cout << "Enter h or 'help' during gameplay to see this message again.\n";
    cout << "\n\n\n\n";
}

void clear_console()
{
    // Simulates clearing the console.
    for (int i = 0; i < 100; ++i) {
        std::cout << std::endl;
    }
}

void clear_cin()
{
    // Clears the cin buffer, useful in preparation for new input.
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool validate_seed(int& seed)
{
    // Given a potential seed, verifies if that integer is valid.
    // Pre-Condition: An integer representing the potential seed.
    // Post-Condition: a bool: Specifying if the seed is valid (t). 
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
    // Prompt the user to enter a valid seed. Obtains that seed
    // Pre-condition: none.
    // Post-condition: a valid integer (n) to be implemented as a seed.

    cout << "\n\nPlease enter any whole number, this will simply load the game with a given seed.\n";
    int seed = 0;
    bool valid = false; 

    while (!valid)
        // The purpose of this loop is to force the user into a continual prompt for valid seed data.
        // Until valid => Prompt again.
    {
        valid = validate_seed(seed);
    }

    cout << "Seed obtained " << seed << "\n";
    return seed;
}

void display_number(vector<int>& number)
{
    // Given a pre condition of : valid integer array (passed by reference to save memory).
    // Simply displays the given number using a range for loop (void post condit).

    // Useful for quickly printing the vector digits in number form. 

    for (int n : number)
    {
        cout << n;
    }

    cout << "\n";
}

bool is_digit(int num)
{
    // Self explanatory.
    // Pre condition: A potential digit integer.
    // Post condition: A bool. True = is_digit
    if (num < 0 || num > 9)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool is_unique(int& digit, vector<int>& number)
{
    // verify the given int (digit) is unique in the given vector (number).
    // pre condition: A digit integer, and a number
    // post condition: A bool (t == unique)


    for (int n : number)
    {
        if (n == digit)
            // If any number in the given vector matches the digit, its not unique.
        {
            return false;
        }
    }
    return true;
}

bool valid_digit(int& digit, vector<int>& number)
{   

    // Performs two seperate tasks. verifying if the given number is both digit and unique.
    // Only then can we call an input valid.
 
    // pre condition: A digit integer, and a number
    // post condition: A bool

    // A rather redundant safety check, one could say.

    if (!is_digit(digit))
    {
        return false;
    }
    else if (!is_unique(digit, number))
    {
        return false;
    }
    else 
    {
        return true;
    }
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

        while (!valid_digit(new_digit, number))
            // If this digit is not valid (matches a previous digit for example).
            // Calculate a new random digit and try again.
        {   
            cout << "Fluctuation in quantum field: Calculating new seed digit.\n";
            new_digit = get_digit();
        }
        number.push_back(new_digit);
    }

    cout << "Number generated succesfully\n";
    // DEBUG 
    //display_number(number); //uncomment to help with bug detection, or game modification.
    return number;
}

void load_game(vector<int>& number)
{
    // Obtain a seed using return_seed()
    // Use this to load the number to be guessed into the vector. 
    // In essence preparing the game for a new round of play. 

    // PreConditions: a vector<int> of any valid form, contents irrelevant.
    // No post conditions due to pass by ref.
    int seed = return_seed();
    number.clear();
    number = load_number(seed);
    cout << "Game loaded succesfully.\n";
    cout << "\n\n\n\n";
}

int char_to_int(char c)
{   
    // Uses the fact that '0' in ASCII is '48';
    // Converts to a correct digit.
    // Pre condition: Any valid char.
    // Post condition an integer value.
    return (int{ c } - '0');
}

bool validate_guess(int& digit)
{   
    //pre-condition: An integer digit. 
    // post-condition: A bool representing a valid guess (t). Return false for quit request.
    // Obtain a valid guess from the user.

    char guess = ' ';

    clear_cin();
  
    while (true)
    {
        // any digit 0-9 is valid.
       // q or quit == quit.
       // h == display help.
        // All other characters prompt invalid entry. 

        cout << "Enter digit to guess\n";
        cin >> guess;

        if (guess == 'q')
            // Quit game
        {   
            return false;
        }
        else if (guess == 'h')
            // Print help menu
        {
            welcome();
            clear_cin();
            continue;
        }
        else if (!is_digit(char_to_int(guess))) // This rather messy statement simply confirms or rejects that the users guess is a digit. 
            // Invalid input
        {   
            cout << "\n\n\n\n";
            cout << "Invalid entry.\nDigits must range from (0-9):\n";
            clear_cin();
            continue;
        }
        else
            // Valid input. Process guess
        {
            cout << "Success.\n\n\n";
            digit = char_to_int(guess);
            return true;
        }
    }
}


bool get_guess(vector<int>& guess)
{
    // Loop through continously, prompting for a guess and calculating accordingly.
    // Pre-Condition: A valid vector of ints, passed by reference(The users potential guess). And a digit
    // Post-condition: A bool determing whether we should quit to main loop. true to quit.
    //bool  = false;

    // Performs the critical step of obtaining a full and valid guess from the user. Ending a round of gameplay.
    bool loop = true;

    for (int i = 0; i < 4; ++i)
    {
        // Obtain a valid digit from the user.
        int digit = 0;
        // Exit will be true if the user requested to quit.

        if (!validate_guess(digit))
        {
            return true;
        }
        else
        {
            // Push back the valid digit into the guess.
            guess.push_back(digit);
            cout << "Loading " << digit << "\n";
        }
    }
    return false; 
}

bool play_again(vector<int>& number)
{   
    // Pre:condition: The number itself passed by ref (important so we can load a new number)
    // Post Cond: A bool which determines if the user wants to play again. (true for yes)
    char input = ' ';

    clear_cin();
    cout << "\nPress any key to play again, or q to quit.\n";
    cin >> input;
    clear_cin();

    if (input == 'q')
    {
        return true;
        cout << "Exiting game!\n";
    }
    else 
    {   
        // In this junction, the game loop continues, but a new number must be created from which to guess.
        load_game(number);
        return false;
    }
}

bool get_score(vector<int>& number, vector<int>& guess)
{
    // Return true if the user won, and false if they did not guess correctly.
    // pre condition: The number to be guessed, and the guess itself. Both valid and passed by ref.
    // Post condition: A bool (t == win) (f == incorrect guess)
    int bulls = 0;
    int cows = 0;
    int tries = 0;
    int wins = 0;

    vector<int> score;

    // Determine bulls and cows.
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

    // Display info.
    clear_console();
    cout << "You guessed ";
    display_number(guess);
    guess.clear(); // Reset the users guess, to prevent guesses stacking in vector.
    // Determine win condition. 
    if (bulls == 4)
    {
        return true;
    }
    else
    {   
        cout << "\nThat's " << bulls << " bulls and " << cows << " cows!\n";
        return false; 
    }
}



void start_game()
{   
    // No Pre or post condition. This loop is entirely self contained.
    // Useful for later additions, or use in other programs. 

    // Create variables. 
    bool quit = false;
    bool win = false;

    vector<int> number;
    vector<int> guess;
    int tries = 0;
    int bulls = 0;
    int win_count = 0;

    // Setup first round.
    welcome();
    load_game(number);


    // Begin main loop
    while (!quit)
    {   
        quit = get_guess(guess);

        if (quit)
        {
            continue;
        }

        win = get_score(number, guess);
        ++tries;

        if (win)
        {   
            ++win_count;
            cout << "And you won!\n You guessed the number ";
            display_number(number);
            cout << "\nYou won in " << tries << " guesses.\n";
            cout << win_count << " wins so far this game.\n";
            quit = play_again(number);
            tries = 0; 
        }
        else
        {
            cout << "Try again...\n";
        }
    }// end while
    cout << "Exiting.";
}



int main()
// Implement the bulls and cows game. 
// We give thanks to the overlord Bjarne Stroustrup.
{
    try
    {
        start_game();
        return 0;
    }
    catch (exception e)
    {
        cerr << e.what();
        return 1;
    }
}