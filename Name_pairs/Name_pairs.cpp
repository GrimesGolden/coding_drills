#include "Name_pairs.h"

namespace Name
{
    void Name_pairs::read_names()
    {
        // Reading in names. 
        string user_input;

        cout << "Please enter names, or enter STOP to stop reading in names.\n";
        cout << "Enter a name >>";
        while (getline(cin, user_input))
        {
            if (user_input == "STOP")
            {
                break;
            }

            name.push_back(user_input);
            cout << "You entered " << user_input << ".\n";
            cout << "Enter next name >>";
        }
    }

    void Name_pairs::read_ages()
    {
        double user_input = 0;

        for (const string& n : name)
        {
            bool valid = false;

            while (!valid)
            {
                cout << "Enter " << n << "'s age >> ";

                if (cin >> user_input)
                {
                    age.push_back(user_input);
                    cout << "success\n";
                    valid = true;
                }
                else {
                    cout << "Try again.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }
        }

        cin.clear(); // Stops input from being stored here. 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    void Name_pairs::print()
    {
        // print out name[i], age[i] pairs
        for (int i = 0; i < name.size(); ++i)
        {
            cout << name[i] << " is age " << age[i] << ".\n";
        }
    }

    void Name_pairs::sort()
    {
        // sorts the ages, and names.

        // make a copy of names. 
        vector<string> name_copy = name;
        vector<double> age_copy = age;
        // sort the names. 
        std::sort(name.begin(), name.end());

        // names are now alphabetically sorted.

        // for each name, sort through the original name vector until you find the original index. 
        for (int i = 0; i < name.size(); ++i)
        {
            for (int j = 0; j < name_copy.size(); ++j)
            {
                if (name[i] == name_copy[j])
                {
                    age_copy[i] = age[j];

                }
            }
        }

        age = age_copy;
        // replace age[i] with the new index. 
    }

    // operator overloads
    ostream& operator<<(ostream& os, const Name_pairs& np)
    {
        // print out name[i], age[i] pairs
        for (int i = 0; i < np.name.size(); ++i)
        {
            os << np.name[i] << " is age " << np.age[i] << ".\n";
        }

        return os; 
    }

    bool operator ==(const Name_pairs& left, const Name_pairs& right)
    {   
        bool equal = true; 

        for (int i = 0; i < left.name.size(); ++i)
        {
            if (left.name[i] != right.name[i])
            {
                equal = false;
                break;
            }
        }

        if (!equal)
        {
            return equal;
        }
        else
        {
            for (int i = 0; i < left.age.size(); ++i)
            {
                if (left.age[i] != right.age[i])
                {
                    equal = false;
                    break;
                }
            }
        }

        return equal; 
        
    }
} // End namespace Name
