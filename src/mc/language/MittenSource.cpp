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

#include "MittenSource.h"

using namespace std;

namespace mitten
{
	MittenSource::MittenSource()
	{
		lexer.deliminate(" ") = Filtered;
		lexer.deliminate("\t") = Filtered;
		lexer.deliminate("\n") = Filtered;
		lexer.deliminate("(");
		lexer.deliminate(")");
		lexer.deliminate(",");
		lexer.deliminate("{");
		lexer.deliminate("}");
		lexer.deliminate(";");
		lexer.deliminate("[");
		lexer.deliminate("]");
		lexer.deliminate("\"", "\"");
		lexer.deliminate("'", "'");
		lexer.deliminate("\"\"\"", "\"\"\"");
		lexer.deliminate("//", "\n") = Filtered;
		lexer.deliminate("/*", "*/") = Filtered;
		lexer.deliminate("+");
		lexer.deliminate("-");
		lexer.deliminate("*");
		lexer.deliminate("/");
		lexer.deliminate("%");
		lexer.deliminate("&");
		lexer.deliminate("|");
		lexer.deliminate("^");
		lexer.deliminate("<<");
		lexer.deliminate(">>");
		lexer.deliminate("~");
		lexer.deliminate("&&");
		lexer.deliminate("||");
		lexer.deliminate("^^");
		lexer.deliminate("!");
		lexer.deliminate("=");
		lexer.deliminate("+=");
		lexer.deliminate("-=");
		lexer.deliminate("*=");
		lexer.deliminate("/=");
		lexer.deliminate("%=");
		lexer.deliminate("&=");
		lexer.deliminate("|=");
		lexer.deliminate("^=");
		lexer.deliminate("<<=");
		lexer.deliminate(">>=");
		lexer.deliminate("~=");
		lexer.deliminate("==");
		lexer.deliminate("!=");
		lexer.deliminate("<");
		lexer.deliminate("<=");
		lexer.deliminate(">");
		lexer.deliminate(">=");
		lexer.deliminate(":");

		structureParser.setGlobalBoundName("global");
		structureParser.setGlobalSplit("line", ";");
		structureParser.bind("expression", "(", ")", "argument", ",");
		structureParser.bind("scope", "{", "}", "line", ";");
		structureParser.onNode = onNode;
	}

	MittenSource MittenSource::fromString(string s)
	{
		MittenSource rtn;
		rtn.path = "--";
		rtn.body = s;
		return rtn;
	}

	MittenSource MittenSource::fromFile(string p)
	{
		MittenSource rtn;
		rtn.path = p;
		rtn.body = readFile8(p);
		return rtn;
	}

	void MittenSource::onNode(AST &a, ASTBuilder &b, ErrorHandler &e, StructureParser &p)
	{
		MittenErrorHandler &meh = dynamic_cast<MittenErrorHandler &>(e);

		if (a.isBranch() && a.name().compare("line") == 0)
		{
			cout << "LINE: " << a.display() << "\n";

			if (a.size() == 2)
			{
				if (a[0].isLeaf() && a[0].leaf().value().compare("include") == 0)
				{
					if (a[1].isBranch())
					{
						if (a[1].size() == 1)
						{
							if (a[1][0].size() == 1)
							{
								if (a[1][0][0].isLeaf())
								{
									Token inc = a[1][0][0].leaf();
									if (inc.tag() == SymbolTag)
										cout << "INCLUDE MODULE '" << inc.value() << "'\n";
									else if (inc.tag() == StringLiteralTag)
										cout << "INCLUDE FILE '" << inc.value() << "'\n";
									else
										meh.includeRequiresModuleOrFileName(a[0].leaf());
								}
								else
								{
									meh.includeRequiresModuleOrFileName(a[0].leaf());
								}
							}
							else
							{
								meh.includeRequiresOneArgument(a[0].leaf());
							}
						}
						else
						{
							meh.includeRequiresOneArgument(a[0].leaf());
						}
					}
					else
					{
						meh.includeRequiresArgumentList(a[0].leaf());
					}
				}
			}
		}
	}

	AST MittenSource::parse()
	{
		vector<Token> toks = lexer.lex(body, path, meh);
		return structureParser.parse(toks, meh);
	}

	bool MittenSource::compileFromAST(AST a)
	{
		cout << a.display() << "\n";

		return meh.dump();
	}

	bool MittenSource::compile()
	{
		compileFromAST(parse());
	}
}
