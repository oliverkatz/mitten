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

#include "MittenLexer.h"

using namespace std;

namespace mitten
{
	int MittenLexer::directivePattern(int from, string s)
	{
		bool multi = false;

		for (int i = from; i < s.size(); i++)
		{
			if (s[i] == '\n')
			{
				if (!multi)
				{
					return i-from+1;
				}
			}
			else if (s[i] == '#' && (i < s.size()-1 && s[i+1] == '{'))
			{
				multi = true;
			}
			else if (s[i] == '#' && (i < s.size()-1 && s[i+1] == '}'))
			{
				if (multi)
				{
					return i-from+2;
				}
			}
		}

		return s.size()-from;
	}

	void MittenLexer::onToken(Token t, vector<Token> &v)
	{
		if (t.tag() == DeliminatorTag && t.value()[0] == '#')
		{
			cout << "DELIMINATOR '" << t.value() << "'\n";

			if (t.value().find("#{") != string::npos)
			{
				vector<Token> d = directiveLexer.lex(t.value().substr(0, t.value().find("#{\n")), t.file(), t.line(), t.column());
				cout << "\tcommand";
				for (auto i : d)
					cout << " '" << i.value() << "'";
				
				vector<Token> da = directiveLexer.lex(t.value().substr(t.value().find("#{\n")+3), t.file(), t.line()+1, 0);
				da.pop_back();
				cout << "\n\tbody";
				for (auto i : da)
					cout << " '" << i.value() << "'";
				cout << "\n";
			}
			else
			{
				vector<Token> d = directiveLexer.lex(t.value(), t.file(), t.line(), t.column());
				cout << "\tcommand";
				for (auto i : d)
					cout << " '" << i.value() << "'";
				cout << "\n";
			}
		}
		else if (lexicalMacros.find(t.value()) != lexicalMacros.end())
		{
			v.insert(v.end(), lexicalMacros[t.value()].begin(), lexicalMacros[t.value()].end());
		}
		else
		{
			v.push_back(t);
		}
	}

	MittenLexer::MittenLexer()
	{
		deliminate("//", "\n") = Filtered;
		deliminate("/*", "*/") = Filtered;
		deliminate("#", directivePattern);
		deliminate("\n") = Filtered;
		deliminate("\t") = Filtered;
		deliminate(" ") = Filtered;

		directiveLexer = Lexer(*this);
		directiveLexer.undeliminate("#");
	}
}
