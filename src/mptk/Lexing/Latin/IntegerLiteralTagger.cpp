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

#include "IntegerLiteralTagger.h"

using namespace std;

namespace mitten
{
	bool IntegerLiteralTagger::isIntegerLiteral(Token t)
	{
		return isIntegerLiteral(t.value());
	}

	bool IntegerLiteralTagger::isIntegerLiteral(string s)
	{
		if (s.compare("0x") == 0)
		{
			return false;
		}

		std::string tmp;
		if (s[s.size()-1] == 'h' && (isdigit(s[0]) || (s[0] >= 'a' && s[0] <= 'f') || (s[0] >= 'A' && s[0] <= 'F')))
			tmp = "0x" + s.substr(0, s.size()-1);
		else
			tmp = s;

		try
		{
			stoi(tmp, NULL, 0);
			return true;
		}
		catch(invalid_argument &e)
		{
			return false;
		}
	}

	int IntegerLiteralTagger::parse(Token t)
	{
		return parse(t.value());
	}

	int IntegerLiteralTagger::parse(string s)
	{
		if (s.compare("0x") == 0)
			throw runtime_error("invalid integer format");

		string tmp;
		if (s[s.size()-1] == 'h' && (isdigit(s[0]) || (s[0] >= 'a' && s[0] <= 'f') || (s[0] >= 'A' && s[0] <= 'F')))
			tmp = "0x" + s.substr(0, s.size()-1);
		else
			tmp = s;

		return stoi(tmp, NULL, 0);
	}
}
