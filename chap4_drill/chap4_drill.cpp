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

double convert_meters(double num, char unit) {
    // Converts the given number into meters, based off its unit.
    // Yes there are magic numbers, too lazy to change. In an ideal world we would have these as some form of constexpr. 

    switch (unit) {
    case 'c':
        num = num / 100;
        break;
    case 'm':
        break;
    case 'i':
        num = (num * (2.54 / 100));
        break;
    case 'f':
        num = ((num * 12 * 2.54) / 100);
        break;
    default:
        cout << "Conversion error in convert_meters function.\n";
        break;
    }

    return num;
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
    string unit = "";

    double largest = 0;
    double smallest = 0;
    double users_num = 0;

    bool initial_loop = true;
    bool valid_unit = false;

    vector<string> units = { "cm", "m", "in", "ft" };
    vector<double> converted_nums;

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
        clear_buffer(); 
        cout << "Enter a unit: ";

        if (cin >> unit) {
            for (string u : units) {
                if (unit == u) {
                    valid_unit = true;
                }
            }
            if (valid_unit) {
                //convert unit to meters and push
                cout << "You entered " << users_num << unit << "\n";
                cout << "Converted to meters this is " << convert_meters(users_num, unit[0]) << "m\n";
                converted_nums.push_back(convert_meters(users_num, unit[0]));
                valid_unit = false;
            }
            else if (!valid_unit) {
                cout << "Please enter a valid unit.\n";
                clear_buffer();
                continue;
            }
        }
        else {
            clear_buffer();
            cout << "Invalid input, how could this happen?\n";
        }



    }
    // End while loop

    sort(converted_nums.begin(), converted_nums.end());
    std::cout << "The smallest value entered was " << converted_nums[0] << "m\n";
    std::cout << "The largest value entered was " << converted_nums[converted_nums.size() - 1] << "m\n";
} // End main

