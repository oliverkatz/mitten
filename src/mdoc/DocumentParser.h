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

#ifndef __MITTEN_DOCUMENT_PARSER_H
#define __MITTEN_DOCUMENT_PARSER_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>

#include <MPTK.h>

namespace mitten
{
	typedef enum
	{
		BulletType,
		NumberedType,
		LabeledType
	} ListType;

	typedef enum
	{
		Numbers,
		LettersUpper,
		LettersLower,
		NumeralsUpper,
		NumeralsLower
	} ListNumberingType;

	class DocumentParser
	{
	protected:
		std::string path;
		std::string body;

		virtual void onText(std::string t);
		virtual void onReference(std::string r);
		virtual void onTitle(std::string t);
		virtual void onSubtitle(std::string st);
		virtual void onAuthor(std::string a);
		virtual void onDate(std::string d);
		virtual void onSection(std::string s, std::string r);
		virtual void onSubSection(std::string s, std::string r);
		virtual void onSubSubSection(std::string s, std::string r);
		virtual void onSubSubSubSection(std::string s, std::string r);
		virtual void onAppendix(std::string a, std::string r);
		virtual void onBeginAbstract();
		virtual void onEndAbstract();
		virtual void onBeginFigure(std::string f, std::string r);
		virtual void onEndFigure();
		virtual void onBeginCode();
		virtual void onEndCode();
		virtual void onBeginAlgorithm();
		virtual void onEndAlgorithm();
		virtual void onAlgorithmInstruction(std::string s);
		virtual void onAlgorithmBeginStatement(std::string sn, std::string s);
		virtual void onAlgorithmEndStatement();
		virtual void onBeginList(ListType lt = BulletType, ListNumberingType lnt = Numbers);
		virtual void onBeginListElement(std::string l = "");
		virtual void onEndListElement();
		virtual void onEndList();
		virtual void onNewLine();
		virtual void onNewPage();
		virtual void onNewParagraph();
		virtual void onBeginAxiom(std::string n, std::string r);
		virtual void onEndAxiom();
		virtual void onBeginTheorem(std::string n, std::string r);
		virtual void onEndTheorem();
		virtual void onBeginCorrelary(std::string n, std::string r, std::string to);
		virtual void onEndCorrelary();

	private:
		std::string errorPage;
		int errorCount;

		void error(Token source, std::string message);

		bool currentlyInAlgorithm, currentlyInList;

		void handleCommand(Token tok, std::string command);

	public:
		DocumentParser() : errorCount(0), currentlyInAlgorithm(false) {}

		static void init();

		void read(std::string p);

		bool parse();
		std::string dumpErrors();
	};
}

#endif