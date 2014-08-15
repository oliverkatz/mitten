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
#include "../Core/AST.h"
#include "../Lexing/Lexer.h"
#include "../Parsing/StructureParser.h"

using namespace std;
using namespace mitten;

int nmacro = 0;

void myOnNode(AST &a, ASTBuilder &b, ErrorHandler &eh, StructureParser &p)
{
	if (a.isLeaf() && p.isMacroDefined(a.leaf().value()))
	{
		a = p.getMacroValue(a.leaf().value());
		nmacro++;
	}
}

int main()
{
	Test test = Test("StructureParserTest");

	string page = "include(std);\n\nvoid main()\n{\n\tprint(\"hello, world\\n\");\n}\n\n";
	Lexer lexer;
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

	InternalErrorHandler eh;

	vector<Token> toks = lexer.lex(page, "--", eh);

	StructureParser parser;

	parser.bind("expression", "(", ")", "argument", ",");
	parser.bind("scope", "{", "}", "line", ";");

	AST ast = parser.parse(toks, eh);

	test.assert(eh.empty());

	vector<Token> toks2 = {
		Token("A")
	};

	ast = parser.parse(toks2, eh);

	test.assert(ast.isBranch());
	test.assert(ast.size() == 1);
	test.assert(ast[0].isLeaf());
	test.assert(ast[0].leaf().value().compare("A") == 0);

	parser.onNode = myOnNode;
	parser.defineMacro("A", AST::createLeaf(Token("5")));

	ast = parser.parse(toks2, eh);

	test.assert(ast.isBranch());
	test.assert(ast.size() == 1);
	test.assert(ast[0].isLeaf());
	test.assert(ast[0].leaf().value().compare("5") == 0);
	test.assert(nmacro == 1);

	return (int)(test.write());
}
