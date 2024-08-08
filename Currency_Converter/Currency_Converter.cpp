// Currency_Converter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "std_lib_facilities.h"

void input_coin(int& coin, string message) {
    cout << "How many " << message << "?\n";
    cin >> coin;
}

void print_coin(int coin, string message) {
    cout << "You have " << coin << " " << message << '\n';
}

int main()
{
    double value = 0.0;

    // Store vectors of string and int values.
    vector<string> coins = { "pennies", "nickels", "dimes", "quarters", "half dollars", "dollar coins" };
    vector<int> int_coins(coins.size()); 
    vector<int> coin_values = { 1, 5, 10, 25, 50, 100 };
    
    // Loop through each and load in. 

    // Inputting coin counts.
    for (int i = 0; i < coins.size(); ++i) {
        input_coin(int_coins[i], coins[i]);
    }

    // Printing users coin count. 
    for (int i = 0; i < coins.size(); ++i) {
        print_coin(int_coins[i], coins[i]);
    }

    // Calculate.
    for (int i = 0; i < coins.size(); ++i) {
        value += (int_coins[i] * coin_values[i]);
    }

    // Set precision and print. 
    cout << fixed << setprecision(2);
    cout << "That's a total of: " << '$' << value/100; 
}
