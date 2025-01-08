#pragma once
#include "std_lib_facilities.h";

namespace Name
{
    class Name_pairs
    {
    public:
        void read_names();

        void read_ages();

        void print();

        void sort();

        friend ostream& operator<<(ostream& os, const Name_pairs& np); // declare as a friend to give it direct access to the name and age vector, 

        friend bool operator ==(const Name_pairs& left, const Name_pairs& right); 

    private:
        vector<string> name;
        vector<double> age;

    };
}