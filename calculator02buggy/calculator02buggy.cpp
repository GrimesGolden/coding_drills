//
// This is example code from Chapter 6.7 "Trying the second version" of
// "Software - Principles and Practice using C++" by Bjarne Stroustrup
//

/*
    This file is known as calculator02buggy.cpp
*/

#include "std_lib_facilities.h"

const char quit = 'q';
const char print = ';';
const char number = '8';
const string prompt = "> ";
const string result = "= ";

//------------------------------------------------------------------------------

class Token{
    // This class represents a token for the grammar.
    // These tokens have both a kind represented by char and a type represented by a double value.
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
    if (full) error("putback() into a full buffer"); // We cannot put a token into a full buffer.
    buffer = t;       // copy t to buffer
    full = true;      // buffer is now full
}

//------------------------------------------------------------------------------

void Token_stream::ignore(char c)
{
    if (full && c == buffer.kind)
        // If the buffer is full and it's tokens kind matches the given char
        // We set full to false which means this token in buffer will be discarded next time we do a putback().
    {   
        full = false; // effectively ignore the c in buffer.
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
        cin >> val;   // Then read it back as a double.
        // We know have token with both a kind and value.
        return Token(number, val);  
    }
    default:
        error("Bad token");
    }
}

//------------------------------------------------------------------------------

Token_stream ts;        // provides get() and putback()  // We create an instance of the token stream called ts. 


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
    Token t = ts.get(); // Get a token from cin.
    switch (t.kind) {
    case '(':    // handle '(' expression ')' 
    {
        double d = expression(); // This will ascertain what expression exists after the '(' char.
        t = ts.get(); // And this will get the token after the expression, valid if equal to == ')'
        if (t.kind != ')') {
            error("')' or expected");
        }
        return d; // Now returns the calculated expression, effectively adding () capability. For example (5*5) returns 25. 
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
        // If the Token displays a kind which represents a number. 
        // We need to look at the next token (to see if its factorial).
        Token next = ts.get();
        if (next.kind != '!')
        {
            // If not just put the next token back for later, then perform the standard primary() tasks.
            ts.putback(next);
            return t.value; // return the numbers literal value. (Treat the token as a standard primary)
        }
        else if (next.kind == '!')
        {
            // In this case we must perform the factorial task. 
            int f = t.value; // create an integer from the doubles value
            f = factorial(f); // and use it in the factorial function.
            return f; // return this value, and do not putback the '!' token (it has already served its purpose here)
        }
    }
    case '-':
        return -primary(); // In the case of a negative in front of the value, perform primary again, but switch it to a negative value.
    case '+':
        return primary(); // This just allows for a unary '+' operator, for example +2 returns 2.
    default:
        error("primary expected"); // If we call primary on any other token kind, we will return an error.
    }
}

//------------------------------------------------------------------------------

// deal with *, /, and %
double term()
{   
    // In the case of term we call primary and call it left.
    // Primary will call another token in from the buffer using ts.get().
    double left = primary(); 
    Token t = ts.get();  // We know call get once more, for the next token.
    // For example "2*2" would first have left = 2, then ts.get would aquire the '*' token.

    while (true) {
        switch (t.kind) {
        case '*':
            // We once again call the primary function into task.
            left *= primary();
            // The purpose of getting the next token here, is to either chain terms together such as 2*2*2, or else discover token kinds that trigger default cases.
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
            left = fmod(left, d); //The C library function double fmod(double x, double y) returns the remainder of x divided by y.
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

    // Also clear the cin buffer and disregard any remaining input inside. 
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
        try // Errors will occur inside the while loop, meaning we do not leave the function.
        {
            cout << prompt;
            Token t = ts.get(); // A curious note, if a ';' is detected at the end of an expression it will be recieved here, from within expression(), not from the above cin.
            while (t.kind == print) // eat '='
            {   
                // If the token is equal to ';' just keep getting more input.
                t = ts.get();
            }

            if (t.kind == quit)
                // It is this logic, which causes statements such as "2+2;" to return 4.
                // expression() only handles up to 2+2, leaving ";" in the buffer to be recieved by ts.get().
            {
                return;
            }

            ts.putback(t);
            cout << result << expression() << '\n'; // Note: this is the all important call, to expression(). Which handles the grammar. 
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