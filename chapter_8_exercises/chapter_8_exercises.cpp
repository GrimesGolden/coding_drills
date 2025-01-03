// chapter_8_exercises.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "std_lib_facilities.h"
#include<time.h>
#include<cstdlib>

void print(string label, vector<int>numbs)
   //Exercise 1. 
   // Write a function print() that prints a vector of ints to cout. Give it two arguments; A string for labeling the output, and a vector.
{   
    cout << label; 

    for (int i = 0; i < numbs.size(); ++i)
    {
        cout << numbs[i] << "." << "\n";
    }
}

void print_str(string label, vector<string>numbs)
{
    cout << label;

    for (int i = 0; i < numbs.size(); ++i)
    {
        cout << numbs[i] << "." << "\n";
    }
}

void fibonacci(int x, int y, vector<int>& fibs, int n)
// Returns a vector of fibonnaci numbers.
// x and y are ints
// v is an empt vector<int> and n is the number of elements to put into v
{
    for (int i = 0; i < n; ++i)
    {
        if (i == 0)
        {
            fibs.push_back(x);
        }
        else if (i == 1)
        {
            fibs.push_back(y);
        }
        else if (i > 1)
        {
            int prev = fibs[(i - 1)];
            int prev_2 = fibs[(i - 2)];

            int sum = prev + prev_2;
            fibs.push_back(sum);
        }
        else
        {
            error("error in fibonnaci");
        }
    }
}

// write two functions that reverse the order of elements in a vector<int>
/*
* For example, 1, 3, 5, 7, 9 becomes 9, 7, 5, 3, 1
* the first reverse function shoild produce a new vector with the reversed sequence leaving the old unchanged
* the other should reverse the elements without using any other vector. 
* 
* now redo it with a vector of strings
*/
vector<int> swap_value(vector<int> v)
{   
    vector<int> new_v;

    for (int i = v.size() - 1; i >= 0; --i)
    {
        new_v.push_back(v[i]);
    }

    return new_v; 
}

void swap_ref(vector<int>& v)
// Reverses any vector of integers by reference.
{
    int last_element = v.size() - 1;
    int n = v.size() - 1;

    for (int i = 0; i < n; ++i)
    {
        int temp = v[i];
        v[i] = v[n];
        v[n] = temp;

        --n; 
    }
}

vector<string> swap_string_v(vector<string> v)
{
    vector<string> new_v;

    for (int i = v.size() - 1; i >= 0; --i)
    {
        new_v.push_back(v[i]);
    }

    return new_v;
}

void swap_string_ref(vector<string>& v)
// Reverses any vector of integers by reference.
{
    int last_element = v.size() - 1;
    int n = v.size() - 1;

    for (int i = 0; i < n; ++i)
    {
        string temp = v[i];
        v[i] = v[n];
        v[n] = temp;

        --n;
    }
}

void generate_names(int total, vector<string>& names) {
    // Creates a vector of random names
    // The parameter determines the number of psuedo-random names to load
    // ("how many names you want")

    // Seed the rand() function. 
    srand(time(0));

    // Declare variables of ints to store index.
    int f_index = 0;
    int l_index = 0;
    // Vectors to store name sections.
    vector<string> first = { "Danny", "Virgil", "Johnny", "Lil", "ASAP", "Ratchet", "Piper", "Master", "Vector", "Jackson", "Shootie", "Big", "Lieutenant", "Commander", "Froggie", "Pimp", "Mr.", "Merlot", "Fattie", "Shawn", "Slaine", "HomeBoy", "Prozac", "Goats", "Dirt", "Young", "Freddy", "Ridgeback", "Dollarbill", "Tyler", "Sadboy", "Conner", "Maxo", "Dante", "Tyrone", "Taylor", "Doug", "Slapface", "Susboy", "Joe", "Oldboy", "Sadman", "Captain"};
    vector<string> last = { "TwoDicks", "FastHands", "McKenzie", "Splice", "FaceSlap", "Harambe", "TwoHands", "McGee", "McBride", "TwoShort", "TwoChains", "Shephard", "BackHand", "StealYoGurl", "Leather", "LostHisShoe", "HighIQ", "Wigs", "White", "Sandman", "Turner", "Milkbone", "Nasty", "Papoose", "Jackson", "Countbills", "McGregor", "FatPocks", "Kream", "LayPipe", "Brown", "Swift", "Manchester", "2000", "Rogan" , "Cockles", "Dicks"};
    // The "random" name itself.
    string name;

    // Loop through using the parameter, which the number of names we wish to generate, and output. 
    for (int i = 1; i <= total; ++i) {
        f_index = rand() % first.size();
        l_index = rand() % last.size();

        name = first[f_index] + " " + last[l_index];

        names.push_back(name);
    }

}

void load_names(vector<string>& name, vector<double>& age, int size)
{   
    generate_names(size, name);

    for (int i = 0; i < size; ++i)
    {
        double a = 0;
   
        cout << "Enter " << name[i] << "'s age >> ";

        if (cin >> a)
        {
            cout << "Age entered succesfully.\n";
        }
        else
        {
            cout << "Incorrect age, fuck you, entering 0\n";
            a = 0; 
        }

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        age.push_back(a);
    }

    cout << "Vectors loaded succesfully\n";
}

void create_sort_names(int size)
{   
    // Creates and sorts however many names. 
    // Size of the list is based off parameter
    vector<string> name;
    vector<double> age;

    load_names(name, age, size);

    vector<string> unsorted_name = name;
    sort(name.begin(), name.end());

    for (int i = 0; i < name.size(); ++i)
    {
        for (int j = 0; j < unsorted_name.size(); ++j)
        {
            if (name[i] == unsorted_name[j])
            {
                cout << name[i] << " , age " << age[j] << "\n";
                break;
            }
        }
    }
}

double compute_index(const vector<double>& price, const vector<double>& weight)
{
    // write a function that given two vector<double> price and weight, 
    // computes a value, an index, that is the sum of all price[i] * weight[i]. 
    // Make sure to have weight.size() == price.size()
    if (price.size() != weight.size())
    {
        return -1;
    }
    else
    {
        double index = 0;

        for (int i = 0; i < price.size(); ++i)
        {
            double product = price[i] * weight[i];
            index += product;
        }

        return index; 
    }
}

double max_index(const vector<double>& numbs)
{   
    double max = 0;

    if (numbs.size() <= 0)
    {
        cout << "Error, this vector is empty.";
        max = -1;
    }
    else
    {
        double max_numb = numbs[0];
        double max_i = 0;

        for (int i = 0; i < numbs.size(); ++i)
        {
            if (numbs[i] > max_numb)
            {
                max_numb = numbs[i];
                max_i = i;
            }
        }

        cout << "The max number in this vector is " << max_numb << " occuring at index " << max_i << ".\n";

        max = max_numb;
    }

    return max;
}

double min_index(const vector<double>& numbs)
{   
    double min = 0;

    if (numbs.size() <= 0)
    {
        cout << "Error, this vector is empty.";
        min = -1;
    }
    else
    {
        double min_numb = numbs[0];
        double min_i = 0;

        for (int i = 0; i < numbs.size(); ++i)
        {
            if (numbs[i] < min_numb)
            {
                min_numb = numbs[i];
                min_i = i;
            }
        }

        cout << "The minimum number in this vector is " << min_numb << " occuring at index " << min_i << ".\n";
        min = min_numb;
    }

    return min; 
}

double mean(const vector<double>& numbs)
{
    double sum = 0;

    for (double n : numbs)
    {
        sum += n;
    }

    return (sum / ( numbs.size() ) );
}

double median(vector<double>& numbs)
{   
    int middle = numbs.size() / 2;
    double median = 0;
    
    sort(numbs.begin(), numbs.end()); 

    if ((numbs.size() % 2) == 0)
    {
        // Its even
        double m = numbs[middle];
        m += numbs[--middle];

        median = m / 2;
    }
    else if ((numbs.size() % 2) != 0)
    {
        // Its odd
        median = numbs[middle];
    }
    else
    {
        cout << "Fucked.\n";
        return -1;
    }
}

struct Data
{
    double mean;
    double median;
    double min;
    double max;
};

Data compute_stats(vector<double> numbs)
{
    // Completes exercise 11. 
    cout << "Computing statistics.\n";

    Data stats; 

    stats.mean = mean(numbs);
    stats.median = median(numbs);
    stats.min = min_index(numbs);
    stats.max = max_index(numbs);

    cout << "Success. Returning.\n";

    return stats;
}

void print_until_ss(const vector<string>& v, string quit)
{   
    int count = 0;
    for (string s : v)
    {
        if (s == quit) {
            ++count;
        }

        if (count == 2)
        {
            return;
        }

        cout << s << '\n';
    }
}

vector<int> count_chars(const vector<string>& words)
{   
    vector<int> lengths;

    for (string word : words)
    {
        int count = 0;
        for (char c : word)
        {
            ++count;
        }
        lengths.push_back(count);
    }

    return lengths;
}

string longest_string(const vector<string>& words)
{
    vector<int> count = count_chars(words);

    int max = count[0]; 
    int index = 0; 

    for (int i = 0; i < count.size(); ++i)
    {
        if (count[i] > max)
        {
            max = count[i];
            index = i; 
        }
    }

    return words[index]; 
}

string shortest_string(const vector<string>& words)
{
    vector<int> count = count_chars(words);

    int min = count[0];
    int index = 0;

    for (int i = 0; i < count.size(); ++i)
    {
        if (count[i] < min)
        {
            min = count[i];
            index = i;
        }
    }

    return words[index];
}

string first(vector<string> words)
{
    sort(words.begin(), words.end());

    return words[0];
}

string last(vector<string> words)
{
    sort(words.begin(), words.end());

    return words[words.size() - 1];
}

void read_const(const int numb)
{
    cout << "The number is " << numb << "\n";
}


int main()
{
    vector<string> words {
        "apple", "banana", "cherry", "date", "elephant",
        "forest", "giraffe", "honey", "island", "jungle",
        "kite", "lemon", "mountain", "night", "ocean",
        "pencil", "quartz", "river", "sunset", "tiger",
        "umbrella", "violet", "whisper", "xylophone", "yacht"
    };

    vector<int> count = count_chars(words);

    for (int i = 0; i < words.size(); ++i)
    {
        cout << words[i] << " has length " << count[i] << ".\n";
    }

    cout << "The longest string is " << longest_string(words)  << "\n";
    cout << "The shortest string is " << shortest_string(words) << "\n";
    cout << "The lexicographically first word is " << first(words) << " and the lexicographically last is " << last(words) << "\n";

    read_const(102); 

}
