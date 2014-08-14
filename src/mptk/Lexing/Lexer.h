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

#ifndef __MITTEN_LEXER_H
#define __MITTEN_LEXER_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "../Core/Token.h"
#include "../Core/ErrorHandler.h"
#include "Latin/BooleanLiteralTagger.h"
#include "Latin/CharacterLiteralTagger.h"
#include "Latin/FloatingLiteralTagger.h"
#include "Latin/IntegerLiteralTagger.h"
#include "Latin/StringLiteralTagger.h"
#include "Latin/SymbolTagger.h"

namespace mitten
{
	/*! \brief Bitwise flags for deliminator declarations.
	 * The lexer uses these flags to configure how the tokens are added to the resultant token vector.
	 */
	typedef enum
	{
		Defaults = 0x00, //! No special flags.
		Filtered = 0x01, //! Removes the token from the token vector resultant from lexing.
	} DeliminatorFlags;

	/*! \brief Performs lexing. 
	 * Configure this class only to configure the lexical grammar for the source language.
	 */
	class Lexer
	{
	protected:
		/*! \brief Helper type.
		 * Used to store deliminator start/end-points. It contains not only the
		 * string pattern itself, but the line/column difference across the
		 * string.
		 */
		typedef struct StringConstPattern
		{
			std::string value; //! String value.
			int linediff, coldiff; //! Line/column difference across the string.

			/*! \brief Constructor.
			 * Initializes empty pattern.
			 */
			StringConstPattern() : linediff(0), coldiff(0) {}

			/*! \brief Constructor.
			 * Initializes pattern with string value.
			 * \param v String value.
			 */
			StringConstPattern(std::string v);
		} StringConstPattern;

		/*! \brief Callback to be used for deliminator end-points.
		 * \param from The current position in the string.
		 * \param s The string to look for the end-point in.
		 * \returns Length of the resultant deliminator.
		 */
		typedef int (*DeliminatorPatternCallback)(int from, std::string s);

		/*! \brief Helper type.
		 * Stores deliminator descriptions.
		 */
		typedef struct Deliminator
		{
			StringConstPattern start; //! Start point.
			StringConstPattern end; //! End point.
			DeliminatorFlags flags; //! Description flags.
			DeliminatorPatternCallback patternCallback; //! A callback that can be used in leiu of the end point.

			/*! \brief Constructor.
			 * Initiates empty deliminator.
			 */
			Deliminator() : flags(Defaults), patternCallback(NULL) {}

			/*! \brief Constructor.
			 * Creates deliminator with start but no end point.
			 * \param p Start point.
			 */
			Deliminator(StringConstPattern p) : start(p), flags(Defaults), patternCallback(NULL) {}

			/*! \brief Constructor.
			 * Creates deliminator with start and an end point specified by a callback.
			 * \param p Start point.
			 * \param c Pattern callback.
			 */
			Deliminator(StringConstPattern p, DeliminatorPatternCallback c) : start(p), flags(Defaults), patternCallback(c) {}

			/*! \brief Constructor.
			 * Creates deliminator with start and end points.
			 * \param p Start point.
			 * \param e End point.
			 */
			Deliminator(StringConstPattern s, StringConstPattern e) : 
				start(s), end(e), patternCallback(NULL), flags(Defaults) {}
		} Deliminator;

		/*! \brief The set of deliminators, sorted by size and then start-point.
		 */
		std::unordered_map<size_t, 
			std::unordered_map<std::string, Deliminator> > delims;

		/*! \brief The length of the longest deliminator added to the deliminator set.
		 */
		size_t maxDelimLength;

		/*! \brief Helper method to identify the tag of any given token.
		 * \todo Optimize for better efficiency.
		 * \param t Input token.
		 * \return Token tag.
		 */
		TokenTag findTag(Token t);

		/*! \brief Lexical macro dictionary. 
		*/
		std::unordered_map<std::string, std::vector<Token> > lexicalMacros;

	public:
		BooleanLiteralTagger boolTag; //! The boolean tag parser.
		IntegerLiteralTagger intTag; //! The int tag parser.
		FloatingLiteralTagger floatTag; //! The float tag parser.
		CharacterLiteralTagger charTag; //! The character tag parser.
		StringLiteralTagger stringTag; //! The string tag parser.
		SymbolTagger symbolTag; //! The symbol tag parser.
		
		/*! \brief Callback which is run upon recieving token.
		 * The first argument is the token which was lexed. The second is the current vector
		 * of tokens. To replicate default behavior (tokens lexed are added to the results vector)
		 * simply append the token lexed to the back of the vector.
		 */
		std::function<void (Token, std::vector<Token> &, ErrorHandler &)> onToken;

		/*! \brief Constructor.
		 * Initializes a lexer with an empty lexical grammar.
		 */
		Lexer() : maxDelimLength(0) {}

		/*! \brief Copy constructor.
		 * Copies the lexer given completely.
		 */
		Lexer(const Lexer &l) : boolTag(l.boolTag), intTag(l.intTag), floatTag(l.floatTag), charTag(l.charTag), stringTag(l.stringTag), symbolTag(l.symbolTag), delims(l.delims), maxDelimLength(l.maxDelimLength) {}

		/*! \brief Adds a new deliminator to the lexical grammar.
		 * \param s The start point of the deliminator.
		 * \param e An optional end point for the deliminator.
		 * \returns A reference to the deliminator flags for the deliminator; set them as you please to configure the deliminator.
		 */
		DeliminatorFlags &deliminate(std::string s, std::string e = "");

		/*! \brief Adds a new deliminator to the lexical grammar.
		 * \param s The start point of the deliminator.
		 * \param c The callback to be used to detect the end point for the deliminator.
		 * \returns A reference to the deliminator flags for the deliminator; set them as you please to configure the deliminator.
		 */
		DeliminatorFlags &deliminate(std::string s, DeliminatorPatternCallback c);

		/*! \brief Removes a deliminator from the lexical grammar.
		 * \param s The start point of the deliminator to remove.
		 */
		void undeliminate(std::string s);

		/*! \brief Defines a new macro for use in the rest of the code.
		 * \param s The name of the macro.
		 * \param v The value of the macro.
		 * \param eh The error handler.
		 */
		void defineMacro(std::string s, std::vector<Token> v);
		
		/*! \brief Undefines an existing macro for the rest of the code.
		 * \param s The name of the macro.
		 * \param eh The error handler.
		 */
		void undefineMacro(std::string t);
		
		/*! \brief Checks whether or not a macro is defined.
		 * \param s The name of the macro.
		 */
		bool isMacroDefined(std::string s);

		/*! \brief Performs the actual lexical analysis.
		 * \param s The input string.
		 * \param f The input file name.
		 * \param eh The error handler.
		 * \param lineoff The starting line number (from 1), -1 if none.
		 * \aaram coloff The starting column number (from 0), -1 if none.
		 * \returns The resultant token vector.
		 */
		std::vector<Token> lex(std::string s, std::string f, ErrorHandler &eh, int lineoff = -1, int columnoff = -1);
	};
}

#endif
