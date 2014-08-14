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

#ifndef __MITTEN_EXPRESSION_PARSER_H
#define __MITTEN_EXPRESSION_PARSER_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stdexcept>

#include <limits.h>

#include "../Core/Token.h"
#include "../Core/AST.h"
#include "../Core/ASTBuilder.h"
#include "../Core/ErrorHandler.h"

#define MITTEN_MAX_PRECEDENCE INT_MAX

namespace mitten
{
	/*! \brief Parser to convert expression ASTs into a more pragmatic form.
	 * Re-orders expression ASTs resulting from the StructureParser into an organization which makes it easy to handle expressions.
	 */
	class ExpressionParser
	{
	protected:
		/*! \brief Declares the configuration of an operator.
		 */
		typedef struct OperatorInfo
		{
			bool unary; //! Set tp true for unary, false for binary.
			bool leftAssociative; //! Set to true if unary operator is left associative (note that it can be both left and right associative).
			bool rightAssociative; //! Set to true if unary operator is right associative (note that it can be both left and right associative).
			int precedence; //! Precedence (larger numbers are higher precedence).

			/*! \brief Constructor.
			 * Initializes empty operator declaration.
			 */
			OperatorInfo() : unary(true), leftAssociative(false), rightAssociative(false) {}

			/*! \brief Constructor.
			 * Initializes full operator declaration.
			 * \param u True for unary, false for binary.
			 * \param l True for left associative.
			 * \param r True for right associative.
			 * \param p Precedence.
			 */
			OperatorInfo(bool u, bool l, bool r, int p) : unary(u), leftAssociative(l), rightAssociative(r), precedence(p) {}
		} OperatorInfo;

		int maxPrecedence; //! Highest precedence used so far.

		std::string expressionBound; //! AST node name for expressions.
		std::string expressionElement; //! AST node name for expression elements (i.e. arguments).
		std::string functionNode; //! AST node name for function calls.
		std::string operationUnaryLeftNode; //! AST node name for unary left operations.
		std::string operationUnaryRightNode; //! AST node name for unary right operations.
		std::string operationBinaryNode; //! AST node name for binary operations.
		std::unordered_map<std::string, OperatorInfo> operators; //! Dictionary of operator declarations.

		/*! \brief Detects if a string is a symbol.
		 * \todo Replace this with token tags.
		 */
		virtual bool isSymbol(std::string s);

		/*! \brief Detects if a string is a literal.
		 * \todo Replace this with token tags.
		 */
		virtual bool isLiteral(std::string s);

	public:
		/*! \brief Constructor.
		 * Initializes empty expression parser. */
		ExpressionParser() : maxPrecedence(0) {}

		/*! \brief Sets the expression AST node name.
		 */
		void setExpressionBound(std::string b);

		/*! \brief Sets the expression element AST node name.
		 */
		void setExpressionElement(std::string e);

		/*! \brief Sets the function call AST node name.
		 */
		void setFunctionNode(std::string f);

		/*! \brief Sets the unary left operation AST node name.
		 */
		void setOperationUnaryLeftNode(std::string o);

		/*! \brief Sets the unary right operation AST node name.
		 */
		void setOperationUnaryRightNode(std::string o);

		/*! \brief Sets the binary operation AST node name.
		 */
		void setOperationBinaryNode(std::string o);

		/*! \brief Adds the declaration of a unary left operator.
		 * \param o Operator symbol.
		 * \param p Precedence (-1 for automatically increasing sequentially).
		 */
		void addUnaryLeftOperator(std::string o, int p = -1);

		/*! \brief Adds the declaration of a unary right operator.
		 * \param o Operator symbol.
		 * \param p Precedence (-1 for automatically increasing sequentially).
		 */
		void addUnaryRightOperator(std::string o, int p = -1);

		/*! \brief Adds the declaration of a unary left and right operator.
		 * \param o Operator symbol.
		 * \param p Precedence (-1 for automatically increasing sequentially).
		 */
		void addUnaryBothOperator(std::string o, int p = -1);

		/*! \brief Adds the declaration of a binary operator.
		 * \param o Operator symbol.
		 * \param p Precedence (-1 for automatically increasing sequentially).
		 */
		void addBinaryOperator(std::string o, int p = -1);

		/*! \brief Runs the parser.
		 * \param ast Input AST containing only an expression.
		 * \oaram e The error handler to be used for storing errors.
		 */
		AST parse(AST ast, ErrorHandler &e);
	};
}

#endif