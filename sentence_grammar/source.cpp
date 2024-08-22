#include "source.h";

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
bool end_detected(string& word)
{   
    // Pre-Condition: Can handle any string, but only verbs should ever enter this function (test for this).
    // Post-Condition: A bool, determining if it does in fact end with a period. 
    // Note: we should alter strip_word to strip only a copy of the word, because we only want to test if its a verb. 
    bool valid = false;

    if (word.size() <= 1)
    {   
        // If the size of the word suggests an empty string. 
        // Return, we do not want to handle this scenario.
        return valid;
    }
    else if (word.size() > 2)
    {   
        // In the case we have some reasonable size of string.
        // Test that the last char is in fact a  '.'.
        int last_index = word.size() - 1;
        char end = '.';

        if (word[last_index] == end)
        {
            valid = true;
        }
    }
    return valid;
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

        if (end_detected(word))
        {   
            cout << "Ending input.";
            break;
        }
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

bool article(vector<string>& string_stream)
{   
    // Purpose: Determine if the given sentence begins with an article.
    // Pre condition of valid string vector: passed by reference for memory and clarity.
    // Post Condition: A bool determing if article (T)

    vector<string> articles = { "the" };

    bool status = false;

    if (!string_stream.empty())
    {   
        // If the stream (sentence) is not empty, check that the first string element is an article.
        string input = string_stream[0];

        // If it is an article remove that element from the sentence, and return true. 
        for (string word : articles) {
            if (word == input) {
                pop_front(string_stream);
                status = true;
            }
        }
    }

    return status;
}

bool verb(vector<string>& string_stream)
{   
    // Purpose: Determine if the given sentence begins with a verb.
    // Pre condition of valid string vector: passed by reference for memory and clarity.
    // Post Condition: A bool determing if verb (T)

    vector<string> verbs = { "rules", "fly", "swim"};

    // we strip input here, because this could grammatically be the end of a sentence.
    // DEBUG be careful with this. Its only needed under particular circumstances, which sentence logic will handle.
    // At the very least we may want to NOT pass by reference here. Why? = We dont want to alter the sentence merely to determine if it contains a verb.
    //strip_input(input);

    bool status = false;

    if (!string_stream.empty())
    {
        // If the stream (sentence) is not empty, check that the first string element is a verb.
        string input = string_stream[0];

        // If it is a verb remove that element from the sentence, and return true. 
        for (string word : verbs) {
            if (word == input) {
                pop_front(string_stream);
                status = true;
            }
        }
    }

    return status;
}

bool conjunction(vector<string>& string_stream)
{   
    // Purpose: Determine if the given sentence begins with a conjunction.
    // Pre condition of valid string vector: passed by reference for memory and clarity.
    // Post Condition: A bool determing if conjunction (T)

    // We do not strip input, because there is no valid sentence that has conjunction followed by '.' 
    vector<string> conjunctions = { "and", "or", "but" };

    bool status = false;

    if (!string_stream.empty())
    {
        // If the stream (sentence) is not empty, check that the first string element is a verb.
        string input = string_stream[0];

        // If it is a verb remove that element from the sentence, and return true. 
        for (string word : conjunctions) {
            if (word == input) {
                pop_front(string_stream);
                status = true;
            }
        }
    }

    return status;
}

bool noun(vector<string>& string_stream)
{   
    // Purpose: Determine if the given sentence begins with a noun.
    // Pre condition of valid string vector: passed by reference for memory and clarity.
    // Post Condition: A bool determing if noun (T)

    vector<string> nouns = { "birds", "fish", "c++", "apple", "car", "tree", "computer", "book", "river", "dog", "house", "sun", "moon",
"mountain", "teacher", "phone", "pencil", "cats", "city", "ocean", "flower", "horses", "table",
"chair", "window", "plane", "boat", "road", "cloud", "star", "pen", "clock", "shoe",
"beach", "forest", "grass", "lamp", "school", "desk", "shirt", "hat", "door", "sand",
"train", "bicycle", "garden", "rain", "snow", "bridge", "cup", "map", "rock", "bed" };

    bool status = false;

    if (!string_stream.empty())
    {
        // If the stream (sentence) is not empty, check that the first string element is a verb.
        string input = string_stream[0];

        // If it is a verb remove that element from the sentence, and return true. 
        for (string word : nouns) {
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

    if (article(string_stream))
    {
        if (noun(string_stream))
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

    // Begin.
    bool valid = false;

    // If the string_stream is empty, we have an error
    if (string_stream.empty())
    {
        error("Empty vector passed to sentence()");
    }
    else
    {
        // If the string stream is not empty, we are off to a possibly valid start.
        // Lets begin at the top. Does it contain a noun or a phrase?
        if (noun(string_stream) || phrase(string_stream))
        {
            // If it does contain a noun or phrase? is it followed by a verb?
            // 
        }
    }




}

