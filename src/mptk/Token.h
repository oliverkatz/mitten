/*!****************************************************************************
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

#ifndef __MITTEN_TOKEN_H
#define __MITTEN_TOKEN_H

#include <iostream>
#include <string>

namespace mitten
{
	/*! \brief An enumeration of the different token tags.
	 * Tokens are automatically tagged with certain built-in tags during lexing. These tags identify symbols,
	 * different literal types, deliminators, and synthetically-generated tokens generated by the preprocessor.
	 * Since these tags are entirely built-in, they cannot be extended. At most, there should be only 8 of them
	 * due to how they are stored in the token class.
	 */
	typedef enum
	{
		DeliminatorTag, //! Tag assigned to all deliminator tokens.
		SymbolTag, //! Tag assigned to C-style symbols.
		BooleanLiteralTag, //! Tag assigned to boolean literal tokens.
		IntegerLiteralTag, //! Tag assigned to integer literal tokens.
		FloatingLiteralTag, //! Tag assigned to floating-point literal tokens.
		CharacterLiteralTag, //! Tag assigned to character literal tokens.
		StringLiteralTag, //! Tag assigned to string literal tokens.
		SyntheticTag //! Tag assigned to tokens synthesized by the preprocessor.
	} TokenTag;

	/*! \brief Contains the information required in a simple token.
	 * \todo Reduce memory footprint.
	 */
	class Token
	{
	protected:
		int _line; //! Line number of the first character of the token.
		int _column; //! Column number of the first character of the token.
		std::string _value; //! The token's value.
		TokenTag _tag; //! The token's tag.
		std::string _file; //! The file path of the origin file.

	public:
		/*! \brief Constructor.
		 * Intializes the line and column number to the beginning of the file.
		 */
		Token() : _line(1), _column(0), _file("--") {}

		/*! \brief Constructor
		 * Sets all of the information in the token.
		 * \param v The value of the token.
		 * \param f The origin file path.
		 * \param l The line number.
		 * \param c The column number.
		 * \param t Optional token tag.
		 */
		Token(std::string v, std::string f, int l, int c, TokenTag t = DeliminatorTag) : _line(l), _column(c), _value(v), _tag(t), _file(f) {}

		/*! \brief Gets the line number of the first character of the token. 
		 * Starts from 1.
		 */
		int line();

		/*! \brief Gets the column number of the first character of the token.
		 * Starts from 0.
		 */
		int column();

		/*! \brief Gets the value of the token. */
		std::string value();

		/*! \brief Gets the tag of the token. */
		TokenTag tag();

		/*! \brief Assigns the tag of the token.
		 * Used mostly by the tagger in the Lexer class.
		 */
		TokenTag &setTag(TokenTag t);

		/*! \brief Gets the file path of the origin file. */
		std::string file();
	};
}

#endif