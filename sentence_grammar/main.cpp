// sentence_grammar.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "source.h";

vector<string> string_stream;


int main()
// Step One, make a program that can detect if input is a noun.
// Step Two, make a program that can detect if article + noun is still a noun. 
// Step Three, make a program that can detect if input is a sentence. 
{   
    try
    {
        fill_stream(string_stream);
        read_stream(string_stream);
        cout << "Poppin'";
        pop_front(string_stream);
        read_stream(string_stream);

        if (sentence(string_stream))
        {
            cout << " valid\n";
        }

    }
    catch (const std::exception& e) 
    {
        // Catch and print exceptions derived from std::exception
        cerr << "Exception caught: " << e.what() << std::endl;
    }
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
