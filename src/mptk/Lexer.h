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

/* File:    Lexer.h
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

#ifndef __MITTEN_LEXER_H
#define __MITTEN_LEXER_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "Token.h"
#include "BooleanLiteralTagger.h"
#include "CharacterLiteralTagger.h"
#include "FloatingLiteralTagger.h"
#include "IntegerLiteralTagger.h"
#include "StringLiteralTagger.h"
#include "SymbolTagger.h"

namespace mitten
{
	/* Enumerator: DeliminatorFlags
	 * ----------------------------
	 * Bit flags for deliminators.
	 */
	typedef enum
	{
		Defaults = 0x00, 	// no special flags
		Filtered = 0x01, 	// removes the token from the token vector resultant
							// from lexing
	} DeliminatorFlags;

	/* Class: Lexer
	 * ------------
	 * Performs lexing. Configure this class only to configure the lexical
	 * grammar for the source language.
	 */
	class Lexer
	{
	protected:
		/* Helper Type: StringConstPattern
		 * -------------------------------
		 * Used to store deliminator start/end-points. It contains not only the
		 * string pattern itself, but the line/column difference across the
		 * string.
		 */
		typedef struct StringConstPattern
		{
			std::string value; // string value
			int linediff, coldiff; // line/column difference across the string

			/* Constructor
			 * -----------
			 * Initializes empty pattern.
			 */
			StringConstPattern() : linediff(0), coldiff(0) {}

			/* Constructor
			 * -----------
			 * Initializes pattern with string value.
			 * 'v' - string value
			 */
			StringConstPattern(std::string v);
		} StringConstPattern;

		typedef int (*DeliminatorPatternCallback)(int from, std::string s);

		/* Helper Type: Deliminator
		 * ------------------------
		 * Stores deliminator descriptions.
		 */
		typedef struct Deliminator
		{
			StringConstPattern start, end; // start and end points
			DeliminatorFlags flags; // description flags
			DeliminatorPatternCallback patternCallback;

			/* Constructor
			 * -----------
			 * Initiates empty deliminator.
			 */
			Deliminator() : flags(Defaults), patternCallback(NULL) {}

			/* Constructor
			 * -----------
			 * Creates deliminator with start but no end point.
			 */
			Deliminator(StringConstPattern p) : start(p), flags(Defaults), patternCallback(NULL) {}

			Deliminator(StringConstPattern p, DeliminatorPatternCallback c) : start(p), flags(Defaults), patternCallback(c) {}

			/* Constructor
			 * -----------
			 * Creates deliminator with start and end points.
			 */
			Deliminator(StringConstPattern s, StringConstPattern e) : 
				start(s), end(e), patternCallback(NULL), flags(Defaults) {}
		} Deliminator;

		/* Member: delims
		 * --------------
		 * The set of deliminators, sorted by size and then start-point.
		 */
		std::unordered_map<size_t, 
			std::unordered_map<std::string, Deliminator> > delims;

		/* Member: maxDelimLength
		 * ----------------------
		 * The length of the longest deliminator added to the deliminator set.
		 */
		size_t maxDelimLength;

		TokenTag findTag(Token t);

	public:
		BooleanLiteralTagger boolTag;
		IntegerLiteralTagger intTag;
		FloatingLiteralTagger floatTag;
		CharacterLiteralTagger charTag;
		StringLiteralTagger stringTag;
		SymbolTagger symbolTag;

		/* Constructor
		 * -----------
		 * Initializes a lexer with an empty lexical grammar.
		 */
		Lexer() : maxDelimLength(0) {}

		/* Method: deliminate
		 * ------------------
		 * Adds a new deliminator to the lexical grammar.
		 * 's'     - the start point of the deliminator
		 * 'e'     - an optional end point for the deliminator
		 * returns - a reference to the deliminator flags for the deliminator;
		 *           set them as you please to configure the deliminator.
		 */
		DeliminatorFlags &deliminate(std::string s, std::string e = "");

		DeliminatorFlags &deliminate(std::string s, DeliminatorPatternCallback c);

		/* Method: lex
		 * -----------
		 * Performs the actual lexical analysis.
		 * 's'     - the input string
		 * returns - the resultant token vector
		 */
		std::vector<Token> lex(std::string s);
	};
}

#endif