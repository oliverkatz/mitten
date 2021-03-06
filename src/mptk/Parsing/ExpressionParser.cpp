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
				return false;
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

	void ExpressionParser::setFunctionNode(string f)
	{
		functionNode = f;
	}

	void ExpressionParser::setOperationUnaryLeftNode(string o)
	{
		operationUnaryLeftNode = o;
	}

	void ExpressionParser::setOperationUnaryRightNode(string o)
	{
		operationUnaryRightNode = o;
	}

	void ExpressionParser::setOperationBinaryNode(string o)
	{
		operationBinaryNode = o;
	}

	void ExpressionParser::addUnaryLeftOperator(string o, int p)
	{
		if (p == -1)
			p = maxPrecedence++;
		operators[o] = OperatorInfo(true, true, false, p);
	}

	void ExpressionParser::addUnaryRightOperator(string o, int p)
	{
		if (p == -1)
			p = maxPrecedence++;
		operators[o] = OperatorInfo(true, false, true, p);
	}

	void ExpressionParser::addUnaryBothOperator(string o, int p)
	{
		if (p == -1)
			p = maxPrecedence++;
		operators[o] = OperatorInfo(true, true, true, p);
	}

	void ExpressionParser::addBinaryOperator(string o, int p)
	{
		if (p == -1)
			p = maxPrecedence++;
		operators[o] = OperatorInfo(false, false, false, p);
	}

	bool ExpressionParser::isExpression(AST a)
	{
		if (a.isBranch())
			return (a.name().compare(expressionBound) == 0);
		else
			return false;
	}

	bool ExpressionParser::isExpressionElement(AST a)
	{
		if (a.isBranch())
			return (a.name().compare(expressionElement) == 0);
		else
			return false;
	}

	bool ExpressionParser::isLiteral(AST a)
	{
		if (a.isLeaf())
			return isLiteral(a.leaf().value());
		else
			return false;
	}

	bool ExpressionParser::isSymbol(AST a)
	{
		if (a.isLeaf())
			return isSymbol(a.leaf().value());
		else
			return false;
	}

	bool ExpressionParser::isOperator(AST a)
	{
		if (a.isLeaf())
			return (operators.find(a.leaf().value()) != operators.end());
		else
			return false;
	}

	int ExpressionParser::getPrecedenceOfNode(AST a)
	{
		int ptmp = MITTEN_MAX_PRECEDENCE;
		if (a.isBranch())
		{
			if (a.name().compare(operationUnaryLeftNode) == 0)
			{
				ptmp = operators[a[1].leaf().value()].precedence;
			}
			else if (a.name().compare(operationUnaryRightNode) == 0)
			{
				ptmp = operators[a[0].leaf().value()].precedence;
			}
			else if (a.name().compare(operationBinaryNode) == 0)
			{
				ptmp = operators[a[1].leaf().value()].precedence;
			}
		}

		return ptmp;
	}

	AST ExpressionParser::parse(AST ast, ErrorHandler &e)
	{
		stack<AST> expressionStack;

		if (ast.isLeaf())
			return ast;

		for (int i = 0; i < ast.size(); i++)
		{
			AST a = ast[i];
			AST value;

			if (isExpression(a) || isLiteral(a) || isSymbol(a))
			{
				if (isExpression(a))
				{
					if (a.size() != 1)
					{
						e.unexpectedArgumentList(a.rightmost().leaf());
					}
					else if (isExpressionElement(a[0]))
					{
						value = parse(a[0], e);
					}
					else
					{
						e.expectedExpression(a.rightmost().leaf());
					}
				}
				else if (isLiteral(a))
				{
					value = a;
				}
				else if (isSymbol(a))
				{
					if (i != ast.size()-1 && isExpression(ast[i+1]))
					{
						value = AST::createNode(functionNode);
						value.append(a);

						for (int j = 0; j < ast[i+1].size(); j++)
						{
							value.append(parse(ast[i+1][j], e));
						}

						i++;
					}
					else
					{
						value = a;
					}
				}
				else if (isExpression(a))
				{
					value = a;
				}

				if (!expressionStack.empty() && isOperator(expressionStack.top()))
				{
					string o = expressionStack.top().leaf().value();
					AST oast = expressionStack.top();

					if (operators[o].unary == false)
					{
						expressionStack.pop();

						if (expressionStack.empty())
						{
							e.operationRequiredLeftOperand(oast.leaf());
						}
						else if (isExpression(expressionStack.top()))
						{
							e.operationRequiredLeftOperand(oast.leaf());
						}
						else
						{
							AST lvalue = expressionStack.top();
							expressionStack.pop();

							int ptmp = getPrecedenceOfNode(lvalue);

							if (operators[o].precedence > ptmp)
							{
								AST tmp = AST::createNode(operationBinaryNode);
								tmp.append(lvalue.rightmost());
								tmp.append(oast);
								tmp.append(value);
								lvalue.rightmost() = tmp;
								expressionStack.push(lvalue);
							}
							else
							{
								AST tmp = AST::createNode(operationBinaryNode);
								tmp.append(lvalue);
								tmp.append(oast);
								tmp.append(value);
								expressionStack.push(tmp);
							}
						}
					}
					else if (operators[o].rightAssociative)
					{
						expressionStack.pop();
						AST tmp = AST::createNode(operationUnaryRightNode);
						tmp.append(oast);
						tmp.append(value);
						expressionStack.push(tmp);
					}
				}
				else
				{
					expressionStack.push(value);
				}
			}
			else if (isOperator(a))
			{
				if (!operators[a.leaf().value()].unary)
				{
					expressionStack.push(a);
				}
				else
				{
					if (operators[a.leaf().value()].leftAssociative && operators[a.leaf().value()].rightAssociative)
					{
						if (expressionStack.empty() || (!expressionStack.empty() && isExpression(expressionStack.top())))
						{
							value = expressionStack.top();
							expressionStack.pop();

							int ptmp = getPrecedenceOfNode(value);

							if (operators[a.leaf().value()].precedence > ptmp)
							{
								AST tmp = AST::createNode(operationUnaryLeftNode);
								tmp.append(value.rightmost());
								tmp.append(a);
								value.rightmost() = tmp;
								expressionStack.push(value);
							}
							else
							{
								AST tmp = AST::createNode(operationUnaryLeftNode);
								tmp.append(value);
								tmp.append(a);
								expressionStack.push(tmp);
							}
						}
					}
					else if (operators[a.leaf().value()].leftAssociative && !operators[a.leaf().value()].rightAssociative)
					{
						if (!expressionStack.empty() && (isOperator(expressionStack.top())))
						{
							value = expressionStack.top();
							expressionStack.pop();

							int ptmp = getPrecedenceOfNode(value);

							if (operators[a.leaf().value()].precedence > ptmp)
							{
								AST tmp = AST::createNode(operationUnaryLeftNode);
								tmp.append(value.rightmost());
								tmp.append(a);
								value.rightmost() = tmp;
								expressionStack.push(value);
							}
							else
							{
								AST tmp = AST::createNode(operationUnaryLeftNode);
								tmp.append(value);
								tmp.append(a);
								expressionStack.push(tmp);
							}
						}
					}
					else if (operators[a.leaf().value()].rightAssociative)
					{
						expressionStack.push(a);
					}
				}
			}
			else
			{
				e.unexpectedTokenInExpression(a.rightmost().leaf());
			}
		}

		if (expressionStack.empty())
		{
			return AST();
		}
		else if (expressionStack.size() == 1)
		{
			if (isOperator(expressionStack.top()))
			{
				e.cannotOperateOnAnOperator(expressionStack.top().leaf());
			}
			else
			{
				return expressionStack.top();
			}
		}
		else
		{
			e.unexpectedArgumentList(expressionStack.top().rightmost().leaf());
		}

		return AST();
	}
}
