// calculator_attempt.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "std_lib_facilities.h"

class Token {
public:
    char kind; // what kind of token.
    int value; // for numbers, what type of value.
};

void get_value(vector<Token>& tokens, int value)
{
    Token t{ '8', value };
    cout << "Pushing back value token" << value << "\n";
    tokens.push_back(t);
}

void insert_value(vector<Token>& tokens, int value, int index)
{
    Token t{ '8', value };
    cout << "Inserting value token" << value << "\n";
    //  myVector.insert(myVector.begin() + indexToInsert, valueToInsert);
    tokens.insert(tokens.begin() + (index), t);
}



void get_operand(vector<Token>& tokens, char value)
{
    Token t{ value };
    cout << "Pushing back operand token" << value << "\n";
    tokens.push_back(t);

}

int calculate(char op, int lval, int rval)
{
    switch (op)
    {
    case '+':
        return (lval + rval);
        break;
    case '-':
        return (lval - rval);
        break;
    case '*':
        return (lval * rval);
        break;
    case '/':
        return (lval / rval);
        break;
    default:
        cout << "Error, " << op << " is not an operand";
        keep_window_open();
        return 0;
    }
}


void process_operand(vector<Token>& tokens, char op)
{
    for (int i = 0; i < tokens.size(); ++i)
    {   
        cout << "The size of tokens right now is: " << tokens.size();
        if (tokens[i].kind == op)
        {   
            // DEBUG
            cout << "This worked. With " << tokens[i].kind << " \n";
            cout << "LVAL worked: ";
            int lval = tokens[i - 1].value;
            cout << lval << "\n";
            cout << "RVAL worked: ";
            int rval = tokens[i + 1].value;
            cout << rval << "\n";

            int result = calculate(op, lval, rval);
            cout << "Result: " << result << " worked.\n";
            // confused yet?

            Token t = { '8', result };
            tokens[i + 1] = t;
            // myVector.begin() + (indexToKeep - 2), myVector.begin() + indexToKeep
            tokens.erase(tokens.begin() + i - 1, tokens.begin() + 1 + i); // DEBUG THIS LINE


            // myVector.erase(myVector.begin() + indexToRemove - 1, myVector.begin() + indexToRemove + 2);
           // tokens.erase(tokens.begin() + i + 1);
            //tokens.erase(tokens.begin() + i);

            //insert_value(tokens, result, (index - 1));
            cout << "Inserting " << result << "\n";
            --i;
        }
    }
    cout << "Broke the loop in process_operand\n";
}

void process_tokens(vector<Token>& tokens)
{
    process_operand(tokens, '*');
    process_operand(tokens, '/');
    process_operand(tokens, '+');
    process_operand(tokens, '-');

    cout << "Result " << tokens[0].value << "\n";
}

int token_calc()
{
    cout << "Please enter expression (we can handle +, -, *, and /)\n";
    cout << "add an x to end expression (e.g., 1+2*3x): ";
    int lval = 0;
    int rval;
    vector<Token> tokens;
    cin >> lval;

    if (!cin)
    {
        error("no first operand");
    }

    get_value(tokens, lval);

    for (char op; cin >> op;)
    {
        if (op != 'x')
        {
            cin >> rval;
            //get_value(tokens, rval);
        }

        if (!cin)
        {
            error("no second operand");
        }

        switch (op)
        {
        case '+':
        case '-':
        case '*':
        case '/':
            get_operand(tokens, op);
            get_value(tokens, rval);
            break;
        default:
            cout << "Exiting.";
            process_tokens(tokens);
            keep_window_open();
            return 0;
        }
    }
    error("bad expression");
}

int calc()
{
    cout << "Please enter expression (we can handle +, -, *, and /)\n";
    cout << "add an x to end expression (e.g., 1+2*3x): ";
    int lval = 0;
    int rval;
    cin >> lval;

    if (!cin)
    {
        error("no first operand");
    }

    for (char op; cin >> op;)
    {
        if (op != 'x')
        {
            cin >> rval;
        }

        if (!cin)
        {
            error("no second operand");
        }

        switch (op)
        {
        case '+':
            lval += rval;
            break;
        case '-':
            lval -= rval;
            break;
        case '*':
            lval *= rval;
            break;
        case '/':
            lval /= rval;
            break;
        default:
            cout << "Result: " << lval << "\n";
            keep_window_open();
            return 0;
        }
    }
    error("bad expression");
}

int main()
{
    try 
    {
        return token_calc();
    }
    catch (exception& e)
    {
        cout << e.what();
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
