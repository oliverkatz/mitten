/******************************************************************************
 *                                 _ _   _                                    *
 *                           /\/\ (_) |_| |_ ___ _ __                         *
 *                          /    \| | __| __/ _ \ '_ \                        *
 *                         / /\/\ \ | |_| ||  __/ | | |                       *
 *                         \/    \/_|\__|\__\___|_| |_|                       *
 *                                                                            *
 ******************************************************************************/

/*
 * Copyright (c) 2014, Oliver Katz
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, 
 * this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice, 
 * this list of conditions and the following disclaimer in the documentation 
 * and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <iostream>
#include <MUnit.h>

#include "../Core/Token.h"
#include "../Core/Reconstruction.h"
#include "../Lexing/Lexer.h"

using namespace std;
using namespace mitten;

int ntoks = 0;

void myOnToken(Token t, vector<Token> &v, ErrorHandler &e)
{
	ntoks++;
}

int main()
{
	Test test = Test("LexerTest");

	Lexer lexer;
	try
	{
		lexer.deliminate("");
	}
	catch(runtime_error &e)
	{
		test.assert("deliminating empty string safety");
	}

	lexer.deliminate("(");
	lexer.deliminate(")");
	lexer.deliminate(",");

	lexer.deliminate("{");
	lexer.deliminate("}");
	lexer.deliminate(";");

	lexer.deliminate(" ") = Filtered;
	lexer.deliminate("\t") = Filtered;
	lexer.deliminate("\n") = Filtered;

	lexer.deliminate("\"", "\"");

	string page = "include(std);\n\nvoid main()\n{\n\tprint(\"hello, world\\n\");\n}\n\n";

	InternalErrorHandler eh;
	vector<Token> toks = lexer.lex(page, "--", eh);

	test.assert(reconstructFromTokenVector(toks).compare(page) == 0);

	vector<Token> avalue = {
		Token("5")
	};
	lexer.defineMacro("A", avalue);

	page = "A;\n";
	toks = lexer.lex(page, "--", eh);

	test.assert(toks.size() == 3);
	test.assert(toks[0].value().compare("5") == 0);

	vector<Token> avalue2 = {
	};
	lexer.defineMacro("A", avalue2);

	toks = lexer.lex(page, "--", eh);

	test.assert(toks.size() == 2);

	vector<Token> avalue3 = {
		Token("5"),
		Token("+"),
		Token("2")
	};
	lexer.defineMacro("A", avalue3);

	toks = lexer.lex(page, "--", eh);

	test.assert(toks.size() == 5);

	lexer.onToken = myOnToken;
	toks = lexer.lex(page, "--", eh);
	test.assert(ntoks == 5);

	return (int)(test.write());
}