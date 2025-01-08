// Name_pairs.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "std_lib_facilities.h"
#include "Name_pairs.h"
using Name::Name_pairs;


int main()
{
    cout << "We have created two pairs.\n";

    Name_pairs first; 
    Name_pairs second;

    cout << "Reading first\n";
    first.read_names();
    first.read_ages();

    cout << "Reading second\n";
    second.read_names();
    second.read_ages();

    cout << "Are they equal?\n";

    first.sort();

    if (first == second)
    {
        cout << "YES\n";
    } 
    else
    {
        cout << "NAH.\n";
    }

}