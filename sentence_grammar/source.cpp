#include "source.h";

bool noun(string word)
{   // Given a valid string.
    // (Pre condition)
    // Determines if the string is valid using the given criteria.
    // Post condition: bool; 
    bool status = false;
    if (word == "birds") {
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
}

