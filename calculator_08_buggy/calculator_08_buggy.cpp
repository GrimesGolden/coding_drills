
/*
	calculator08buggy.cpp

	Helpful comments removed.

	We have inserted 3 bugs that the compiler will catch and 3 that it won't.
*/

#include "std_lib_facilities.h"

struct Token {
	// Holds a token with a value, kind and possible name for Variable representations. 
	char kind;
	double value = 0; // Stops the warning about value not being declared. 
	string name;
	Token(char ch) :kind(ch), value(0) { } // default constructor
	Token(char ch, double val) :kind(ch), value(val) { } // constructor for the case of a char (kind) with a double value
	Token(char ch, string n) :kind(ch), name(n) { } // Constructor for initializing name with kind and string (Variable).
};

class Token_stream {
	bool full;
	Token buffer;
public:
	Token_stream() :full(0), buffer(0) { } // Stream intializes with empty buffer

	Token get(); 
	void unget(Token t) { buffer = t; full = true; }

	void ignore(char);
};

// Various consts to improve efficiency and clarity.
const char let = 'L';
const char quit = 'q'; 
const char print = ';';
const char number = '8';
const char name = 'a';
const char square_root = 'S';
const string prompt = "> ";
const string result = "= ";
const string declkey = "let";

Token Token_stream::get()
{	

	if (full) { full = false; return buffer; }
	char ch;
	cin >> ch;
	switch (ch) {
		// In these cases, return only a char (Let the token represent itself.)
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case '=':
	case print: 
	case quit:
		return Token(ch);
		// For the following cases, the token holds its kind (number) as well as its double value. 
	case '.':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	{	cin.unget(); // Put the character back into the input stream, then read it in as a double. 
	double val;
	cin >> val;
	return Token(number, val); // Call the appropriate constructor. 
	}
	default:
		// This handles all other cases, with specifics for the logic regarding a variable, example "let x = 2". 
		if (isalpha(ch)) { // Is the character an alphabet symbol. 
			string s;
			s += ch; // Begin filling a string with the character. 

			while (cin.get(ch) && (isalpha(ch) || isdigit(ch))) s += ch; // While succesfully reading in a character ch, if its equal to an alphabet symbol or a digit, add it to the string s.
			cin.unget(); // Put the character which ended this string filling process (perhaps a ';' or '=' for example) back into the cin buffer.
			if (s == declkey) return Token(let); // If s is == "let" we are declaring a variable.
			if (s == "sqrt") return Token(square_root); // I will let 'S' represent a square root call.
			return Token(name, s); // Return a Token with the appropriate kind and string value, it will represent a variable. 
		}
		error("Bad token"); // Fall through. 
	}
}

void Token_stream::ignore(char c)
{
	// Ignore input up to the appropriate character (c). 
	if (full && c == buffer.kind) {
		full = false;
		return;
	}
	full = false;

	char ch;
	while (cin >> ch)
		if (ch == c) return;
}

struct Variable {
	string name;
	double value;
	Variable(string n, double v) :name(n), value(v) { }
};

vector<Variable> names; // Hold the Variables created by declaration() calls. 

double get_value(string s)
{
	// Getters and setters for variables in the names vector.
	
	for (int i = 0; i < names.size(); ++i)
		if (names[i].name == s) return names[i].value;  
	error("get: undefined name ", s);
}

void set_value(string s, double d)
{
	for (int i = 0; i <= names.size(); ++i)
		if (names[i].name == s) {
			names[i].value = d;
			return;
		}
	error("set: undefined name ", s);
}

bool is_declared(string s)
{
	for (int i = 0; i < names.size(); ++i)
		if (names[i].name == s) return true;
	return false;
}

Token_stream ts; // Token stream created here.

double expression(); // Declaration to appease functions below. 
double statement();

double primary()
{	
	// Fufills the last portion of the grammar.
	// A primary is a +/- number, an (expression) in parentheses, or the name of a variable (its value). 

	Token t = ts.get();
	switch (t.kind) {
	case '(':
	{	
		double d = expression();
		t = ts.get();
		if (t.kind != ')') error("'(' expected");
		return d;
	}
	case '-':
		return -primary();
	case number:
		return t.value;
	case name:
		return get_value(t.name);
	case square_root:
	{
		t = ts.get(); // Must disregard '('
		if (t.kind != '(') error("'(' expected"); // ts.get() will find most bad tokens but expressions like sqrt*2); are more subtle.
		double d = expression(); // Get the inner expression from sqrt(expression());
		t = ts.get(); // Have to disregard the outer ')' too; 
		if (t.kind != ')') error("'(' expected");
		return(sqrt(d));
	}
	default:
		error("primary expected");
	}
}

double term()
{	
	// Fufills the intermediate portion of the grammar. 
	// A tern is a, primary*primary, primary/primary, or a primary%primary. 

	double left = primary();
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '*':
			left *= primary();
			break;
		case '/':
		{	double d = primary();
		if (d == 0) error("divide by zero");
		left /= d;
		break;
		}
		case '%':
		{ 
			double d = primary();
			if (d == 0) error("%:divide by zero");
			left = fmod(left, d); //The C library function double fmod(double x, double y) returns the remainder of x divided by y.
			break;
		}
		default:
			ts.unget(t);
			return left;
		}
	}
}

double expression()
{	
	// The first portion of the grammar. 
	// An expression is a term or term+term or term-term. 

	double left = term();
	while (true) { // This while loop is subtle, the default statement is the critical step which will locate a ';' statement and allow left value to be returned. 
		// Example: 2+2 breaks and goes back into the very loop. 2+2; is what triggers a default and returns 4. 
		Token t = ts.get();
		switch (t.kind) {
		case '+':
			left += term();
			break;
		case '-':
			left -= term();
			break;
		default:
			ts.unget(t);
			return left;
		}
	}
}

double declaration()
{	
	// Fufills the syntax of a declaration i.e "let x = 2+2;"

	Token t = ts.get();
	if (t.kind != name) error("name expected in declaration");
	string name = t.name;
	if (is_declared(name)) error(name, " declared twice"); // This simply checks if any other Variable by the given name is present in the vector.
	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of ", name); // Must match above syntax.
	double d = expression(); // Any valid expression is allowed in a declaration, but it be declared with some expression. No "let x;" allowed
	names.push_back(Variable(name, d)); // The creation of a Variable occurs here. 
	return d; // For the logic in functions below to work, declaration must return a value. 
}

double statement()
{	// Fufills a major portion of the grammar.
	// A statement is either a declaration (a variable declaration) or an expression (mathematical). 
	Token t = ts.get();
	switch (t.kind) {
	case let:
		return declaration();
	default:
		ts.unget(t);
		return expression();
	}
}

void clean_up_mess()
{
	// Ignore everything up to the print symbol. 
	// Also clears the cin buffer and ignores, to prepare for a clean input.
	ts.ignore(print);
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}


void calculate()
{
	while (true) try {
		// Note that we catch errors inside the loop, meaning loop continues after printing and cleanup.
		cout << prompt;
		Token t = ts.get();
		while (t.kind == print) t = ts.get(); // If the token is ';' get more input. This is why the prompt works 
		//This will disregard further ;; characters. While maintaining the loop.
		if (t.kind == quit) return; // Exit the loop with 'q'
		ts.unget(t); // Put the token back, we just wanted to check if it was a quit or a print. 
		cout << result << statement() << endl; // The all important call to statement. 
	}
	catch (runtime_error& e) {
		cerr << e.what() << endl;
		clean_up_mess();
	}
}

int main()

try {
	// Adding a predefined name k, meaning 1000.
	names.push_back(Variable("k", 1000));
	calculate();
	return 0;
}
catch (exception& e) {
	cerr << "exception: " << e.what() << endl;
	char c;
	while (cin >> c && c != ';');
	return 1;
}
catch (...) {
	cerr << "exception\n";
	char c;
	while (cin >> c && c != ';');
	return 2;
}