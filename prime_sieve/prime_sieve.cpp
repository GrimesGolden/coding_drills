// prime_sieve.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "std_lib_facilities.h"

bool is_marked(int num, vector<int> marked) {
    // Returns true, if the given number is marked, that is it shows up in the marked vector. 
    bool found = false; 

    for (int i = 0; i < marked.size(); ++i) {
        if (num == marked[i]) {
            found = true;
            break;
        }
    }
    return found;
}

bool find_marked(int index, int p, vector<int> numbers, vector<int>& marked) {
    // Using the given index, iterate by p.
    // Every number on the list which is a multiple of p will be added to the marked list.
    // In essence this function performs the step in the algorithm of finding every 'pth' marked number.
    // It will also perform the step of returning false if no numbers are left marked, meaning we have exhausted the algorithm and are done.
    bool valid = false;

    for (int i = index; i < numbers.size(); i += p) {
        if (!is_marked(numbers[i], marked)) {
            // if the number is not marked, add it to the marked list.
            marked.push_back(numbers[i]);
            valid = true;
        }
    }
    return valid;
}

void return_primes(vector<int> numbers, vector<int> marked) {
    // Given a list of numbers, and the marked list.
    // Returns the remaining numbers which are not on the full marked vector.
    // Therefore, it returns a list of primes, as those numbers which remain are by default prime at this stage. 
    vector<int> primes;

    for (int i = 0; i < numbers.size(); ++i) {
        if (!is_marked(numbers[i], marked)) {
            // If number is not marked it must be prime.
            primes.push_back(numbers[i]);
        }
    }
    
    for (int num : primes) {
        cout << num << ".\n";
    }
}



int main()
{   
    // Print a list of primes from 1 to 100, using the Sieve of Eratosthenes. 
    // Not this program will only work with a list of ordered numbers beginning at 2 i.e 2 to 100. 
    vector<int> numbers;
    vector<int> marked; 

    for (int i = 2; i <= 100; ++i) {
        // Load a vector with the numbers 2 to 100.
        numbers.push_back(i);
    }

    int p = numbers[0];
    bool valid = true;

    // Iterate through the list by p.
    for (int i = 0; i < numbers.size(); ++i) {
        // Find the first non marked number.
        if (!is_marked(numbers[i], marked)) {
            // This becomes out first 'p'.
            // Using this p, begin from every number which is 'p' greater. That is, divisible by 2 if p == 2 for example. 
            // We use i+numbers[i] to designate that we do not want p itself to become marked, but every number which is past it 
            // (for example 2 is not marked but 4 is).
            valid = find_marked((i+numbers[i]), numbers[i], numbers, marked);
            if (!valid) {
                // If there ever comes a time that no p is found in the entire list.
                // We shall break out of the for loop at that time, we are done at this point. 
                break; 
            }
        } // end if
    } // end for


    cout << "Printing primes\n";

    return_primes(numbers, marked);
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
