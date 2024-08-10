// Ascii.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "std_lib_facilities.h"

// Exercises and drills for PPP. 

int square(int x) {
    // Computes the square using addition. 
    // Try this page 116. 
    int value = 0;

    for (int i = x; i >= 1; --i) {
        value += x;
    }

    return value;
}

string str_lower(string word) {

    // Returns a lower case version of the given string. 
    // Does not modify the given string. 

    string lower = word;

    for (int i = 0; i < word.size(); ++i) {
        char c = tolower(word[i]);
        lower[i] = c;
    }

    return lower;
}

void censor(vector<string> words) {

    // Prints the given vector of strings, with any words that match the censored words "BLEEPED" out.
    // Does not modify given vector.
    vector<string> banned = { "Shit", "Fuck", "Piss", "Broccoli", "Cunt", "Assfucker", "Rape", "Whore", "Hello" };

    cout << "'nYou entered: \n";

    // Itirate through the word list
    for (string word : words) {
        // Itirate through the banned word list.
        for (string x : banned) {
            // If the current word matches a banned word (not case sensitive)
            if (str_lower(word) == str_lower(x)) {
                // Replace the word with BLEEP and exit the iteration of banned list (go to the next word)
                word = "BLEEP";
                break;
            }
        }
        cout << word << "\n";
    }
}

int main()
{

    // Try this, prints Ascii
    /*
    for (int i = 0; i < 26; ++i) {
        cout << char('a' + i) << " " << int{ char('a' + i) } << " ";
        cout << char('A' + i) << " " << int{ char('A' + i) } << "\n";
    }
    */

    /*
    int i = 0;

    while (i < 26) {
        cout << char('a' + i) << " " << int{ char('a' + i) } << "\n";
        ++i;
    }
    */

    // Excercise to bleep out certain words. (pg 125 ppp)

    // Prompt user for words and fill a vector.
    // Call above function. 
    cout << "Enter words: ";

    vector<string> words;

    for (string word; cin >> word;) {
        words.push_back(word);
    }

    censor(words);
}