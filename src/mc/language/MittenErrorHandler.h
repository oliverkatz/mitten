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

#ifndef __MITTEN_LANGUAGE_MITTEN_ERROR_HANDLER_H
#define __MITTEN_LANGUAGE_MITTEN_ERROR_HANDLER_H

#include <iostream>
#include <string>
#include <vector>
#include <MPTK.h>

namespace mitten
{
	class MittenErrorHandler : public ErrorHandler
	{
	protected:
		std::string filePath;
		std::vector<std::string> fileBody;

		std::string errorPage;
		int errorCount;

		void append(Token source, std::string message);

	public:
		MittenErrorHandler() : errorCount(0) {}

		void setFilePath(std::string f);
		void setFileBody(std::string b);

		void mismatchedStructureBounds(Token source, std::string start, std::string end);
		void incompleteStructureBound(Token source, std::string start, std::string end);
		void unexpectedArgumentList(Token source);
		void expectedExpression(Token source);
		void operationRequiredLeftOperand(Token source);
		void unexpectedTokenInExpression(Token source);
		void cannotOperateOnAnOperator(Token source);

		void cannotNestBlockComments(Token source);
		void incompleteBlockComment(Token source);
		void insufficientDirectiveArguments(Token source);
		void unknownDirective(Token source);
		void macroAlreadyDefined(Token source);
		void useOfUndefinedMacro(Token source);

		void directiveCallRequiresArgumentList(Token source);

		void improperIncludeFormat(Token source);
		void includeRequiresArgumentList(Token source);
		void includeRequiresOneArgument(Token source);
		void includeRequiresModuleOrFileName(Token source);

		bool empty();
		bool dump();
		void clear();
	};
}

#endif