// Name_pairs.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "std_lib_facilities.h"
#include "Name_pairs.h"
using Name::Name_pairs;


int main()
{
    Name_pairs pairs = Name_pairs(); 

    pairs.read_names();
    cout << "Now reading ages.\n";
    pairs.read_ages();
    pairs.print();
    cout << "Sorting\n";
    pairs.sort();
    pairs.print();
    cout << "RETEST.\n";
    pairs.sort();
    pairs.print(); 
}