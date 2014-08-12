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

#include "MittenErrorHandler.h"

using namespace std;

namespace mitten
{
	void MittenErrorHandler::append(Token source, string message)
	{
		if (!filePath.empty())
			errorPage += filePath+":";

		errorPage += to_string(source.line())+":"+to_string(source.column())+" - "+message+"\n";
		errorPage += "    from '"+source.value()+"'\n";

		if (!fileBody.empty())
		{
			errorPage += fileBody[source.line()-1]+"\n";
			errorPage += string(source.column(), ' ')+"^\n";
		}

		errorPage += "\n";
		errorCount++;
	}

	void MittenErrorHandler::setFilePath(string f)
	{
		filePath = f;
	}

	void MittenErrorHandler::setFileBody(string b)
	{
		istringstream ss(b);

		while (!ss.eof())
		{
			string tmp;
			getline(ss, tmp);
			fileBody.push_back(tmp);
		}
	}

	void MittenErrorHandler::mismatchedStructureBounds(Token source, std::string start, std::string end)
	{
		append(source, "mismatched structure bounds between '"+start+"' and '"+end+"'");
	}

	void MittenErrorHandler::incompleteStructureBound(Token source, std::string start, std::string end)
	{
		append(source, "incomplete structure bound started with '"+start+"', but not completed with '"+end+"'");
	}

	void MittenErrorHandler::unexpectedArgumentList(Token source)
	{
		append(source, "unexpected argument list - only one element required");
	}

	void MittenErrorHandler::expectedExpression(Token source)
	{
		append(source, "expected expression here");
	}

	void MittenErrorHandler::operationRequiredLeftOperand(Token source)
	{
		append(source, "operator '"+source.value()+"' requires left operand");
	}

	void MittenErrorHandler::unexpectedTokenInExpression(Token source)
	{
		append(source, "unexpected token '"+source.value()+"' in expression");
	}

	void MittenErrorHandler::cannotOperateOnAnOperator(Token source)
	{
		append(source, "cannot operate on an operator");
	}

	void MittenErrorHandler::cannotNestBlockComments(Token source)
	{
		append(source, "cannot nest block comments");
	}

	void MittenErrorHandler::incompleteBlockComment(Token source)
	{
		append(source, "incomplete block comment");
	}

	void MittenErrorHandler::insufficientDirectiveArguments(Token source)
	{
		append(source, "preprocessor directive expects more arguments");
	}

	void MittenErrorHandler::unknownDirective(Token source)
	{
		append(source, "unknown preprocessor directive");
	}

	void MittenErrorHandler::macroAlreadyDefined(Token source)
	{
		append(source, "macro already defined");
	}

	void MittenErrorHandler::useOfUndefinedMacro(Token source)
	{
		append(source, "use of undefind macro");
	}

	bool MittenErrorHandler::empty()
	{
		return (errorCount == 0);
	}

	bool MittenErrorHandler::dump()
	{
		if (errorCount == 0)
		{
			return false;
		}
		else
		{
			cerr << errorPage;
			if (errorCount == 1)
				cerr << "1 error in " << filePath << ".\n";
			else
				cerr << errorCount << " errors in " << filePath << ".\n";
			return true;
		}
	}

	void MittenErrorHandler::clear()
	{
		errorPage = "";
		errorCount = 0;
	}
}
