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

#ifndef __MITTEN_INTEGER_LITERAL_TAGGER_H
#define __MITTEN_INTEGER_LITERAL_TAGGER_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "../../Core/Token.h"

namespace mitten
{
	/*! \brief Identifies integer literals from tokens.
	 */
	class IntegerLiteralTagger
	{
	public:
		bool allowDecimal; //! Set to true to allow decimal integers.
		bool allowOctal; //! Set to true to allow octal integers.
		bool allowHexadecimalLowercase; //! Set to true to allow hex integers with lowercase letters.
		bool allowHexadecimalUppercase; //! Set to true to allow hex integers with uppercase letters.
		bool allowNegative; //! Set to true to allow negative integers.

		/*! \brief Constructor
		 * Initializes C-style integers. */
		IntegerLiteralTagger() : allowDecimal(true), allowOctal(true), 
			allowHexadecimalLowercase(true), allowHexadecimalUppercase(true),
			allowNegative(true) {}

		/*! \brief Checks if a token is an integer according to the configuration.
		 * \param t Token to be checked.
		 * \returns True only if the token is a valid integer.
		 */
		bool isIntegerLiteral(Token t);

		/*! \brief Checks if a string is an integer according to the configuration.
		 * \param t String to be checked.
		 * \returns True only if the string is a valid integer.
		 */
		bool isIntegerLiteral(std::string s);

		/*! \brief Parses the integer literal's contents.
		 * String-to-int conversion function.
		 */
		int parse(Token t);

		/*! \brief Parses the integer literal's contents.
		 * String-to-int conversion function.
		 */
		int parse(std::string s);
	};
}

#endif