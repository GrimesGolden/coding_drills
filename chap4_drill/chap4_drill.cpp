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

    // Step 7. Change the body of the loop, so it reads just one double each time.
    // Track which is the largest and smallest, if it's smallest so dar write "smallest so far after."
    // If its largest so far, write "largest so far, after the number."

    char input = ' ';
    double largest = 0;
    double smallest = 0;
    double users_num = 0; 
    bool initial_loop = true;

    while (input != '|') {
        cout << "Enter '|' to quit, or any character to continue.";
        cin >> input;

        if (input == '|') {
            continue; 
        }

        clear_buffer();

        // Collect input
        if (initial_loop) {
            cout << "\nEnter first number: ";
        }
        else {
            cout << "\nEnter another number: ";
        }
        
        if (cin >> users_num) {
            if (initial_loop) {
                largest = users_num;
                smallest = users_num;
                initial_loop = false;
            }
        }
        else {
            // Call out invalid input, and clear buffer.
            cout << "Invalid input.\n\n";
            cin.clear();
            // Return to beginning of while loop.
            continue;
        }

        // Handle input
        if (users_num < smallest) {
            smallest = users_num;
        }
        else if (users_num > largest) {
            largest = users_num;
        }

        cout << "You entered: " << users_num << "\n";
        cout << "The largest number entered so far is: " << largest << "\n";
        cout << "The smallest number entered so far is: " << smallest << "\n";


        
    }
}
