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

/* File:    ExpressionParser.h
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

#ifndef __MITTEN_EXPRESSION_PARSER_H
#define __MITTEN_EXPRESSION_PARSER_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stdexcept>

#include "Token.h"
#include "AST.h"
#include "ASTBuilder.h"
#include "ErrorHandler.h"

namespace mitten
{
	class ExpressionParser
	{
	protected:
		typedef struct OperatorInfo
		{
			bool unary;
			bool leftAssociative, rightAssociative;
			int precedence;

			OperatorInfo() : unary(true), leftAssociative(false), rightAssociative(false) {}
			OperatorInfo(bool u, bool l, bool r, int p) : unary(u), leftAssociative(l), rightAssociative(r), precedence(p) {}
		} OperatorInfo;

		int maxPrecedence;

		std::string expressionBound, expressionElement;
		std::string functionNode;
		std::string operationUnaryLeftNode, operationUnaryRightNode, operationBinaryNode;
		std::unordered_map<std::string, OperatorInfo> operators;

		virtual bool isSymbol(std::string s);
		virtual bool isLiteral(std::string s);

	public:
		ExpressionParser() : maxPrecedence(0) {}

		void setExpressionBound(std::string b);
		void setExpressionElement(std::string e);
		void setFunctionNode(std::string f);
		void setOperationUnaryLeftNode(std::string o);
		void setOperationUnaryRightNode(std::string o);
		void setOperationBinaryNode(std::string o);

		void addUnaryLeftOperator(std::string o, int p = -1);
		void addUnaryRightOperator(std::string o, int p = -1);
		void addUnaryBothOperator(std::string o, int p = -1);
		void addBinaryOperator(std::string o, int p = -1);

		AST parse(AST ast, ErrorHandler &e);
	};
}

#endif