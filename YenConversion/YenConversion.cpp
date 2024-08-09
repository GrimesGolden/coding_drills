// YenConversion.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "std_lib_facilities.h"

int main()
{
    bool valid = false;

    vector<char> currencies = { 'y', 'k', 'p' };
    vector<double> conversions = { 0.0068, 0.092, 1.27 };
    vector<string> currencies_str = { "yen", "kroner", "pounds" };

    char input = ' ';
    double value = 0;
    int index = 0;

    cout << "Welcome to the currency conversion program.\n" << "Please enter the currency to convert.\n";
    cout << "For yen enter y.\nFor kroner enter k.\nFor pounds enter p.\n";

    cout << ">>>";
    cin >> input;

    cout << fixed << setprecision(2);

    for (int i = 0; i < currencies.size(); ++i) {
        if (input == currencies[i]) {
            valid = true;
            index = i;
            break;
        }
    }

    if (valid) {
        cout << "Enter amount of " << currencies_str[index] << " to convert : >>>";
        cin >> value;
        cout << "Converting " << "$" << value << " " << currencies_str[index] << " to dollars.\n";
        value *= conversions[index];
        cout << "Result: $" << value << '\n';
    }
    else {
        cout << "Error. No such input: " << input << "\n";
    }
}