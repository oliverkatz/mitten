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

/* File:    ExpressionParser.cpp
 * Author:  Oliver Katz
 * Version: 0.01-alpha
 * License: BSD 2-Clause
 * ========================================================================== *
 * Parses ASTs into ordered expression ASTs.
 */

/* Changelog:
 * ========================================================================= *
 * 0.01-alpha ------------------------------------------------ July 20, 2014 *
 * Initial release.
 */

#include "ExpressionParser.h"

using namespace std;

namespace mitten
{
	bool ExpressionParser::isSymbol(string s)
	{
		if (s.empty())
			return false;

		if (!isalpha(s[0]) && s[0] != '_')
			return false;

		return true;
	}

	bool ExpressionParser::isLiteral(string s)
	{
		if (s.empty())
		{
			return false;
		}
		else if (s[0] == '-')
		{
			return true;
		}
		else if (s[0] == '.')
		{
			return true;
		}
		else if (s[0] == '\"')
		{
			return true;
		}
		else if (s[0] == '\'')
		{
			return true;
		}
		else if (isdigit(s[0]))
		{
			return true;
		}
		else if (isalpha(s[0]))
		{
			if (s.back() == 'h')
			{
				for (int i = 1; i < s.size()-1; i++)
					if (!isdigit(s[i]) && ((s[i] < 'a' && s[i] > 'f') && (s[i] < 'A' && s[i] > 'F')))
						return false;

				return true;
			}
			else
			{
				return true;
			}
		}
		else
		{
			return false;
		}
	}

	void ExpressionParser::setExpressionBound(string b)
	{
		expressionBound = b;
	}

	void ExpressionParser::setExpressionElement(string e)
	{
		expressionElement = e;
	}

	void ExpressionParser::addUnaryLeftOperator(string o)
	{
		operators[o] = OperatorInfo(false, true, false);
	}

	void ExpressionParser::addUnaryRightOperator(string o)
	{
		operators[o] = OperatorInfo(false, false, true);
	}

	void ExpressionParser::addUnaryBothOperator(string o)
	{
		operators[o] = OperatorInfo(false, true, true);
	}

	void ExpressionParser::addBinaryOperator(string o)
	{
		operators[o] = OperatorInfo(true, false, false);
	}

	AST ExpressionParser::parse(AST ast, ErrorHandler &e)
	{
		if (ast.isLeaf())
			return ast;

		stack<AST> expressionStack;

		for (int i = 0; i < ast.size(); i++)
		{
			AST a = ast[i];
			if ((a.isBranch() && a.name().compare(expressionBound) == 0) || (a.isLeaf() && (isLiteral(a.leaf().value) || isSymbol(a.leaf().value))))
			{
				AST value;

				if (a.isBranch() && a.name().compare(expressionBound) == 0)
				{
					if (a.size() != 1)
					{
						//e.push_back(Error(a.rightmost().leaf(), "expected expression not argument list"));
					}
					else if (a[0].isBranch() && a[0].name().compare(expressionElement) == 0)
					{
						value = parse(a[0], e);
					}
					else
					{
						//e.push_back(Error(a.rightmost().leaf(), "expected expression"));
					}
				}
				else if (a.isLeaf() && isLiteral(a.leaf().value))
				{
					value = a;
				}
				else if (a.isLeaf() && isSymbol(a.leaf().value))
				{
					if (i != ast.size()-1 && (ast[i+1].isBranch() && ast[i+1].name().compare(expressionBound) == 0))
					{
						//value = AST::createNode()
					}
				}
			}
			else if (a.isLeaf() && operators.find(a.leaf().value) != operators.end())
			{

			}
			else
			{
				/*if (a.isLeaf())
					e.push_back(Error(a.leaf(), "unexpected token in expression"));
				else
					e.push_back(Error(a.rightmost().leaf(), "unexpected token in expression"));*/
			}
		}

		if (expressionStack.empty())
		{
			return AST();
		}
		else if (expressionStack.size() == 1)
		{
			if (expressionStack.top().isLeaf() && operators.find(expressionStack.top().leaf().value) != operators.end())
			{
				//e.push_back(Error(expressionStack.top().leaf(), "mismatched operators"));
			}
			else
			{
				return expressionStack.top();
			}
		}
		else
		{
			/*if (expressionStack.top().isLeaf())
				e.push_back(Error(expressionStack.top().leaf(), "mismatched expression"));
			else
				e.push_back(Error(expressionStack.top().rightmost().leaf(), "mismatched expression"));*/
		}
	}
}
