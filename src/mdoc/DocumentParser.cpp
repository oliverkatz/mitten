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

/* File:    DocumentParser.h
 * Author:  Oliver Katz
 * Version: 0.01-alpha
 * License: BSD 2-Clause
 * ========================================================================== *
 * Intermediate class used to parse documents.
 */

/* Changelog:
 * ========================================================================= *
 * 0.01-alpha ------------------------------------------------ July 20, 2014 *
 * Initial release.
 */

#include "DocumentParser.h"

using namespace std;

namespace mitten
{
	Lexer __mdocLexer;
	Lexer __mdocCommandLexer;
	Lexer __mdocTextLexer;
	bool __mdocInitted = false;

	void DocumentParser::onText(string t)
	{
		cout << "Text: '" << t << "'\n";
	}

	void DocumentParser::onReference(string r)
	{
		cout << "Reference to: '" << r << "'\n";
	}

	void DocumentParser::onTitle(string t)
	{
		cout << "Title: '" << t << "'\n";
	}

	void DocumentParser::onSubtitle(string st)
	{
		cout << "Subtitle: '" << st << "'\n";
	}

	void DocumentParser::onAuthor(string a)
	{
		cout << "Author: '" << a << "'\n";
	}

	void DocumentParser::onDate(string d)
	{
		cout << "Date: '" << d << "'\n";
	}

	void DocumentParser::onSection(string s, string r)
	{
		cout << "Section: '" << s << "' (reference: '" << r << "')\n";
	}

	void DocumentParser::onSubSection(string s, string r)
	{
		cout << "Subsection: '" << s << "' (reference: '" << r << "')\n";
	}

	void DocumentParser::onSubSubSection(string s, string r)
	{
		cout << "Subsubsection: '" << s << "' (reference: '" << r << "')\n";
	}

	void DocumentParser::onSubSubSubSection(string s, string r)
	{
		cout << "Subsubsubsection: '" << s << "' (reference: '" << r << "')\n";
	}

	void DocumentParser::onAppendix(string a, string r)
	{
		cout << "Appendix: '" << a << "' (reference: '" << r << "')\n";
	}

	void DocumentParser::onBeginAbstract()
	{
		cout << "Begin: abstract\n";
	}

	void DocumentParser::onEndAbstract()
	{
		cout << "End: abstract\n";
	}

	void DocumentParser::onBeginFigure(string f, string r)
	{
		cout << "Begin: figure (name '" << f << "', reference '" << r << "')\n";
	}

	void DocumentParser::onEndFigure()
	{
		cout << "End: figure\n";
	}

	void DocumentParser::onBeginCode()
	{
		cout << "Begin: code\n";
	}

	void DocumentParser::onEndCode()
	{
		cout << "End: code\n";
	}

	void DocumentParser::onBeginAlgorithm()
	{
		cout << "Begin: algorithm\n";
	}

	void DocumentParser::onEndAlgorithm()
	{
		cout << "End: algorithm\n";
	}

	void DocumentParser::onAlgorithmInstruction(string s)
	{
		cout << "Algorithm Instruction: '" << s << "'\n";
	}

	void DocumentParser::onAlgorithmBeginStatement(string sn, string s)
	{
		cout << "Begin: algorithm statement (statement name '" << sn << "', statement '" << s << "')\n";
	}

	void DocumentParser::onAlgorithmEndStatement()
	{
		cout << "End: algorithm statement\n";
	}

	void DocumentParser::onBeginList(ListType lt, ListNumberingType lnt)
	{
		cout << "Begin: list\n";
	}

	void DocumentParser::onBeginListElement(string l)
	{
		cout << "Begin: list element (label '" << l << "')\n";
	}

	void DocumentParser::onEndListElement()
	{
		cout << "End: list element\n";
	}

	void DocumentParser::onEndList()
	{
		cout << "End: list\n";
	}

	void DocumentParser::onNewLine()
	{
		cout << "New line\n";
	}

	void DocumentParser::onNewPage()
	{
		cout << "New page\n";
	}

	void DocumentParser::onNewParagraph()
	{
		cout << "New paragraph\n";
	}

	void DocumentParser::onBeginAxiom(string n, string r)
	{
		cout << "Begin: axiom (name '" << n << "', reference '" << r << "')\n";
	}

	void DocumentParser::onEndAxiom()
	{
		cout << "End: axiom\n";
	}

	void DocumentParser::onBeginTheorem(string n, string r)
	{
		cout << "Begin: theorem (name '" << n << "', reference '" << r << "')\n";
	}

	void DocumentParser::onEndTheorem()
	{
		cout << "End: theorem\n";
	}

	void DocumentParser::onBeginCorrelary(string n, string r, string to)
	{
		cout << "Begin: correlary (name '" << n << "', reference '" << r << "', to '" << to << "')\n";
	}

	void DocumentParser::onEndCorrelary()
	{
		cout << "End: correlary\n";
	}

	void DocumentParser::error(Token source, string message)
	{
		errorPage += path+":"+to_string(source.line)+":"+to_string(source.column)+" - "+message+"\n";
		errorCount++;
	}

	void DocumentParser::handleCommand(Token tok, string command)
	{
		vector<Token> ctoks = __mdocCommandLexer.lex(command);

		if (ctoks.empty())
		{
			error(tok, "empty command.");
		}

		if (ctoks[0].value.compare("title") == 0)
		{
			if (ctoks.size() != 2)
			{
				error(ctoks[0], "command 'title' expects 1 argument.");
			}
			else
			{
				if (ctoks[1].value[0] != '\"')
				{
					error(ctoks[1], "expected string.");
				}
				else if (ctoks[1].value.back() != '\"')
				{
					error(ctoks[1], "incomplete string constant.");
				}
				else
				{
					onTitle(stripString(ctoks[1].value.substr(1, ctoks[1].value.size()-2)));
				}
			}
		}
		else if (ctoks[0].value.compare("subtitle") == 0)
		{
			if (ctoks.size() != 2)
			{
				error(ctoks[0], "command 'subtitle' expects 1 argument.");
			}
			else
			{
				if (ctoks[1].value[0] != '\"')
				{
					error(ctoks[1], "expected string.");
				}
				else if (ctoks[1].value.back() != '\"')
				{
					error(ctoks[1], "incomplete string constant.");
				}
				else
				{
					onSubtitle(stripString(ctoks[1].value.substr(1, ctoks[1].value.size()-2)));
				}
			}
		}
		else if (ctoks[0].value.compare("author") == 0)
		{
			if (ctoks.size() != 2)
			{
				error(ctoks[0], "command 'author' expects 1 argument.");
			}
			else
			{
				if (ctoks[1].value[0] != '\"')
				{
					error(ctoks[1], "expected string.");
				}
				else if (ctoks[1].value.back() != '\"')
				{
					error(ctoks[1], "incomplete string constant.");
				}
				else
				{
					onAuthor(stripString(ctoks[1].value.substr(1, ctoks[1].value.size()-2)));
				}
			}
		}
		else if (ctoks[0].value.compare("date") == 0)
		{
			if (ctoks.size() != 2)
			{
				error(ctoks[0], "command 'date' expects 1 argument.");
			}
			else
			{
				if (ctoks[1].value[0] != '\"')
				{
					error(ctoks[1], "expected string.");
				}
				else if (ctoks[1].value.back() != '\"')
				{
					error(ctoks[1], "incomplete string constant.");
				}
				else
				{
					onDate(stripString(ctoks[1].value.substr(1, ctoks[1].value.size()-2)));
				}
			}
		}
		else if (ctoks[0].value.compare("begin") == 0)
		{
			if (ctoks.size() < 2)
			{
				error(ctoks[0], "command 'begin' expects at least 1 argument.");
			}
			else
			{
				if (ctoks[1].value.compare("abstract") == 0)
				{
					onBeginAbstract();
				}
				else if (ctoks[1].value.compare("figure") == 0)
				{
					if (ctoks.size() != 4)
					{
						error(ctoks[1], "scope 'figure' expects 2 arguments.");
					}
					else
					{
						if (ctoks[2].value[0] != '\"')
						{
							error(ctoks[2], "expected string.");
						}
						else if (ctoks[2].value.back() != '\"')
						{
							error(ctoks[2], "incomplete string constant.");
						}
						else
						{
							onBeginFigure(stripString(ctoks[2].value.substr(1, ctoks[2].value.size()-2)), stripString(ctoks[3].value));
						}
					}
				}
				else if (ctoks[1].value.compare("code") == 0)
				{
					onBeginCode();
				}
				else if (ctoks[1].value.compare("algorithm") == 0)
				{
					onBeginAlgorithm();
					currentlyInAlgorithm = true;
				}
				else if (ctoks[1].value.compare("list") == 0)
				{
					if (ctoks.size() == 2)
					{
						onBeginList();
					}
					else if (ctoks.size() == 3)
					{
						ListType lt = BulletType;
						if (ctoks[2].value.compare("bullet") == 0)
						{
							lt = BulletType;
						}
						else if (ctoks[2].value.compare("numbered") == 0)
						{
							lt = NumberedType;
						}
						else if (ctoks[2].value.compare("labeled") == 0)
						{
							lt = LabeledType;
						}
						else
						{
							error(ctoks[2], "unknown list type '"+ctoks[2].value+"'.");
						}

						onBeginList(lt);
					}
					else if (ctoks.size() == 4)
					{
						ListType lt = NumberedType;
						if (ctoks[2].value.compare("bullet") == 0)
						{
							error(ctoks[2], "unexpected list type '"+ctoks[2].value+"'.");
						}
						else if (ctoks[2].value.compare("numbered") == 0)
						{
							lt = NumberedType;
						}
						else if (ctoks[2].value.compare("labeled") == 0)
						{
							error(ctoks[2], "unexpected list type '"+ctoks[2].value+"'.");
						}
						else
						{
							error(ctoks[2], "unknown list type '"+ctoks[2].value+"'.");
						}

						ListNumberingType lnt;
						if (ctoks[3].value.compare("numbers") == 0)
						{
							lnt = Numbers;
						}
						else if (ctoks[3].value.compare("LETTERS") == 0)
						{
							lnt = LettersUpper;
						}
						else if (ctoks[3].value.compare("letters") == 0)
						{
							lnt = LettersLower;
						}
						else if (ctoks[3].value.compare("NUMERALS") == 0)
						{
							lnt = NumeralsUpper;
						}
						else if (ctoks[3].value.compare("numerals") == 0)
						{
							lnt = NumeralsLower;
						}
						else
						{
							error(ctoks[3], "unknown list numbering type '"+ctoks[3].value+"'.");
						}

						onBeginList(lt, lnt);
					}
					else
					{
						error(ctoks[1], "scope 'list' expects 0-2 arguments.");
					}
				}
				else if (ctoks[1].value.compare("axiom") == 0)
				{
					if (ctoks.size() != 4)
					{
						error(ctoks[1], "scope 'axiom' expects 2 arguments.");
					}
					else
					{
						if (ctoks[2].value[0] != '\"')
						{
							error(ctoks[2], "expected string.");
						}
						else if (ctoks[2].value.back() != '\"')
						{
							error(ctoks[2], "incomplete string constant.");
						}
						else
						{
							onBeginAxiom(stripString(ctoks[2].value.substr(1, ctoks[2].value.size()-2)), stripString(ctoks[3].value));
						}
					}
				}
				else if (ctoks[1].value.compare("theorem") == 0)
				{
					if (ctoks.size() != 4)
					{
						error(ctoks[1], "scope 'theorem' expects 2 arguments.");
					}
					else
					{
						if (ctoks[2].value[0] != '\"')
						{
							error(ctoks[2], "expected string.");
						}
						else if (ctoks[2].value.back() != '\"')
						{
							error(ctoks[2], "incomplete string constant.");
						}
						else
						{
							onBeginTheorem(stripString(ctoks[2].value.substr(1, ctoks[2].value.size()-2)), stripString(ctoks[3].value));
						}
					}
				}
				else if (ctoks[1].value.compare("correlary") == 0)
				{
					if (ctoks.size() != 5)
					{
						error(ctoks[1], "scope 'correlary' expects 3 arguments.");
					}
					else
					{
						if (ctoks[2].value[0] != '\"')
						{
							error(ctoks[2], "expected string.");
						}
						else if (ctoks[2].value.back() != '\"')
						{
							error(ctoks[2], "incomplete string constant.");
						}
						else
						{
							onBeginCorrelary(stripString(ctoks[2].value.substr(1, ctoks[2].value.size()-2)), stripString(ctoks[3].value), stripString(ctoks[4].value));
						}
					}
				}
				else
				{
					error(ctoks[1], "unknown scope '"+ctoks[1].value+"'.");
				}
			}
		}
		else if (ctoks[0].value.compare("end") == 0)
		{
			if (ctoks.size() != 2)
			{
				error(ctoks[0], "command 'end' expects 1 arguent.");
			}
			else
			{
				if (ctoks[1].value.compare("abstract") == 0)
				{
					onEndAbstract();
				}
				else if (ctoks[1].value.compare("figure") == 0)
				{
					onEndFigure();
				}
				else if (ctoks[1].value.compare("code") == 0)
				{
					onEndCode();
				}
				else if (ctoks[1].value.compare("algorithm") == 0)
				{
					onEndAlgorithm();
					currentlyInAlgorithm = false;
				}
				else if (ctoks[1].value.compare("list") == 0)
				{
					onEndList();
				}
				else if (ctoks[1].value.compare("axiom") == 0)
				{
					onEndAxiom();
				}
				else if (ctoks[1].value.compare("theorem") == 0)
				{
					onEndTheorem();
				}
				else if (ctoks[1].value.compare("correlary") == 0)
				{
					onEndCorrelary();
				}
				else
				{
					error(ctoks[1], "unknown scope '"+ctoks[1].value+"'.");
				}
			}
		}
		else if (ctoks[0].value.compare("section") == 0)
		{
			if (ctoks.size() != 3)
			{
				error(ctoks[0], "command 'section' expects 2 arguments.");
			}
			else
			{
				if (ctoks[1].value[0] != '\"')
				{
					error(ctoks[1], "expected string.");
				}
				else if (ctoks[1].value.back() != '\"')
				{
					error(ctoks[1], "incomplete string constant.");
				}
				else
				{
					onSection(stripString(ctoks[1].value.substr(1, ctoks[1].value.size()-2)), stripString(ctoks[2].value));
				}
			}
		}
		else if (ctoks[0].value.compare("subsection") == 0)
		{
			if (ctoks.size() != 3)
			{
				error(ctoks[0], "command 'subsection' expects 2 arguments.");
			}
			else
			{
				if (ctoks[1].value[0] != '\"')
				{
					error(ctoks[1], "expected string.");
				}
				else if (ctoks[1].value.back() != '\"')
				{
					error(ctoks[1], "incomplete string constant.");
				}
				else
				{
					onSubSection(stripString(ctoks[1].value.substr(1, ctoks[1].value.size()-2)), stripString(ctoks[2].value));
				}
			}
		}
		else if (ctoks[0].value.compare("subsubsection") == 0)
		{
			if (ctoks.size() != 3)
			{
				error(ctoks[0], "command 'subsubsection' expects 2 arguments.");
			}
			else
			{
				if (ctoks[1].value[0] != '\"')
				{
					error(ctoks[1], "expected string.");
				}
				else if (ctoks[1].value.back() != '\"')
				{
					error(ctoks[1], "incomplete string constant.");
				}
				else
				{
					onSubSubSection(stripString(ctoks[1].value.substr(1, ctoks[1].value.size()-2)), stripString(ctoks[2].value));
				}
			}
		}
		else if (ctoks[0].value.compare("subsubsubsection") == 0)
		{
			if (ctoks.size() != 3)
			{
				error(ctoks[0], "command 'subsubsubsection' expects 2 arguments.");
			}
			else
			{
				if (ctoks[1].value[0] != '\"')
				{
					error(ctoks[1], "expected string.");
				}
				else if (ctoks[1].value.back() != '\"')
				{
					error(ctoks[1], "incomplete string constant.");
				}
				else
				{
					onSubSubSubSection(stripString(ctoks[1].value.substr(1, ctoks[1].value.size()-2)), stripString(ctoks[2].value));
				}
			}
		}
		else if (ctoks[0].value.compare("appendix") == 0)
		{
			if (ctoks.size() != 3)
			{
				error(ctoks[0], "command 'appendix' expects 2 arguments.");
			}
			else
			{
				if (ctoks[1].value[0] != '\"')
				{
					error(ctoks[1], "expected string.");
				}
				else if (ctoks[1].value.back() != '\"')
				{
					error(ctoks[1], "incomplete string constant.");
				}
				else
				{
					onAppendix(stripString(ctoks[1].value.substr(1, ctoks[1].value.size()-2)), stripString(ctoks[2].value));
				}
			}
		}
		else if (ctoks[0].value.compare("newline") == 0)
		{
			onNewLine();
		}
		else if (ctoks[0].value.compare("newpage") == 0)
		{
			onNewPage();
		}
		else
		{
			error(ctoks[0], "unknown command '"+ctoks[0].value+"'.");
		}
	}

	void DocumentParser::init()
	{
		if (!__mdocInitted)
		{
			__mdocLexer.deliminate("#", "\n");
			__mdocLexer.deliminate("\n") = Filtered;

			__mdocCommandLexer.deliminate(" ") = Filtered;
			__mdocCommandLexer.deliminate("\t") = Filtered;
			__mdocCommandLexer.deliminate("\"", "\"");

			__mdocTextLexer.deliminate("[", "]");
		}
	}

	void DocumentParser::read(string p)
	{
		path = p;
		body = readFile(p);
	}

	bool DocumentParser::parse()
	{
		if (!__mdocInitted)
		{
			init();
		}

		vector<Token> toks = __mdocLexer.lex(body);

		bool lastWasText = false;

		for (auto i : toks)
		{
			if (i.value.empty())
			{
				continue;
			}
			else if (i.value[0] == '#')
			{
				if (i.value.size() > 1)
				{
					handleCommand(i, i.value.substr(1, i.value.size()-2));
				}
				else
				{
					error(i, "empty command.");
				}

				lastWasText = false;
			}
			else if (currentlyInAlgorithm)
			{
				lastWasText = false;

				string line = stripString(i.value);

				if (line.back() == '{')
				{
					line = stripString(line.substr(0, line.size()-1));
					if (line.compare("{") == 0)
					{
						error(i, "'{' must be on same line.");
					}
					else if (line.find(" ") != string::npos)
					{
						string sn = line.substr(0, line.find(" "));
						string s = line.substr(line.find(" ")+1);
						onAlgorithmBeginStatement(stripString(sn), stripString(s));
					}
					else
					{
						onAlgorithmBeginStatement(stripString(line), "");
					}
				}
				else if (line.compare("}") == 0)
				{
					onAlgorithmEndStatement();
				}
				else
				{
					onAlgorithmInstruction(line);
				}
			}
			else
			{
				if (lastWasText)
					onNewParagraph();

				vector<Token> ttoks = __mdocTextLexer.lex(i.value);
				for (auto j : ttoks)
				{
					if (j.value[0] == '[')
					{
						onReference(stripString(j.value.substr(1, j.value.size()-2)));
					}
					else
					{
						onText(stripString(j.value));
					}
				}

				lastWasText = true;
			}
		}

		return (errorCount == 0);
	}

	string DocumentParser::dumpErrors()
	{
		return errorPage+"\n"+(errorCount == 1 ? "1 error.\n" : to_string(errorCount)+" errors.\n");
	}
}
