// sentence_grammar.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "std_lib_facilities.h";

bool noun(string word)
{   // Given a valid string.
    // (Pre condition)
    // Determines if the string is valid using the given criteria.
    // Post condition: bool; 
    bool status = false;
    if (word == "birds") {
        status = true;
    }
    else if (word == "fish") {
        status = true;
    }
    else if (word == "C++") {
        status = true;
    }
    else {
        //do nothing.
    }
    return status;
}
int main()
// Step One, make a program that can detect if input is a noun.
{   
    string input = "";
    

    while (input != ".")
    {
        cin >> input;

        if (noun(input)) {
            cout << input << " is a noun.\n";
        }
        else if (!noun(input)) {
            cout << input << " is NOT A noun.\n";
        }
        else {
            cout << input << " is invalid.\n";
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