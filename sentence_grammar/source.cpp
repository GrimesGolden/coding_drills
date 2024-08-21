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

bool article(string input)
{
    // Given a pre condition of valid string.
    // Determines if the given string is an article.
    vector<string> articles = { "the" };

    bool status = false;

    for (string word : articles) {
        if (word == input) {
            status = true;
        }
    }

    return status;
}

bool verb(string& input)
{
    // Given a pre condition of valid string.
    // Determines if the given string is a verb.
    vector<string> verbs = { "rules", "fly", "swim"};

    // we strip input here, because this could grammatically be the end of a sentence.
    strip_input(input);

    bool status = false;

    for (string word : verbs) {
        if (word == input) {
            status = true;
        }
    }

    return status;
}

bool conjunction(string input)
{
    // Given a pre condition of valid string.
    // Determines if the given string is a conjunction.

    // We do not strip input, because there is no valid sentence that has conjunction followed by '+'. 
    vector<string> verbs = { "and", "or", "but" };

    bool status = false;

    for (string word : verbs) {
        if (word == input) {
            status = true;
        }
    }

    return status;
}

bool noun(string& input)
{
    vector<string> nouns = { "birds", "fish", "c++", "apple", "car", "tree", "computer", "book", "river", "dog", "house", "sun", "moon",
"mountain", "teacher", "phone", "pencil", "cat", "city", "ocean", "flower", "horse", "table",
"chair", "window", "plane", "boat", "road", "cloud", "star", "pen", "clock", "shoe",
"beach", "forest", "grass", "lamp", "school", "desk", "shirt", "hat", "door", "sand",
"train", "bicycle", "garden", "rain", "snow", "bridge", "cup", "map", "rock", "bed" };

    strip_input(input);

    bool status = false;

    for (string word : nouns) {
        if (word == input) {
            status = true;
        }
    }

    return status;
}

bool noun_phrase(string& input)
{   // Given a valid string.
    // (Pre condition)
    // Determines if the string is a noun phrase (article + noun) using the given criteria.
    // Post condition: bool; 

    // if the input string is an article, then check if the following string is a noun. Only under these conditions is it a noun
    
    if (article(input))
    { // Check the next input.
        string next = "";
        cin >> next;

        if (next == ".")
        {
            // In the event the article is followed by a period,
            // Replace it in the cin (so the loop can read a '.' in main) and return false. 
            // Because "the." is not a noun.
            cin.putback('.');
            return false;
        }
        else if (next != ".")
        {   
            // In the event there is not a '.', we first combine input with this next string (whatever it might be).
            // First strip the next word of '.'. Cin buffer now holds only '.'
            strip_input(next);
            input = (input + " " + next);
            // Now a check to see if this next string (next) is a noun.
            if (noun(next))
                // If it is return true we have (article + noun)
            {   
                return true;
            }
            else 
            {   
                // In this case we dont have a noun phrase, what we have is an article combined with something not a noun.
                // A grammatical error, which is why we combined it with the orginal input, to make for a useful error message back in the calling function.
                return false;
            }

        } // end else if 
    }
    else if (!article(input))
    {
        return false;
    }
} // end function.

bool sentence(string& input)
{   
    // Pre step: First check to see if this "sentence" is just a ".": in this case put the "." back and return false. // But is this not included in step one?
    // step one: is it a noun or a noun phrase (the input that is)
    // if it is not, it automatically fails. 
    if (noun(input) || noun_phrase(input))
    {
        string next = "";
        cin >> next;
       // cout << "Value of next on line 169 is: " << next << "\n";
        // This step again, it could almost be a function, but cant justify it. 
        // This step exists to update the original input with the full extent of the sentence. 
        // Used both for error messages and success outputs. 
        strip_input(input);
        input = (input + " " + next);


        if (verb(next))
        {
            // Sentence == noun or noun phrase + verb
            return true;
        }
        else if (!verb(next))
        {
            // False this is not a sentence. 
            return false;
        }
        else
        {
            // I see no way this could occur, but compiler warns about control paths. 
            error("Reality has imploded. Control paths defy all rational logic.");
            return false;
        }
     } // end if
     else if (!noun(input) && !noun_phrase(input)) // its not either of these
    {
        return false;
    }


    // step two: if it IS a noun or noun phrase, check to see if its followed by a verb.
    // in this case, and this case only, we have a sentence.
    else 
    {
        error("Error in sentence() function, control path failed.");
        return false; 
    }
}

