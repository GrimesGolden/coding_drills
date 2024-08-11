// chap4_drill.cpp : This file contains the 'main' function. Program execution begins and ends there.

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
        cout << "Enter a unit: (cm, m, in or ft): ";
        if (cin >> unit && valid_unit(unit)) {
            // if the unit is valid collect it.
            // if invalid prompt for more
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

double sum_vector(vector<double> v) {
    double sum = 0;

    for (double num : v) {
        sum += num;
    }

    return sum;
}

void print_results(vector<double> conv_nums, vector<double> nums, vector<string> units) {
    // Print the smallest value, the largest value, the sum of the total values.
    // Also print every value and it's appropriate conversion.

    vector<double> sorted_nums = conv_nums;
    sort(sorted_nums.begin(), sorted_nums.end());

    std::cout << "The smallest value entered was " << sorted_nums[0] << "m\n";
    std::cout << "The largest value entered was " << sorted_nums[sorted_nums.size() - 1] << "m\n";

    std::cout << "The total sum is " << sum_vector(sorted_nums) << "m\n";

    std::cout << "Your values are as follows: \n";

    for (int i = 0; i < conv_nums.size(); ++i) {
        cout << nums[i] << units[i] << " converted to: " << conv_nums[i] << "m\n";
    }
}

int main()
// The drill for chapter 4, a program that converts various inputs based on their units.
{   
    // Create variables to store the users char input (Determine when to quit the program).
    // The units for that input.
    char input = ' ';
    string unit = "";

    // Create three vectors to store these numbers converted to meters, their unconverted form, and the units for each value.
    vector<double> converted_nums;
    vector<double> unconverted_nums;
    vector<string> users_units;

    // This will represent the users inputed number
    double users_num = 0;

    bool valid_unit = false;

    while (input != '|') {
        // Unit the correct prompt is issued to quit.
        // 
        // Collect the char
        input = prompt_char(); 

        if (input == '|') {
            // if input is exit, then go back to the while loop, so it can break out.
            // We are done. 
            continue; 
        }
        
        // Collect the number
        users_num = prompt_number();

        // Collect the unit
        unit = prompt_unit();

        // Push back the now valid values.
        converted_nums.push_back(convert_meters(users_num, unit[0]));
        unconverted_nums.push_back(users_num);
        users_units.push_back(unit);

        // Inform user what value they entered, and it's appropriate conversions.
        cout << "You entered " << users_num << unit << "\n";
        cout << "Converted to meters this is " << convert_meters(users_num, unit[0]) << "m\n";
    }
    // End while loop

    if (converted_nums.size() <= 1) {
        // If the vectors have less than one element, we cannot do anything interesting with that.
        cout << "You must enter more than 1 value to analyze results.\n";
    }
    else {
        print_results(converted_nums, unconverted_nums, users_units);
    }
} // End main

