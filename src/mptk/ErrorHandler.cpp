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

/* File:    Error.cpp
 * Author:  Oliver Katz
 * Version: 0.01-alpha
 * License: BSD 2-Clause
 * ========================================================================== *
 * Errors are stored in this class.
 */

/* Changelog:
 * ========================================================================= *
 * 0.01-alpha ------------------------------------------------ July 20, 2014 *
 * Initial release.
 */

#include "ErrorHandler.h"

using namespace std;

namespace mitten
{
	void InternalErrorHandler::append(Token source, string message)
	{
		if (!filename.empty())
			page += filename+":";

		page += to_string(source.line)+":"+to_string(source.column)+" - "+message+"\n";
		page += "    from '"+source.value+"'\n";

		if (!filebody.empty())
		{
			page += filebody[source.line-1]+"\n";
			page += string(source.column, ' ')+"^\n";
		}

		page += "\n";
		count++;
	}

	void InternalErrorHandler::setFileName(string f)
	{
		if (f.find("/") != string::npos)
		{
			filename = f.substr(f.rfind("/")+1);
		}
		else
		{
			filename = f;
		}
	}

	void InternalErrorHandler::setFileBody(string b)
	{
		istringstream ss(b);

		while (!ss.eof())
		{
			string tmp;
			getline(ss, tmp);
			filebody.push_back(tmp);
		}
	}

	void InternalErrorHandler::mismatchedStructureBounds(Token source, std::string start, std::string end)
	{
		append(source, "mismatched structure bounds between '"+start+"' and '"+end+"'");
	}

	void InternalErrorHandler::incompleteStructureBound(Token source, std::string start, std::string end)
	{
		append(source, "incomplete structure bound started with '"+start+"', but not completed with '"+end+"'");
	}

	void InternalErrorHandler::unexpectedArgumentList(Token source)
	{
		append(source, "unexpected argument list - only one element required");
	}

	void InternalErrorHandler::expectedExpression(Token source)
	{
		append(source, "expected expression here");
	}

	void InternalErrorHandler::operationRequiredLeftOperand(Token source)
	{
		append(source, "operator '"+source.value+"' requires left operand");
	}

	void InternalErrorHandler::unexpectedTokenInExpression(Token source)
	{
		append(source, "unexpected token '"+source.value+"' in expression");
	}

	void InternalErrorHandler::cannotOperateOnAnOperator(Token source)
	{
		append(source, "cannot operate on an operator");
	}

	bool InternalErrorHandler::empty()
	{
		return (count == 0);
	}

	bool InternalErrorHandler::dump()
	{
		if (count == 0)
		{
			return false;
		}
		else
		{
			cerr << page;
			if (count == 1)
				cerr << "1 error.\n";
			else
				cerr << count << " errors.\n";
			return true;
		}
	}

	void InternalErrorHandler::clear()
	{
		page = "";
		count = 0;
	}
}
