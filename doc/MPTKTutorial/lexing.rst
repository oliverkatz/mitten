Lexical Analysis
================

Let's start by lexing the following string::

	"f(x+2, 5)"

We can build from the following program::

	#include <iostream>
	#include <string>

	using namespace std;

	#include <MPTK.h>

	using namespace mitten;

	void main()
	{
		// the string we want to lex:
		string source = "f(x+2, 5)";

		// our program goes here
	}

Let us start our modification by creating a **Lexer** object, which will handle the lexical analysis::

	Lexer l;

Deliminators
------------
Deliminators are what we split the string by. They mark the end of a token. For parsing english sentences, the deliminators would be punctuation and spaces. For parsing our source string, the following deliminators should be used::

	"(",
	")",
	"+",
	",",
	" "

For a complete programming language, we might want more. However, this is plenty for our example. Once you can lex a simple string, extending the deliminator set is quite simple.

Adding these deliminators to our **Lexer** object can be done as follows::

	l.deliminate("(");
	l.deliminate(")");
	l.deliminate("+");
	l.deliminate(",");
	l.deliminate(" ");

Now, **l** knows which text to look for to split **source** by. 

Example Tokenization
--------------------

To actually lex the string, we can use the following method::

	l.lex(source, "test.n");

The result of the this method is a *std::vector* of **Token** objects, as follows::

	vector<Token> toks = l.lex(source);

The **Token** class contains some information about each token, but for the purposes of printing out the tokens of the source code, we only need to use the *value* member::

	for (auto i : toks)
		cout << "'" << i.value << "' ";
	cout << "\n";

The final program is::

	#include <iostream>
	#include <string>

	using namespace std;

	#include <MPTK.h>

	using namespace mitten;

	void main()
	{
		// the string we want to lex:
		string source = "f(x+2, 5)";

		// define the lexical analyzer
		Lexer l;

		// configure the lexical analyzer
		l.deliminate("(");
		l.deliminate(")");
		l.deliminate("+");
		l.deliminate(",");
		l.deliminate(" ");

		// lex the source program
		vector<Token> toks = l.lex(source, "test.n");

		// print out the results
		for (auto i : toks)
			cout << "'" << i.value << "' ";
		cout << "\n";
	}

Now if we save this file as *LexSomething.cpp*, we can build and run it with the following::

	$ g++ LexSomething.cpp -o LexSomething -lMPTK
	$ ./LexSomething
	'f' '(' 'x' '+' '2' ',' ' ' '5' ')'

Neat, right? There's a couple more tweaks we can do to take full advantage of the MPTK Lexer.

Filtering
---------

We can tell certain deliminators to not show up in the token vector::

	l.deliminate(" ") = Filtered;

The deliminate method returns a reference to the deliminator's flag variable. *Filtered* is one of the flags you can apply to the deliminator. Now, when we re-build and run the program we get a different result::

	$ ./LexSomething
	'f' '(' 'x' '+' '2' ',' '5' ')'

This is a little cleaner and easier to work with, especially for C-like languages.

Tags
----

MPTK automatically tags tokens with certain attributes. These attributes can be retrieved with the **Token** class's **tag** member. The tag enumerator can have the following values:

- **DeliminatorTag** - All deliminators are of this tag.
- **SymbolTag** - All C symbols are of this tag (configurable via *Lexer::symbolTag*).
- **BooleanLiteralTag** - C++ bool literals are of this tag (configurable via *Lexer::boolTag*).
- **IntegerLiteralTag** - C int literals are of this tag (configurable via *Lexer::intTag*).
- **FloatingLiteralTag** - C float literals are of this tag (configurable via *Lexer::floatTag*).
- **CharacterLiteralTag** - C char literals are of this tag (configurable via *Lexer::charTag*).
- **StringLiteralTag** - C string literals are of this tag (configurable via *Lexer::stringTag*).

This can allow you to identify which category a token might belong to without re-parsing the token. Tagging may be performed with little extra work on MPTK's part (CPU-wise). 

Using Tokens
------------

You can see the **Token** class's **value** and **tag** members above. The only other two members of a token that you can access are the **line** and **column** members. These store the line number (starting from 1) and column number (starting from 0) of the first character of the token. This is useful for error handling, especially later. ::

	// create a token "hi" on line 5, column 8 of file "test.n" with the deliminator tag.
	Token t = Token("hi", "test.n", 5, 8, DeliminatorTag);

	cout << t.value() << "\n";
	cout << t.line() << ":" << t.column() << "\n";
	if (t.tag() == DeliminatorTag)
		cout << "is a deliminator";
	cout << " in file " << t.file() << "\n";

This code will print the following result: ::

	hi
	5:8
	is a deliminator in file test.n


Extending the Lexer
-------------------

There are two ways we can extend the lexer. First, we can write our own method of pattern detection to detect the start point and length of deliminator tokens. What if we have a deliminator that always starts with "#", but has a variable length; if "#{" occurs before the first newline, its end point is the first instance of "#}", but otherwise its end point is the first newline. To perform this detection, we need to use a custom patterned deliminator. ::

	l.deliminate("#", customPattern);

Where *customPattern* is a callback function. Let's go through how it works. ::

	int customPattern(int from, string s)
	{
		// code goes here
	}

*s* is the string containing the text we are parsing. The start point of the deliminator is *from*. The function should return the proper length of the deliminator. To implement the logic above, we can write the following code: ::

	int customPattern(int from, std::string s)
	{
		bool multi = false;

		for (int i = from; i < s.size(); i++)
		{
			if (s[i] == '\n')
			{
				if (!multi)
				{
					return i-from+1;
				}
			}
			else if (s[i] == '#' && (i < s.size()-1 && s[i+1] == '{'))
			{
				multi = true;
			}
			else if (s[i] == '#' && (i < s.size()-1 && s[i+1] == '}'))
			{
				if (multi)
				{
					return i-from+2;
				}
			}
		}

		return s.size()-from;
	}

Now, if we call the lexer, we get the proper result which we could not have gotten with the built in deliminator pattern detection.

Another way to extend the lexer is to create your own lexer class. This is useful, in particular, to overload the *onToken* method which is called every time a token is lexed. ::

	class MyLexer : public Lexer
	{
	protected:
		void onToken(Token t, vector<Token> &v)
	};

	void MyLexer::onToken(Token t, vector<Token> &v)
	{
		// here is how the default behavior is implemented
		v.push_back(t);
	}

The default behavior of *onToken* is simply to append the token to the result vector, but you could use this method to implement a lot of useful features (i.e. a preprocessor).
