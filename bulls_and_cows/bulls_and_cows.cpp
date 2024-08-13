// bulls_and_cows.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "std_lib_facilities.h"

// Bulls and Cow drill implementation for Bjarne Stroustrup PPP. Chapter 4 exercises.

void welcome()
{
    // Simply greets the user, and display the rules of bulls and cows.
    // Performs double duty as both welcome message and help prompt. 
    cout << "Welcome to the bulls and cows game.\n";
    cout << "Guess a secret code made up of 4 unique digits. After each guess, you'll receive clues:\n";
    cout << "Bull: A digit is correct and in the correct position.\n";
    cout << "Cow: A digit is correct but in the wrong position\n";
    cout << "Guess all four to win! Good luck.\n";
    cout << "Enter h or 'help' during gameplay to see this message again.\n";
}

void clear_cin()
{
    // Clears the cin buffer, in preperation for new input.
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool validate_seed(int& seed)
{
    // Given a potential seed, verifies if that integer is valid.
    // Pre condition: an integer passed by reference.
    // Post condition: must return a bool, representing if a valid seed was recieved.
    // The valid seed will be passed by reference to the calling function.
    // The bool represents if this operation was successful.
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
    // Pre-condition: none.
    // Post-condition: a valid integer (n) to be implemented as a seed.
    cout << "\n\nPlease enter any whole number, this will simply load the game with a given seed.\n";
    int n = 0;
    bool valid = false; 
    while (!valid)
        // The purpose of this loop is to force the user into a continual prompt for valid seed data.
        // Until valid => Prompt again.
    {
        valid = validate_seed(n);
    }
    cout << "Seed obtained " << n << "\n";
    return n;
}

void display_number(vector<int>& number)
{
    // Given a pre condition of : valid integer array (passed by reference to save memory).
    // Simply displays the given number using a range for loop (void post condit).
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
}

bool is_unique(int& digit, vector<int>& number)
{
    // verify the given int (digit) is unique in the given vector (number).
    // pre condition: A digit integer, and a number
    // post condition: A bool (unique or not)
    // is the number a digit. if not return false.
    // if it is, perform further work to determine if its unique.
    for (int n : number)
    {
        if (n == digit)
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

    cout << "Number generated succesfully: ";
    display_number(number);
    return number;
}

void load_game(vector<int>& number)
{
    // Given the core variables of the game.
    // (That is the users seed and the vector)
    // Load them with the proper data and continue.

    // PreConditions: a vector<int> of any valid form, it will be cleared.
    // No post conditions due to pass by ref.
    int seed = return_seed();
    number.clear();
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

bool process_guess(int& digit)
{
    // Obtain a valid guess from the user.
    // PreCondition: an int passed by reference, to be processed.
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
            // Quit game
        {
            quit = true;
            //**return true;
        }
        else if (guess == 'h')
            // Print help menu
        {
            welcome();
            clear_cin();
        }
        else if (char_to_int(guess) < 0 || char_to_int(guess) > 9)
            // Invalid input
        {
            cout << "Invalid entry: " << char_to_int(guess) << "\nDigits must range from (0-9):\n";
            clear_cin();
        }
        else
            // Valid input. Process guess
        {
            cout << "Success.\n";
            digit = char_to_int(guess);
            return false;
        }
    }
    return true;
}

bool prompt_guess(vector<int>& guess)
{
    // Loop through continously, prompting for a guess and calculating accordingly.
    // Pre-Condition: A valid vector of ints, passed by reference. 
    // Post-condition: A bool determing whether we should quit to main loop. False to quit.
    bool exit = false;

    for (int i = 0; i < 4; ++i)
    {   
        // Obtain a valid digit from the user.
        int digit = 0;
        // Exit will be true if the user requested to quit. 
        exit = process_guess(digit);
     
        if (exit)
        {   
            cout << "Exiting Game!";
            return false;
        }

        // Push back the valid digit into the guess.
        guess.push_back(digit);
        cout << "Loading " << digit << "\n";
    }
    return true;

}

bool play_again()
{   
    // Post Cond: A bool which determines if the user wants to play again. (true for yes)
    char input = ' ';
    bool play = true;

    clear_cin();
    cout << "You Won!\nPress any key to play again, or q to quit.\n";
    cin >> input;
    clear_cin();

    if (input == 'q')
    {
        play = false;
        cout << "Exiting game!\n";
    }
    return play;
}

bool check_score(vector<int>& number, vector<int>& guess, int& hit, int& miss)
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
    ++miss;

    guess.clear();

    if (bulls == 4)
    {
        if (play_again())
        {  
            ++hit; 
            cout << "You solved in " << miss << " guesses.\n";
            cout << "Playing again! That's " << hit << " wins so far\n";
            miss = 0;
            load_game(number);
        }
        else
        {
            return false;
        }
    }
    return true; 
}

void start_game()
{   
    // Pre condition: The vector containing a valid number to guess (number) and a vector containing the users guess (guess).
    // post condition, loop_game returns a bool, determining if the user wants to quit.

    bool loop = true;
    vector<int> number;
    vector<int> guess;
    int hit = 0;
    int miss = 0; 

    welcome();
    load_game(number);

    while (loop)
    {   
        // Loop will become false if the user enters a quit prompt. (Program exit)
        loop = prompt_guess(guess);

        if (!loop)
        {
            continue;
        }

        loop = check_score(number, guess, hit, miss);
    }// end while
}



int main()
// Implement the bulls and cows game. 
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

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
