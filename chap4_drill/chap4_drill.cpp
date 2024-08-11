// chap4_drill.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "std_lib_facilities.h"



void clear_buffer() {
    // Clears the buffer to prevent errors.
    std::cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
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

char prompt_char() {
    // Prompt user for valid character.
    char input = ' ';
    cout << "Enter '|' to quit, or any character to continue.\n\n>>";
    cin >> input;
    clear_buffer();
    return input;

    /*
    while (input != '|') {
        cout << "Enter '|' to quit, or any character to continue.\n\n>>";
        cin >> input;

        if (input == '|') {
            return;
        }

        clear_buffer();

        // Prompt for a number.
        prompt_number(); 
        // return this number to main

        // if successful prompt for unit.
        prompt_unit();

        // if unit successfull

        // collect original number, unit, convert it, and then push them to three vectors.
        // those three vectors are the converted numbers, the original numbers, and their original units. 
    
    
    */
}

bool valid_unit(string unit) {
    vector<string> units = { "cm", "m", "in", "ft" };
    bool valid = false;

    for (string u : units) {
        if (unit == u) {
            valid = true;
        }
    }
    return valid;
}

double prompt_number() {
    // Collect number from user.

    double num = 0;
    bool input_required = true;

    while (input_required) {
        cout << "Enter a number: ";

        if (cin >> num) {
            // Handle valid input
            cout << "You entered: " << num << "\n";
            input_required = false;
        }
        else {
            // Call out invalid input, and clear buffer.
            cout << "Invalid input.\n\n";
            clear_buffer();
            // Return to beginning of while loop.
        }
    }
    cout << "Returning valid number.\n";
    clear_buffer();
    return num;
}

string prompt_unit() {
    //collect unit from user.

    // Will prompt continuously until valid string acquired. 
    string unit = "";
    bool input_required = true;

    while (input_required) {
        cout << "Enter a unit: ";
        if (cin >> unit && valid_unit(unit)) {
            // if the unit is valid collect it.
            // if invalid prompt for more
            cout << "Unit successful\n";
            input_required = false; 
        }
        else {
            cout << "Invalid unit\n";
            clear_buffer();
            //continue;
        }
    }

    return unit; 
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

    vector<double> converted_nums;
    vector<double> unconverted_nums;
    vector<string> users_units;

    double users_num = 0;

    bool valid_unit = false;



    // start the loop.

    // obtain a valid number.

    // obtain a valid unit. 

    // push these to vectors.

    // convert and push.

    // break from while loop. 
    // finalize and push.


    while (input != '|') {
        // Collect the char
        input = prompt_char(); 

        if (input == '|') {
            // if input is exit, then go back to the while loop, so it can break out.
            // We are done. 
            continue; 
        }
        
        // Collect number
        users_num = prompt_number();

        // Collect unit
        unit = prompt_unit();


        cout << "You entered " << users_num << unit << "\n";
        cout << "Converted to meters this is " << convert_meters(users_num, unit[0]) << "m\n";
        converted_nums.push_back(convert_meters(users_num, unit[0]));
        unconverted_nums.push_back(users_num);
        users_units.push_back(unit);
    }
    // End while loop

    sort(converted_nums.begin(), converted_nums.end());
    std::cout << "The smallest value entered was " << converted_nums[0] << "m\n";
    std::cout << "The largest value entered was " << converted_nums[converted_nums.size() - 1] << "m\n";
} // End main

