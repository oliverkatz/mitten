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

/* File:    FloatingLiteralTagger.cpp
 * Author:  Oliver Katz
 * Version: 0.01-alpha
 * License: BSD 2-Clause
 * ========================================================================== *
 * Detects floating-point literals.
 */

/* Changelog:
 * ========================================================================= *
 * 0.01-alpha ------------------------------------------------ July 20, 2014 *
 * Initial release.
 */

#include "FloatingLiteralTagger.h"

using namespace std;

namespace mitten
{
	bool FloatingLiteralTagger::isFloatingLiteral(Token t)
	{
		return isFloatingLiteral(t.value);
	}

	bool FloatingLiteralTagger::isFloatingLiteral(string s)
	{
		bool gotDot = false;
		for (int i = 0; i < s.size(); i++)
		{
			if (s[i] == '-' && i != 0)
			{
				return false;
			}
			else if (s[i] == '.')
			{
				if (gotDot)
				{
					return false;
				}
				else
				{
					gotDot = true;
				}
			}
			else if (s[i] == 'e' && (i != 0 && i != s.size()-1))
			{
				if (!allowScientific)
				{
					return false;
				}
			}
			else if (isdigit(s[i]))
			{
				continue;
			}
			else if (s[i] != '-')
			{
				return false;
			}
		}

		return true;
	}

	double FloatingLiteralTagger::parse(Token t)
	{
		return parse(t.value);
	}

	double FloatingLiteralTagger::parse(string s)
	{
		if (s.find("e") != string::npos)
		{
			if (!allowScientific)
			{
				throw runtime_error("scientific floats not allowed");
			}
			else
			{
				double base = stod(s.substr(0, s.find("e")));
				double exp10 = stod(s.substr(s.find("e")+1));
				return base*pow(10, exp10);
			}
		}
		else
		{
			return stod(s);
		}
	}
}
