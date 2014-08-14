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

#include "CharacterLiteralTagger.h"

using namespace std;

namespace mitten
{
	bool CharacterLiteralTagger::isCharacterLiteral(Token t)
	{
		return isCharacterLiteral(t.value());
	}

	bool CharacterLiteralTagger::isCharacterLiteral(string s)
	{
		if (s.empty())
		{
			return false;
		}

		if (s.find(inQuote) == 0 && s.rfind(unQuote) == s.size()-unQuote.size())
		{
			if (s.size() == 1+inQuote.size()+unQuote.size())
			{
				return true;
			}
			else if (s.size() > 1+inQuote.size()+unQuote.size())
			{
				return allowEscapes;
			}
		}
		else
		{
			return false;
		}
	}

	char CharacterLiteralTagger::parse(Token t)
	{
		return parse(t.value());
	}

	char CharacterLiteralTagger::parse(string s)
	{
		if (s.empty())
			throw runtime_error("invalid character literal");

		if (s.find(inQuote) == 0 && s.rfind(unQuote) == s.size()-unQuote.size())
		{
			if (s.size() == 1+inQuote.size()+unQuote.size())
			{
				return s[inQuote.size()];
			}
			else if (s.size() > 1+inQuote.size()+unQuote.size())
			{
				string tmp = evaluateEscapeCodes(s.substr(inQuote.size(), s.size()-inQuote.size()-unQuote.size()));
				return tmp[0];
			}
		}
		else
		{
			throw runtime_error("invalid character literal");
		}
	}
}
