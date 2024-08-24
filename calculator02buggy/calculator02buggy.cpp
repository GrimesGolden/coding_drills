//
// This is example code from Chapter 6.7 "Trying the second version" of
// "Software - Principles and Practice using C++" by Bjarne Stroustrup
//

/*
    This file is known as calculator02buggy.cpp

    I have inserted 5 errors that should cause this not to compile
    I have inserted 3 logic errors that should cause the program to give wrong results

    First try to find an remove the bugs without looking in the book.
    If that gets tedious, compare the code to that in the book (or posted source code)

    Happy hunting!

*/

#include "std_lib_facilities.h"

const char quit = 'q';
const char print = ';';
const char number = '8';
const string prompt = "> ";
const string result = "= ";

//------------------------------------------------------------------------------

class Token{
public:
    char kind;        // what kind of token
    double value;     // for numbers: a value 
    Token(char ch)    // make a Token from a char
        :kind(ch), value(0) { }
    Token(char ch, double val)     // make a Token from a char and a double
        :kind(ch), value(val) { }
};

//------------------------------------------------------------------------------

class Token_stream {
public:
    Token_stream();   // make a Token_stream that reads from cin
    Token get();      // get a Token (get() is defined elsewhere)
    void putback(Token t);    // put a Token back
    void ignore(char c); // Ignores input up to c.
private:
    bool full = false;        // is there a Token in the buffer?
    Token buffer;     // here is where we keep a Token put back using putback()
};

//------------------------------------------------------------------------------

// The constructor just sets full to indicate that the buffer is empty:
Token_stream::Token_stream()
    :full(false), buffer(0)    // no Token in buffer
{
}

//------------------------------------------------------------------------------

// The putback() member function puts its argument back into the Token_stream's buffer:
void Token_stream::putback(Token t)
{
    if (full) error("putback() into a full buffer");
    buffer = t;       // copy t to buffer
    full = true;      // buffer is now full
}

//------------------------------------------------------------------------------

void Token_stream::ignore(char c)
{
    if (full && c == buffer.kind)
    {   
        full = false; // effectively discard the c in buffer.
        return;
    }

    full = false;

    // now search input.
    char ch = 0;
    while (cin >> ch)
    {
        if (ch == c)
            return;
    }
}

//------------------------------------------------------------------------------

Token Token_stream::get()
{   
    // Read characters from cin and compose a token.

    if (full) {       // do we already have a Token ready?
        // remove token from buffer
        full = false;
        return buffer;
    }

    char ch;

    cin >> ch;    // note that >> skips whitespace (space, newline, tab, etc.)

    switch (ch) {
    case print:    // for "print"
    case quit:    // for "quit"
    case '{':
    case '}':
    case '(':
    case ')':
    case '!': 
    case '+':
    case '-':
    case '*':
    case '/': 
    case '%':
        return Token(ch);        // let each character represent itself

    case '.': // A floating point literal can start with a dot.
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9': 
    {
        cin.putback(ch);         // put digit back into the input stream
        double val;
        cin >> val;   
        // read a floating-point number
        return Token(number, val);  
    }
    default:
        error("Bad token");
    }
}

//------------------------------------------------------------------------------

Token_stream ts;        // provides get() and putback() 

//------------------------------------------------------------------------------

double expression();    // declaration so that primary() can call expression()

//------------------------------------------------------------------------------

// deal with numbers and parentheses
int factorial(int input)
{
    // Working factorial function.
    // Pre Condition: Must take an integer between 0 and 16.
    // Post Condition: An integer value. 
    if (input == 0 || input == 1)
    {
        return 1;
    }
    else if (input < 0)
    {
        error("negative factorial detected.");
    }
    else if (input >= 17)
    {
        error("factorial is too large (max is 16!)");
    }
    else
    {
        int result = input;
        while (input > 1)
        {
            result *= (input - 1);
            --input;
        }
        return result;
    }
}

double primary()
{
    Token t = ts.get();
    switch (t.kind) {
    case '(':    // handle '(' expression ')'
    {
        double d = expression();
        t = ts.get();
        if (t.kind != ')') {
            error("')' or expected");
        }
        return d;
    }
    case '{':
    {
        double d = expression();
        t = ts.get();
        if (t.kind != '}') {
            error("'}' or expected");
        }
        return d;
    }
    case number:
    {
        // we use '8' to represent a number
        // We need to look at the next token (to see if its factorial).
        Token next = ts.get();
        if (next.kind != '!')
        {
            // If not just put it back and perform the standard primary() tasks.
            ts.putback(next);
            return t.value; // return the numbers value
        }
        else if (next.kind == '!')
        {
            // In this case we must perform factorial task. 
            int f = t.value; // create an integer from the doubles value
            f = factorial(f); // and use it in the factorial function.
            return f; // return this value, and no not putback the '!' token (it has been used up here)
        }
    }
    case '-':
        return -primary();
    case '+':
        return primary(); 
    default:
        error("primary expected");
    }
}

//------------------------------------------------------------------------------

// deal with *, /, and %
double term()
{
    double left = primary();
    Token t = ts.get();        // get the next token from token stream

    while (true) {
        switch (t.kind) {
        case '*':
            left *= primary();
            t = ts.get();
            break;
        case '/':
        {
            double d = primary();
            if (d == 0) error("divide by zero");
            left /= d;
            t = ts.get();
            break;
        }
        case '%':
        {
            double d = primary();
            if (d == 0) error("%:divide by zero");
            left = fmod(left, d);
            t = ts.get();
            break;
        }
        default:
            ts.putback(t);     // put t back into the token stream
            return left;
        }
    }
}

//------------------------------------------------------------------------------

// deal with + and -
double expression()
{
    double left = term();      // read and evaluate a Term
    Token t = ts.get();        // get the next token from token stream

    while (true) {
        switch (t.kind) {
        case '+':
            left += term();    // evaluate Term and add
            t = ts.get();
            break;
        case '-':
            left -= term();    // evaluate Term and subtract
            t = ts.get();
            break;
        default:
            ts.putback(t);     // put t back into the token stream
            return left;       // finally: no more + or -: return the answer
        }
    }
}

//------------------------------------------------------------------------------

void clean_up_mess()
{
    // Ignore all input up to ';'.
    ts.ignore(print);

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

//------------------------------------------------------------------------------

void calculate()
{   
    cout << "Welcome to our simple calculator.\nPlease enter expression using floating point numbers.\n";
    cout << "Operators available are *, +, / and -\nTo print result enter =\nTo exit enter 'x'\n>>";

    while (cin)
    {
        try
        {
            cout << prompt;
            Token t = ts.get();
            while (t.kind == print) // eat '='
            {
                t = ts.get();
            }

            if (t.kind == quit)
            {
                return;
            }

            ts.putback(t);
            cout << result << expression() << '\n';
        } // end try
        catch (exception& e)
        {
            cout << "ERROR CAUGHT.\n";
            cerr << e.what() << "\n";
            clean_up_mess();
        } // end catch
    } // end while
}

//------------------------------------------------------------------------------

int main()
{
    calculate();
    return 0;
}

//------------------------------------------------------------------------------