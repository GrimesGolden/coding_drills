
/*
	calculator08buggy.cpp

	The final version of Bjarnes calculator. 
	Contains exercises for Chapter 7 1-4. 

	how to use program: 
	variables use the following format "let x = 5"
	the rest follow format: "2+2;"
	pow(2);
	reassignment is allowed x = 4;
*/

#include "std_lib_facilities.h"

struct Token {
	// This structure represents the basic form of Tokens in the game, used for the grammar. 
	char kind; 
	double value = 0; // Stops the warning about value not being declared. 
	string name;
	Token(char ch) :kind(ch), value(0) { } // default constructor
	Token(char ch, double val) :kind(ch), value(val) { } // constructor for the case of a char (kind) with a double value
	Token(char ch, string n) :kind(ch), name(n) { } // Constructor for initializing name with kind and string (Variable).
};

class Token_stream {
	// Holds the current token, can carry a single Token in buffer. 
	// Can discard the held Token. 
	bool full;
	Token buffer;
public:
	Token_stream() :full(0), buffer(0) { } // Stream intializes with empty buffer

	Token get(); 
	void unget(Token t) { buffer = t; full = true; } // Place a token back in the buffer.

	void ignore(char);
};

struct Variable {
	string name;
	double value;
	Variable(string n, double v) :name(n), value(v) { }
}; // required for symbol table below. 

class Symbol_table {
	// Holds both the users variables, and a list of contant variables we program in. 
	vector<Variable> var_table;
	vector<Variable> const_table;

public:
	// Constructor
	Symbol_table() {
		// Constructor, holding some consts. 
		var_table = {};
		const_table = { Variable("k", 1000), Variable("pi", 3.14159) };
	}
	double get(string s);
	void set(string s, double ds);
	bool is_declared(string s);
	bool is_constant(string s);
	void declare(Variable v);

};

// Various consts to improve efficiency and clarity.
const char let = 'L';
const char quit = 'q'; 
const char print = ';';
const char number = '8'; // Kind of wierd that is an 8 but good symbol to represent all numbers I guess. 
const char name = 'a';
const char square_root = 'S';
const string prompt = "> ";
const string result = "= ";
const string declkey = "let";
const string root = "sqrt";
const string power = "pow";

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
	case ',':
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
	return Token(number, val); // Call the appropriate constructor to create a number token with a double val. 
	}
	default:
		// This handles all other cases, with specifics for the logic regarding a variable, example "let x = 2". 
		if (isalpha(ch)) { // Is the character an alphabet symbol. 
			string s;
			s += ch; // Begin filling a string with the characters. 
			// First char cannot start with an underscore, it will be found in the switch case above.
			// But ones we enter the while loop, underscores are okay. 
			// Underscore needs to be valid in order to allow for underscore_variables
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_')) s += ch; // While succesfully reading in a character ch, if its equal to an alphabet symbol or a digit, add it to the string s.
			cin.unget(); // Put the character which ended this string filling process (perhaps a ';' or '=' for example) back into the cin buffer.
			if (s == declkey) return Token(let); // If s is == "let" we are declaring a variable.
			if (s == root) return Token(square_root); // I will let 'S' represent a square root call.
			if (s == power) return Token('P'); // Let 'P' represent a call to pwr(x, i) function. 
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

bool Symbol_table::is_constant(string s)
{
	for (const Variable& v : const_table)
	{
		if (v.name == s) return true;
	}
	return false;
}

bool Symbol_table::is_declared(string s)
{
	for (const Variable& v : var_table)
	{
		if (v.name == s) return true;
	}
	return false;
}

double Symbol_table::get(string s)
{
	// Getters and setters for variables in the names vector.
	
	for (const Variable& v : var_table)
	{
		if (v.name == s) return v.value; 
	}
	// If its not a regular variable, maybe its a constant. 

	for (const Variable& v : const_table)
	{
		if (v.name == s) return v.value;
	}
	error("get: undefined name ", s);
}

void Symbol_table::set(string s, double d)
{	
	// Also needs to check for constants, function is_constant will be created above. 
	if (is_constant(s))
	{
		error("Cannot redefine a constant variable");
	}

	for (int i = 0; i < var_table.size(); ++i)
		if (var_table[i].name == s) {
			var_table[i].value = d;
			return;
		}
	error("set: undefined name ", s);
}

void Symbol_table::declare(Variable v)
{
	var_table.push_back(v);
}



Token_stream ts; // Token stream created here.
Symbol_table st; // Symbol table created here. 

double expression(); // Declarations to appease functions below. 
double statement();

double square(Token& t)
{	
	// Returns the square root of the given appropriate token.
	// Pre-Condition: A square root token followed by (expression)
	// Post-Condition: An appropriate double value (the square root.)

	t = ts.get(); // Must disregard '('
	if (t.kind != '(')  error("'(' expected"); // ts.get() will find most bad tokens but expressions like sqrt*2); are more subtle.
	double d = expression(); // Get the inner expression from sqrt(expression());
	t = ts.get(); // Have to disregard the outer ')' too; 
	if (t.kind != ')') error("'(' expected");
	if (d < 0)
	{
		error("Warning: negative square root detected. SWAT team deployed.\n");
	}
	else {
		return sqrt(d);
	}
}

double primary(); // just declaring to stop an error in pow() function below. Used on line 190.

double pow(Token& t)
{
	// Return x multiplied by itself i times.
	// Pre Condition: A token to be followed by the inner expression.
	// Post-Condition: An appropriate double value. 
	t = ts.get(); // Must disregard '('
	if (t.kind != '(')  error("'(' expected"); // ts.get() will find most bad tokens but expressions like sqrt*2); are more subtle.

	double x = expression(); // Get the inner expression, this will represent the x in pow(x,i); 
	double original = x; // Used to perform power operation. i.e 2*2*2 for 2^3. 

	t = ts.get(); // This should be a comma or the call to pow(x,i) is invalid, as the comma is what remains in the token stream in a valid call.
	if (t.kind != ',') error("Call must be in the form pow(x,i)");

	int i = narrow_cast<int>(primary());
	if (i < 0)
	{
		error("i must be >= 0\n");
	}

	t = ts.get();


	if (t.kind != ')') error("'(' expected");

	// Some magic numbers here, but I think we can disregard.
	// We know these represent the basic power properties. i.e 2^0 == 1 and 2^1 == 2. 
	if (i == 0)
	{
		return 1;
	}
	else if (i == 1)
	{
		return x;
	}
	else 
	{
		for (i; i > 1; --i)
		{
			x *= original;
		}
	}

	return x; 
}

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
		return primary();
	case number:
		return t.value;
	case name:
		return st.get(t.name);
	case square_root:
	{
		return square(t);
	}
	case 'P':
		// 'P' represents a call to the pow function. 
	{
		return pow(t);
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
	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of ", name); // Must match above syntax.
	double d = expression(); // Any valid expression is allowed in a declaration, but it be declared with some expression. No "let x;" allowed

	if (st.is_constant(name))
	{
		error("Redefinition of constant.");
	}
	else if (st.is_declared(name))
	{
		// If the value exists redeclare it.
		st.set(name, d);
		cout << "Redeclaration  of variable: " << name << "\n";
	}
	else
	{
		// If the value does not exists create a new Variable.
		st.declare(Variable(name, d));
	}
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