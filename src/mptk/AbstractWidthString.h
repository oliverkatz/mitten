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

#ifndef __MITTEN_ABSTRACT_WIDTH_STRING_H
#define __MITTEN_ABSTRACT_WIDTH_STRING_H

#include <iostream>
#include <string>
#include <stdexcept>

#include <string.h>

namespace mitten
{
	/*! \brief String that can have any character width.
	 * Abstracts character width. Supports 8, 16, and 32 bit character encodings.
	 */
	class AbstractWidthString
	{
	protected:
		void *_data; //! Data content.
		size_t _size; //! Size of string.
		size_t _capacity; //! Memory usage capacity.
		unsigned char _width; //! Width of character in bytes.

	public:
		/*! \brief Constructor.
		 * Constructs uninitialized string. 
		 */
		AbstractWidthString() : _data(NULL), _size(0), _capacity(0), _width(1) {}

		/*! \brief Constructor.
		 * Copy constructor to preserve memory management.
		 */
		AbstractWidthString(const AbstractWidthString &s) : _data(s._data), _size(s._size), _capacity(0), _width(s._width) {}

		/*! \brief Constructor.
		 * Creates an abstract width string from an 8-bit C string.
		 */
		static AbstractWidthString fromCString8(const char *s);

		/*! \brief Constructor.
		 * Creates an abstract width string from a 16-bit C string.
		 */
		static AbstractWidthString fromCString16(const char16_t *s);

		/*! \brief Constructor.
		 * Creates an abstract width string from a 32-bit C string.
		 */
		static AbstractWidthString fromCString32(const char32_t *s);

		/*! \brief Constructor.
		 * Creates an abstract width string from an 8-bit C++ string.
		 */
		static AbstractWidthString fromString8(std::string s);

		/*! \brief Constructor.
		 * Creates an abstract width string from a 16-bit C++ string.
		 */
		static AbstractWidthString fromString16(std::u16string s);

		/*! \brief Constructor.
		 * Creates an abstract width string from a 32-bit C++ string.
		 */
		static AbstractWidthString fromString32(std::u32string s);

		/*! \brief Checks if the string is an original resource.
		 */
		bool isResource();

		/*! \brief Checks if the string is a slice of an original resource.
		 */
		bool isSlice();

		/*! \brief Creates a duplicate of the current string's memory.
		 */
		AbstractWidthString copy();

		/*! \brief Creates a duplicate of the current string's memory cast to a certain character width.
		 * \param w Target character width in bytes.
		 */
		AbstractWidthString castToWidth(unsigned char w);

		/*! \brief Converts the string to a standardized format.
		 * Generates an 8-bit C string.
		 */
		const char *toCString8();

		/*! \brief Converts the string to a standardized format.
		 * Generates a 16-bit C string.
		 */
		const char16_t *toCString16();

		/*! \brief Converts the string to a standardized format.
		 * Generates a 32-bit C string.
		 */
		const char32_t *toCString32();

		/*! \brief Converts the string to a standardized format.
		 * Generates an 8-bit C++ string.
		 */
		std::string toString8();

		/*! \brief Converts the string to a standardized format.
		 * Generates a 16-bit C++ string.
		 */
		std::u16string toString16();

		/*! \brief Converts the string to a standardized format.
		 * Generates a 32-bit C++ string.
		 */
		std::u32string toString32();

		/*! \brief Random accessor.
		 * \param n Index of character.
		 * \returns A copy of the character at index n cast to a 32-bit integer.
		 */
		char32_t operator [] (int n);
	};
}

#endif