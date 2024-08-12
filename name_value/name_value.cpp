// name_value.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "std_lib_facilties.h"

void print_welcome() {
    cout << "Enter a set of name and value pairs.\n";
    cout << "Example: Joe 17\n";
    cout << ": ";
}

bool verified_unique(string name, vector<string> names) {
    // Looks through the list of names, and verifies the given name does not match.
    // Effectively verifying the input as unique.
    bool valid = true;

    for (string n : names) {
        if (name == n) {
            valid = false;
            break;
        }
    }

    return valid;
}

void list_pairs(vector<string> names, vector<int> values) {
    cout << "Names : Values\n";

    for (int i = 0; i < names.size(); ++i) {
        cout << names[i] << ':' << values[i] << "\n";
    }
}

void find_score(string name, vector<string> names, vector<int> scores) {
    for (int i = 0; i < names.size(); ++i) {
        if (name == names[i]) {
            cout << "Score found: " << scores[i];
            return;
        }
    }
    cout << "name not found\n";
}

void find_name(int score, vector<string> names, vector<int> scores) {
    vector<string> found_names;

    for (int i = 0; i < names.size(); ++i) {
        if (score == scores[i]) {
            found_names.push_back(names[i]);
        }
    }
    
    if (found_names.size() <= 0) {
        cout << "score not found.\n";
    }
    else {
        cout << "found matching names:\n";
        for (string name : found_names) {
            cout << name << "\n";
        }
    }
}


int main()
{
    string name;
    int value; 

    vector<string> names;
    vector<int> scores;

    const string exit_str = "NoName";
    constexpr int exit_int = 0;

    bool quit = false; 

    //print_welcome();

    while (!quit) {
        print_welcome();

        if (cin >> name && cin >> value) {
            // Obtain input succesfully.
            cout << "You entered name: " << name << "\n";
            cout << "You entered value: " << value << "\n";

            if (name == exit_str && value == exit_int) {
                // If the name matches NoName 0, then exit the program.
                cout << "Exiting.\n";
                quit = true;
                break;
            }
            else if (!verified_unique(name, names)) {
                // If the name already exists, prompt again.
                cout << "This name already exists. Try again.\n";
            } else {
                // In this case the input is valid and verified. Push it back.
                names.push_back(name);
                scores.push_back(value);
                cout << "Valid input. Enter 'NoName 0' to quit at any time.\n\n";
            }
        }
        else {
            // Invalid input, something caused a cin error. 
            cout << "Invalid input. Try again.\n\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } // End while loop

    list_pairs(names, scores);

    while (true) {
        cout << "Enter a name to find the corresponding score.\n";
        cin >> name;
        find_score(name, names, scores);
        cout << "Enter a score to find the corresponding names.\n";
        cin >> value;
        find_name(value, names, scores);
    }


} // End main

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
