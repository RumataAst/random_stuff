#include <iostream>		// for std::cout
#include <stack>		// for stack
#include <exception>		// for exception

#define NUMBER '8'

class Token {
public:
	char	kind;					// what expression number, operator
	double	value;					// value if number
	

	Token(char k): kind{k}, value {0.0} {}		// constructor for operator
	Token(char k, double v): kind{k}, value{v} {}	// constructor for operands
};

Token get_token();	// read a token from cin
double primary();
double term();
double expression();

int	main(void) {
	try {
		while(std::cin)
			std::cout << expression() << '\n';
	}
	catch (std::exception &e) {
		std::cerr << e.what() << '\n';
		return 1;
	}
	catch (...) {
		std::cerr << "exception\n";
		return 2;
	}
	return 0;
}

Token get_token() {
	char	ch;


	std::cin >> ch;    // note that >> skips whitespace (space, newline, tab, etc.)
	switch (ch) {
	case '(': case ')': case '+': case '-': case '*': case '/': 
		return Token(ch);        // let each character represent itself
	case '.':
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	{
		std::cin.putback(ch);         // put digit back into the input stream
		double val;
		std::cin >> val;              // read a floating-point number
		return Token(NUMBER, val);
		}
	default:
	perror("Bad token");
	}
	return ('0', 0);
}

double expression() {
	double left = term();
	Token t = get_token();
	while (true) {
		switch(t.kind) {
		case '+':
			left+=term();
			t = get_token();
			break;
		case '-':
			left-=term();
			t = get_token();
			break;
		default:
			return left;
		}

	}
}

double term() {
	double left = primary();
	Token t = get_token();
	while (true) {
		switch(t.kind) {
		case '*':
			left*=primary();
			t = get_token();
			break;
		case '/':
			if (primary() != 0)
				t = get_token();
			else 
				perror("divide by zero");
			break;
		default:
			return left;
		}
	}
}

double primary() {
	Token t = get_token();
	switch(t.kind) {
	case '(':
	{	double d = expression();
		t = get_token();
		if (t.kind != ')')
			perror("')' expected");
		return d;
	}
	case NUMBER:
		return t.value;
	default:
		perror("primary expected");
	}
	return 0;
}
