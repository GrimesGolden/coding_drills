// chap4_drill.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "std_lib_facilities.h"

void print_smaller(double x, double y) {
    // Step 5. Change the program do it writes out if the numbers are almost equal.
    // After determining which is larger or smaller.
    double smallest = 0;
    double largest = 0;

    double difference = abs(x - y);

    if (x == y) {
        cout << "The numbers are equal.\n";
        return;
    } else if (x < y) {
        smallest = x;
        largest = y;
    } else if (y < x) {
        smallest = y;
        largest = x;
    }
  
    cout << smallest << " is smaller than " << largest << "\n";
    
    if (difference <= (1.0 / 100)) {
        cout << "The numbers are almost equal\n";
    }
}

void clear_buffer() {
    // Clears the buffer to prevent errors.
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    std::cin.clear();
}

int main()
{
    // Step 1.

    // Prompt the user for two numbers then print them in a continuous loop.
    // '|' exits the loop.

    char input = ' ';

    while (input != '|') {
        double num1 = 0;
        double num2 = 0;
        cout << "Enter '|' to quit, or any character to continue.";
        cin >> input;

        if (input == '|') {
            continue; 
        }

        clear_buffer();

        cout << "\nEnter two numbers: \n" << "First num: >>";
        
        if (cin >> num1) {
            cout << "\nSecond num: >>";
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
            print_smaller(num1, num2);
        }
        else {
            cout << "Invalid input.\n\n";
            cin.clear();
            continue;
            //return 0;
        }
    }
}
