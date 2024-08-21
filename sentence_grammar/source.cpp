#include "source.h";

void strip_input(string& input)
{   
    // Strips the '.' from a given string. such as "hello." ==> "hello"
    // Pre-Condition: Any valid string, passed by reference.
    // In the event the strings last element is a '.':
    // This function will put a copy of the '.' back into the cin buffer 
    // then pop_back this element, effectively destroying it. 
    if (input.size() > 1) // This is important, because "." is not to be stripped. 
    {
        int last_index = input.size() - 1;
        char last = input[last_index];

        if (last == '.')
        {   
            //cin.putback(last);
            //input.erase (input.begin()+last_index);
            cin.putback(last);
            input.pop_back();
        }
    }
}

bool noun(string input)
{   // Given a valid string.
    // (Pre condition)
    // Determines if the string is valid using the given criteria.
    // Post condition: bool; 

    vector<string> nouns = { "birds", "fish", "c++", "apple", "car", "tree", "computer", "book", "river", "dog", "house", "sun", "moon",
"mountain", "teacher", "phone", "pencil", "cat", "city", "ocean", "flower", "horse", "table",
"chair", "window", "plane", "boat", "road", "cloud", "star", "pen", "clock", "shoe",
"beach", "forest", "grass", "lamp", "school", "desk", "shirt", "hat", "door", "sand",
"train", "bicycle", "garden", "rain", "snow", "bridge", "cup", "map", "rock", "bed" };

    bool status = false;
    /*
    * if (word == "birds") {
        status = true;
    }
    else if (word == "fish") {
        status = true;
    }
    else if (word == "C++") {
        status = true;
    }
    else {
        //do nothing.
    }
    return status;
    */

    for(string word:nouns) {
        if (word == input) {
            status = true;
        }
    }

    return status; 
}

