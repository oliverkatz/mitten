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

#ifndef __MITTEN_ERROR_HANDLER_H
#define __MITTEN_ERROR_HANDLER_H

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <sstream>

#include "Token.h"

namespace mitten
{
	/*! \brief Stores error messages and prints them out at the end.
	 * This is just an abstract base class. If you want to actually use errors in MPTK, you will have to either implement a subclass of the ErrorHandler base class or use MPTK's InternalErrorHandler.
	 */
	class ErrorHandler
	{
	public:
		/*! \brief Error for mismatched structure bounds.
		 * \param start Start bound used.
		 * \param end End bound used.
		 */
		virtual void mismatchedStructureBounds(Token source, std::string start, std::string end) =0;

		/*! \brief Error for incomplete structure bounds.
		 * \param start Start bound used.
		 * \param end End bound used.
		 */
		virtual void incompleteStructureBound(Token source, std::string start, std::string end) =0;

		/*! \brief Error for unexpected argument list while parsing ASTs.
		 */
		virtual void unexpectedArgumentList(Token source) =0;

		/*! \brief Error for unexpected expression while parsing ASTs.
		 */
		virtual void expectedExpression(Token source) =0;

		/*! \brief Error for required left operands for operators.
		 */
		virtual void operationRequiredLeftOperand(Token source) =0;

		/*! \brief Error for unexpected tokens in expressions while parsing ASTs.
		 */
		virtual void unexpectedTokenInExpression(Token source) =0;

		/*! \brief Error for the inability to operate on operators.
		 */
		virtual void cannotOperateOnAnOperator(Token source) =0;
		
		/*! \brief Error for the re-definition of an existing macro.
		 */
		virtual void macroShadowsExistingDefinition(Token source) =0;
		
		/*! \brief Error for the use of an undefined macro.
		 */
		virtual void useOfUndefinedMacro(Token source) =0;
	};

	/*! \brief Implementation of the ErrorHandler base class.
	 */
	class InternalErrorHandler : public ErrorHandler
	{
	protected:
		std::string filename; //! The filename of the file that was parsed.
		std::vector<std::string> filebody; //! The body of the file that was parsed, split by lines.
		std::string page; //! The string containing all the error messages.
		int count; //! The number of errors produced.

		/* \brief Helper method.
		 * Appends an error message.
		 * \param source Source token.
		 * \param message Error message.
		 */
		virtual void append(Token source, std::string message);

	public:
		/*! \brief Constructor.
		 * Initializes an empty internal error handler. 
		 */
		InternalErrorHandler() : count(0) {}

		/*! \brief Sets the file name.
		 * Required for file name printing.
		 */
		void setFileName(std::string f);

		/*! \brief Sets the file body.
		 * Also splits it up by lines.
		 */
		void setFileBody(std::string b);

		/*! \brief Implemented method.
		 * See the ErrorHandler base class.
		 */
		virtual void mismatchedStructureBounds(Token source, std::string start, std::string end);

		/*! \brief Implemented method.
		 * See the ErrorHandler base class.
		 */
		virtual void incompleteStructureBound(Token source, std::string start, std::string end);

		/*! \brief Implemented method.
		 * See the ErrorHandler base class.
		 */
		virtual void unexpectedArgumentList(Token source);

		/*! \brief Implemented method.
		 * See the ErrorHandler base class.
		 */
		virtual void expectedExpression(Token source);

		/*! \brief Implemented method.
		 * See the ErrorHandler base class.
		 */
		virtual void operationRequiredLeftOperand(Token source);

		/*! \brief Implemented method.
		 * See the ErrorHandler base class.
		 */
		virtual void unexpectedTokenInExpression(Token source);

		/*! \brief Implemented method.
		 * See the ErrorHandler base class.
		 */
		virtual void cannotOperateOnAnOperator(Token source);
		
		/*! \brief Implemented method.
		 * See the ErrorHandler base class.
		 */
		virtual void macroShadowsExistingDefinition(Token source);
		
		/*! \brief Implemented method.
		 * See the ErrorHandler base class.
		 */
		virtual void useOfUndefinedMacro(Token source);

		/*! \brief Checks if there are no errors.
		 * \returns True only if there are no errors.
		 */
		bool empty();

		/* \brief Displays all the errors to the console.
		 * Uses stderr to print them.
		 * \returns True only if errors were printed, false otherwise.
		 */
		bool dump();

		/*! \brief Clears all errors.
		 */
		void clear();
	};
}

#endif
