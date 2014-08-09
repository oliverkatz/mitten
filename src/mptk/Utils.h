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

#ifndef __MITTEN_UTILS_H
#define __MITTEN_UTILS_H

#include <iostream>
#include <string>
#include <streambuf>
#include <fstream>
#include <stdexcept>

namespace mitten
{
	/** \brief Reads a file into a string.
	 * Loads the entire contents of a file into a dynamically-expanding string object.
	 * If readFile is unable to open the file, it will throw a runtime_error.
	 * \param path The path of the file to be read.
	 * \returns The contents of the file.
	 */
	std::string readFile(std::string path);

	/** \brief Evaluates escape codes in a string.
	 * Iterates through the input string and converts all C-style escape codes into their equivalent character codes.
	 * \param s Input string to be iterated.
	 * \returns The resultant string.
	 * \todo Move this method to the AbstractWidthString class.
	 */
	std::string evaluateEscapeCodes(std::string s);

	/** \brief Converts all non-printable characters in the string to escape codes.
	 * Iterates through the input string and converts all non-printable characters to C-style escape codes.
	 * \param s Input string to be iterated.
	 * \returns The resultant string.
	 * \todo Move this method to the AbstractWidthString class.
	 */
	std::string makePrintable(std::string s);

	/** \brief Trims whitespace from both ends.
	 * This should be in the C++ standard library, but it's not easily accessable.
	 * \param s String to be stripped.
	 * \returns The stripped string.
	 * \todo Move this method to the AbstractWidthString class.
	 */
	std::string stripString(std::string s);
}

#endif