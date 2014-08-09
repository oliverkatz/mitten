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

/* File:    MittenSource.cpp
 * Author:  Oliver Katz
 * Version: 0.01-alpha
 * License: BSD 2-Clause
 * ========================================================================== *
 * Source code object for Mitten. Interface to the compiler's frontend.
 */

/* Changelog:
 * ========================================================================= *
 * 0.01-alpha ------------------------------------------------ July 20, 2014 *
 * Initial release.
 */

#include "MittenSource.h"

using namespace std;

namespace mitten
{
	int multiLineMacroPattern(int from, std::string s)
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

	MittenSource::MittenSource()
	{
		lexer.deliminate("//", "\n") = Filtered;
		lexer.deliminate("/*", "*/") = Filtered;
		lexer.deliminate("#", multiLineMacroPattern);
		lexer.deliminate("\n") = Filtered;
		lexer.deliminate("\t") = Filtered;
		lexer.deliminate(" ") = Filtered;

		directiveLexer.deliminate("\t") = Filtered;
		directiveLexer.deliminate(" ") = Filtered;
	}

	bool MittenSource::readSourceFile(string p)
	{
		path = p;
		try
		{
			page = readFile(path);
		}
		catch (runtime_error &e)
		{
			return true;
		}

		return false;
	}

	bool MittenSource::setSourceString(string s)
	{
		path = "--";
		page = s;

		return (s.empty());
	}

	bool MittenSource::lex(bool verbose)
	{
		if (page.empty())
			return true;

		toks = lexer.lex(page, path);

		if (verbose)
		{
			cout << "lex " << path << ":\n";
			cout << string(50, '=') << "\n";

			int line = 1;
			for (auto i : toks)
			{
				if (i.line() != line)
				{
					cout << "\n";
					line = i.line();
				}

				cout << "'" << i.value() << "' ";
			}

			cout << "\n\n";
		}

		return false;
	}

	bool MittenSource::preProcessLexical(bool verbose)
	{
		if (verbose)
		{
			cout << "preprocess lexical " << path << ":\n";
			cout << string(50, '=') << "\n";
		}

		vector<Token> res;

		for (int i = 0; i < toks.size(); i++)
		{
			if (toks[i].tag() == DeliminatorTag && toks[i].value()[0] == '#')
			{
				string d = toks[i].value().substr(1, toks[i].value().size()-2);
				vector<Token> dt = directiveLexer.lex(d, path);
				
				if (dt[0].value().compare("define") == 0)
				{
					if (dt.size() < 2)
					{
						meh.insufficientDirectiveArguments(toks[i]);
					}
					else
					{
						if (lexicalMacros.find(dt[1].value()) != lexicalMacros.end())
						{
							meh.macroAlreadyDefined(toks[i]);
						}
						else
						{
							lexicalMacros[dt[1].value()].insert(lexicalMacros[dt[1].value()].end(), dt.begin()+2, dt.end());
							for (auto j : lexicalMacros[dt[1].value()])
								j.setTag(SyntheticTag);
							if (verbose)
							{
								cout << dt[1].value() << " <=";
								for (int j = 2; j < dt.size(); j++)
									cout << " '" << dt[j].value() << "'";
								cout << "\n";
							}
						}
					}
				}
				else if (dt[0].value().compare("undef") == 0)
				{
					if (dt.size() != 2)
					{
						meh.insufficientDirectiveArguments(toks[i]);
					}
					else
					{
						if (lexicalMacros.find(dt[1].value()) == lexicalMacros.end())
						{
							meh.useOfUndefinedMacro(toks[i]);
						}
						else
						{
							lexicalMacros.erase(dt[1].value());
							if (verbose)
							{
								cout << dt[1].value() << " <= <null>\n";
							}
						}
					}
				}
				else if (dt[0].value().compare("redef") == 0)
				{
					if (dt.size() < 2)
					{
						meh.insufficientDirectiveArguments(toks[i]);
					}
					else
					{
						if (lexicalMacros.find(dt[1].value()) == lexicalMacros.end())
						{
							meh.useOfUndefinedMacro(toks[i]);
						}
						else
						{
							lexicalMacros[dt[1].value()].clear();
							lexicalMacros[dt[1].value()].insert(lexicalMacros[dt[1].value()].end(), dt.begin()+2, dt.end());
							for (auto j : lexicalMacros[dt[1].value()])
								j.setTag(SyntheticTag);
							if (verbose)
							{
								cout << dt[1].value() << " <=";
								for (int j = 2; j < dt.size(); j++)
									cout << " '" << dt[j].value() << "'";
								cout << "\n";
							}
						}
					}
				}
				else if (dt[0].value().compare("include") == 0)
				{
					
				}
				else
				{
					meh.unknownDirective(toks[i]);
				}
			}
			else if (lexicalMacros.find(toks[i].value()) != lexicalMacros.end())
			{
				res.insert(res.end(), lexicalMacros[toks[i].value()].begin(), lexicalMacros[toks[i].value()].end());
			}
			else
			{
				res.push_back(toks[i]);
			}
		}

		toks = res;

		if (verbose)
		{
			cout << string(50, '-') << "\n";

			int line = 1;
			for (auto i : toks)
			{
				if (i.line() != line)
				{
					cout << "\n";
					line = i.line();
				}

				cout << "'" << i.value() << "' ";
			}

			cout << "\n\n";
		}

		return false;
	}

	string MittenSource::reconstruct()
	{
		if (!toks.empty())
		{
			return reconstructFromTokenVector(toks);
		}
		else
		{
			return page;
		}
	}

	void MittenSource::clear()
	{
		page.clear();
		toks.clear();
		lexicalMacros.clear();
		meh.clear();
	}

	bool MittenSource::areErrors()
	{
		return !meh.empty();
	}

	bool MittenSource::dumpErrors()
	{
		return meh.dump();
	}

	void MittenSource::clearErrors()
	{
		meh.clear();
	}
}
