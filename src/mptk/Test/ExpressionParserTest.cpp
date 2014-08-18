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
#include "../Parsing/ExpressionParser.h"

using namespace std;
using namespace mitten;

int main()
{
	Test test = Test("ExpressionParserTest");

	Lexer lexer;
	lexer.deliminate("(");
	lexer.deliminate(")");
	lexer.deliminate(",");

	lexer.deliminate(" ") = Filtered;
	lexer.deliminate("\t") = Filtered;
	lexer.deliminate("\n") = Filtered;

	lexer.deliminate("*");
	lexer.deliminate("+");

	StructureParser sp;
	sp.bind("expression", "(", ")", "argument", ",");

	InternalErrorHandler eh;

	AST expr0 = sp.parse(lexer.lex("2*(3+1)+4", "--", eh), eh);

	test.assert(!eh.dump());

	ExpressionParser ep;

	ep.setExpressionBound("expression");
	ep.setExpressionElement("argument");
	ep.setFunctionNode("fcall");
	ep.setOperationUnaryLeftNode("op_u_l");
	ep.setOperationUnaryRightNode("op_u_r");
	ep.setOperationBinaryNode("op_b");
	ep.addBinaryOperator("+");
	ep.addBinaryOperator("*");

	AST ast = ep.parse(expr0, eh);

	test.assert(!eh.dump());

	eh.clear();
	AST expr1 = sp.parse(lexer.lex("3+f(5)", "--", eh), eh);
	test.assert(!eh.dump());
	ast = ep.parse(expr1, eh);
	test.assert(!eh.dump());

	eh.clear();
	AST expr2 = sp.parse(lexer.lex("f(5)+3", "--", eh), eh);
	test.assert(!eh.dump());
	ast = ep.parse(expr2, eh);
	test.assert(!eh.dump());

	return (int)(test.write());
}
