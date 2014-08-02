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

/* File:    Lexer.cpp
 * Author:  Oliver Katz
 * Version: 0.01-alpha
 * License: BSD 2-Clause
 * ========================================================================== *
 * The lexical analyzer within MPTK is implemented here.
 */

/* Changelog:
 * ========================================================================= *
 * 0.01-alpha ------------------------------------------------ July 20, 2014 *
 * Initial release.
 */

#include "Lexer.h"

using namespace std;

namespace mitten
{
	Lexer::StringConstPattern::StringConstPattern(std::string v)
	{
		value = v;
		for (auto i : v)
		{
			if (i == '\n')
			{
				linediff++;
				coldiff = 0;
			}
			else
			{
				coldiff++;
			}
		}
	}

	TokenTag Lexer::findTag(Token t)
	{
		if (symbolTag.isSymbol(t))
			return SymbolTag;
		else if (boolTag.isBooleanLiteral(t))
			return BooleanLiteralTag;
		else if (charTag.isCharacterLiteral(t))
			return CharacterLiteralTag;
		else if (stringTag.isStringLiteral(t))
			return StringLiteralTag;
		else if (intTag.isIntegerLiteral(t))
			return IntegerLiteralTag;
		else if (floatTag.isFloatingLiteral(t))
			return FloatingLiteralTag;
		else
			return DeliminatorTag;
	}

	DeliminatorFlags &Lexer::deliminate(std::string s, std::string e)
	{
		if (s.empty())
			throw std::runtime_error("cannot deliminate empty string");

		if (e.empty())
			delims[s.size()][s] = Deliminator(StringConstPattern(s));
		else
			delims[s.size()][s] = Deliminator(StringConstPattern(s), 
				StringConstPattern(e));
		if (s.size() > maxDelimLength)
			maxDelimLength = s.size();

		return delims[s.size()][s].flags;
	}

	std::vector<Token> Lexer::lex(std::string s)
	{
		std::vector<Token> rtn;

		int line = 1;
		int column = 0;
		int lastline = 1;
		int lastcolumn = 0;
		bool found = false;
		size_t last = 0;

		for (size_t i = 0; i < s.size(); i++)
		{
			found = false;

			for (size_t j = maxDelimLength; j > 0; j--)
			{
				if (delims.find(j) != delims.end())
				{
					if (delims[j].find(s.substr(i, j)) != delims[j].end())
					{
						Deliminator d = delims[j][s.substr(i, j)];
						if (last < i)
						{
							rtn.push_back(Token(s.substr(last, i-last), 
								lastline, lastcolumn));
							rtn.back().tag = findTag(rtn.back());
						}

						size_t dl = j;
						if (!d.end.value.empty())
						{
							while (dl+i < s.size())
							{
								if (s.substr(i+dl, 
									d.end.value.size()).compare(d.end.value) 
									== 0)
								{
									dl += d.end.value.size();
									break;
								}

								dl++;
							}
						}

						if (!(d.flags & Filtered))
						{
							rtn.push_back(Token(s.substr(i, dl), line, column, DeliminatorTag));
						}
						for (auto c : s.substr(i, dl))
						{
							if (c == '\n')
							{
								line++;
								column = 0;
							}
							else
							{
								column++;
							}
						}

						lastline = line;
						lastcolumn = column;
						i += dl-1;
						last = i+1;
						found = true;
					}
				}
			}

			if (!found)
			{
				if (s[i] == '\n')
				{
					line++;
					column = 0;
				}
				else
				{
					column++;
				}
			}
		}

		return rtn;
	}
}
