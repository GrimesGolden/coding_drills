// key_value_drill.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "std_lib_facilities.h"

void clear_cin()
{
    // Clears the cin buffer, useful in preparation for new input.
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string to_lower(string word)
{   
    // Create a lower case version0 of a given word.
    // Pre condition: a valid string to copy.
    // Post condition: a lower case version of that string.
    string copy = word;

    if (copy.size() > 0)
    {
        copy[0] = tolower(copy[0]);
    }
    return copy;
}

bool valid_string(string& date)
{   
    // Loop through the various days of the week, and confirm that the given string matches a valid choice.
    // Pre Condition: A valid string of any kind, passed by reference to save memory.
    // Post Condition: A bool determining if string is valid (T)
    vector<string> dates = { "mon", "monday", "tue", "tuesday", "wed", "wednesday", "thu", "thursday", "fri", "friday", "sat", "saturday", "sun", "sunday", "q", "quit"};

    for (string valid : dates)
    {
        if (to_lower(date) == valid)
        {
            return true;
        }
    }

    return false; 

}


bool check_quit(vector<string> dates) 
{   
    // Verify that the user has entered a quit request.
    // pre condition: A valid string copy (we dont want to change potential input).
    // post condition: A bool representing quit condition (T to quit).

    if (dates.size() > 0)
    {
        string input = to_lower(dates[dates.size()-1]);

        if (input[0] == 'q')
        {
            return true;
        }
    }
    return false; 
}

void reject_value(int& rejected)
{
    //  Self explanatory.
    cout << "Rejected\n";
    ++rejected;

}

string format_day(string day)
{   
    // Reduce the given day of the week to 3.
    // Pre-Condition: A string that is greater than 3.
    // Post Cond: The string itself; 

    string reduced = day;

    if (day.size() > 3)
    {   
        // Clear the given string.
        reduced = "";

        for (int i = 0; i < 3; ++i)
        {
            reduced += day[i];

        }
    }

    reduced = to_lower(reduced);
    return reduced;
}

bool last_value(string& search, vector<string>& dates, int index)
// This function is used to determine if the given string item (search)
// is the last item in the vector. This is used to verify if we should print a comma ','.
// Also useful for other logical purposes.
// Pre Condition: A string, a vector of string > 0, and an index to search from.
// Post Condition: A bool (T if last value)
{
    bool last = true;

    // Index +1 so we dont count the element itself as a value to search for, (that would cause clear issues). 

    for (int i = (index + 1); i < dates.size(); ++i)
    {
        if (format_day(dates[i]) == search)
        {
            last = false;
        }
    }

    return last;
}

void print_values(string day, vector<string>& dates, vector<int>& values)
// For the given string (day) searches through the dates and finds each value it matches with.
// For that value, print it to the console. Thereby displaying the given values.
// Pre condition: A string to search for matches, the vector of user entered days, the vector of user entered values. 
// Post condition: None, prints to the console only.
{   
    // Return all the values entered for the given day. 
    string search = format_day(day);
    bool value_found = false;

    for (int i = 0; i < dates.size(); ++i)
    {
        if (search == format_day(dates[i]))
            // If a day matches the given search value.
        {
            cout << values[i];
            //DEBUG
            if (!last_value(search, dates, i))
            {
                cout << ", ";
            }

            value_found = true;
        }
    }

    if (!value_found)
    {
        cout << "no values";
    }

}

void compute_results(vector<string>& dates, vector<int>& values)
{   
    
    vector<string> days = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

    cout << "DAYS : VALUES" << "\n";

    for (string day : days)
    {   
        cout << day << ": ";
        print_values(day, dates, values);
        cout << "\n";
    }
}

void process_input(vector<string>& dates, vector<int>& values, int& rejected)
{   
    // Processes an entire line of input from the user.
    // Pre Condition: A vector of strings, ints and an int all passed by ref.
    // Post condition: None.

    // Tasks:
    // If invalid input or format, function rejects that input.
    // prepares for a quit check.
    // pushes back valid inputs. 
    string input = "";
    string day = " ";
    int value = 0;

    cout << "Format [string int]\n";
    cout << "quit 0: to exit program.\n";
    cout << "Input key value pair: ";

    getline(cin, input);
    istringstream stream(input);

    if (stream >> day >> value)
    {
        if (valid_string(day))
        {   
            cout << "Pushing back day.\n";
            dates.push_back(day);
            cout << "Pushing back value.\n";
            values.push_back(value);
        }
        else if (!valid_string(day))
        {   
            // The from [string int] was valid, but the date itself was incorrect.
            // Also rejected.
            reject_value(rejected);
        }
    }
    // The input was not in key value form [string int]
    else
    {
        reject_value(rejected);
    }
}

int main()
{   
    double quit = false;

    vector<string> dates;
    vector<int> values;
    int rejected = 0;

    while (!quit)
    {
        process_input(dates, values, rejected);
        quit = check_quit(dates);
        cout << "\n\n\n\n";
    }

    compute_results(dates, values);
    cout << "With " << rejected << " rejected values.\n";
    cout << "Exiting program.\n";
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
