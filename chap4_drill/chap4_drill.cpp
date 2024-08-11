// chap4_drill.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "std_lib_facilities.h"

int main()
{
    // Step 1. 
    char input = ' ';

    while (input != '|') {
        int num1 = 0;
        int num2 = 0;
        cout << "Enter '|' to quit, or any character to continue.";
        cin >> input; 

        cout << "\nEnter two integers: \n" << "First int: >>";
        
        if (cin >> num1) {
            cout << "\nSecond int: >>";
        }
        else {
            // Call out invalid input, and clear buffer.
            cout << "Invalid input.\n\n";
            cin.clear();
            // Return to beginning of while loop.
            continue;
        }

        if (cin >> num2) {
            cout << "You entered: " << "First number: " << num1 << "\nSecond number: " << num2 << "\n";
        }
        else {
            cout << "Invalid input.\n\n";
            cin.clear();
            continue;
            //return 0;
        }
    }
}
