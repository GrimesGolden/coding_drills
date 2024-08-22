#include "source.h";

// GRAMMARS
vector<string> articles = { "the" };

vector<string> nouns = { "birds", "fish", "c++", "apple", "car", "tree", "computer", "book", "river", "dog", "house", "sun", "moon",
"mountain", "teacher", "phone", "pencil", "cats", "city", "ocean", "flower", "horses", "table",
"chair", "window", "plane", "boat", "road", "cloud", "star", "pen", "clock", "shoe",
"beach", "forest", "grass", "lamp", "school", "desk", "shirt", "hat", "door", "sand",
"train", "bicycle", "garden", "rain", "snow", "bridge", "cup", "map", "rock", "bed" };

vector<string> conjunctions = { "and", "or", "but" };

vector<string> verbs = { "rules", "fly", "swim" };


void pop_front(vector<string>& vec)
{   
    // Purpose: removes the first element from the given vector.
    // Pre Condition: A vector of string passed by reference. 
    // Post Condition: None, due to modifying by reference.
  
    // Remove the first element
    if (!vec.empty()) {
        vec.erase(vec.begin()); // Erase the first element
    }
}

bool end_detected(vector<string>& string_stream)
{
    // Pre-Condition: A string vectors passed by reference, required for modification (removal of '.').
    // Post-Condition: A bool, determining if it does in fact end with a period.  
    bool valid = false;
    
    if (string_stream.size() != 1)
    {   
        //A period only occurs at the end of a sentence.
        return valid;
    }

    else
    {   
        string word = string_stream[0];
        int last_char = word.size() - 1;
        char end = '.';

        if (word[last_char] != end)
        {   
            return valid;
        }
        else
        {   
            // If the last character is '.' then remove it, and return true.
            strip_input(string_stream[0]);
            valid = true;
            return valid; 
        }
    }
}
void fill_stream(vector<string>& string_stream)
{
    // Purpose: Fill a vector with the given line of input (sentence).
    // Pre-Condition: A vector of string, passed by ref.
    // Post-Condit: Due to pass by reference, returns no value.
    // 
    // Read a line of input from the user
    string line;
    cout << "Enter a sentence: ";
    getline(cin, line);

    // Create a string stream from the line of input
    istringstream stream(line);
    string word;

    // Extract words from the stream and store them in a vector
    while (stream >> word) {
        string_stream.push_back(word);
    }
}

void read_stream(vector<string>& string_stream)
{   // Purpose: Output the "string_stream" vector of strings as a sentence.
    // Pre-Condition: A vector of string, passed by ref.
    // Post-Condit: Due to pass by reference, returns no value.
    cout << "You entered:";
    // Output individual words
    for (const auto& w : string_stream) {
        cout << w << " ";
    }

    cout << "\n";
}

void strip_input(string& input)
{   
    // Strips the '.' from a given string. such as "hello." ==> "hello"
    // Pre-Condition: Any valid string, passed by reference.
    // Post-Condition: None, string will be altered by reference. 
    // 
    // In the event the strings last element is a '.': pop back


    if (input.size() > 1) // This is important, because "." is not to be stripped. 
    {
        int last_index = input.size() - 1;
        char last = input[last_index];

        if (last == '.')
        {   
            input.pop_back();
        }
    }
}

bool check_grammar(vector<string>& string_stream, vector<string>& valid_strings)
{
    // Purpose: checks the grammar of the given stream, using the valid string reference.
    // Pre Condition: A string stream, passed by reference for modification, and a valid string vector, passed by ref for ease of memory.
    // Post Condition: Returns a bool, signifying a valid grammar rule for the given stream and terms (T). 
    bool status = false;
    // This handles the unique case of a verb, which also determines the end of certain sentences. 
    string verb = "rules";


    if (valid_strings[0] == verb)
    {   
        // If we are checking for a verb...
        if (end_detected(string_stream) || string_stream.size() > 1)
        {   
            // If its the end of a sentence or possibly contains a further conjunction the merely...
            //continue
        }
        else
        {   
            // return false, this is already not a valid verb.
            return status;
        }
    }


    if (!string_stream.empty())
        // Perform standard checking for given terms and stream. 
    {
        // If the stream (sentence) is not empty, check that the first string element matches a valid grammar term.
        string input = string_stream[0];

        // If it does match a term remove that element from the sentence, and return true. 
        for (string word : valid_strings) {
            if (word == input) {
                pop_front(string_stream);
                status = true;
            }
        }
    }

    return status;
}

bool phrase(vector<string>& string_stream)
{   // Purpose: Determine if the given sentence begins with a phrase.
    // Pre condition of valid string vector: passed by reference for memory and clarity.
    // Post Condition: A bool determing if phrase (T)

    bool valid = false;

    if (check_grammar(string_stream, articles))
    {
        if (check_grammar(string_stream, nouns))
        {   
            // In the event that this stream contained both an article, and a noun, return true.
            // The entire phrase has now been popped from the string. 
            valid = true;
        }
    }
    else
    {   
        // Return false, because phrases only begin with an article.
        return valid;
    }
} // end function.

bool sentence(vector<string>& string_stream)
{
    // Purpose: Determine if the given stream, represents a valid sentence.
    // Pre Condition: A vector of string passed by reference, for memory and clarity.
    // Post Condition: A bool, defining if the given sentence represents a phrase.

    bool valid = false;

    // If the string_stream is empty, we have an error
    // If the string stream is not empty, we are off to a possibly valid start.
    // Then lets begin at the top. Does it contain a noun or a phrase?
    if (!string_stream.empty() && (check_grammar(string_stream, nouns) || phrase(string_stream)))
    {
        if (check_grammar(string_stream, verbs) && string_stream.empty())
            // If the sentence is now empty (ended), and the final word was a valid verb.
            // Then its a sentence.
        {
            valid = true;
            return valid;
        }
        else if (check_grammar(string_stream, conjunctions))
        {
            // If the rest of the stream contains a valid sentence after the conjunction.
            // Return true.
            valid = sentence(string_stream);
            return valid;
        }
        else
        {
            // False.
            return valid;
        }
    } // End if noun or phrase
    else
    {   // not a noun or noun phrase == not a sentence. 
        return valid;
    }
}

