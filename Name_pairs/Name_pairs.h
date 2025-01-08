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

    private:
        vector<string> name;
        vector<double> age;

    };
}