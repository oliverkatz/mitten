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

#ifndef __MITTEN_POSTSCRIPT_DOCUMENT_PARSER_H
#define __MITTEN_POSTSCRIPT_DOCUMENT_PARSER_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>

#include "DocumentParser.h"

namespace mitten
{
	class PostScriptDocumentParser : public DocumentParser
	{
	protected:
		// void onText(std::string t);
		// void onReference(std::string r);
		void onTitle(std::string t);
		void onSubtitle(std::string st);
		void onAuthor(std::string a);
		void onDate(std::string d);
		// void onSection(std::string s, std::string r);
		// void onSubSection(std::string s, std::string r);
		// void onSubSubSection(std::string s, std::string r);
		// void onSubSubSubSection(std::string s, std::string r);
		// void onAppendix(std::string a, std::string r);
		// void onBeginAbstract();
		// void onEndAbstract();
		// void onBeginFigure(std::string f, std::string r);
		// void onEndFigure();
		// void onBeginCode();
		// void onEndCode();
		// void onBeginAlgorithm();
		// void onEndAlgorithm();
		// void onAlgorithmInstruction(std::string s);
		// void onAlgorithmBeginStatement(std::string sn, std::string s);
		// void onAlgorithmEndStatement();
		// void onBeginList(ListType lt = BulletType, ListNumberingType lnt = Numbers);
		// void onBeginListElement(std::string l = "");
		// void onEndListElement();
		// void onEndList();
		// void onNewLine();
		// void onNewPage();
		// void onNewParagraph();
		// void onBeginAxiom(std::string n, std::string r);
		// void onEndAxiom();
		// void onBeginTheorem(std::string n, std::string r);
		// void onEndTheorem();
		// void onBeginCorrelary(std::string n, std::string r, std::string to);
		// void onEndCorrelary();

		std::string header;
		std::string titles;
		std::string toc;
		std::string document;

		int width, height;

	public:
		PostScriptDocumentParser();
		std::string dumpPS();
	};
}

#endif