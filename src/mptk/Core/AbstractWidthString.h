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

 /* NOTE: String width abstraction is a feature that will be used in version 
  * 0.02-alpha. The source code here is unfinished and unused. */

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
		size_t _size; //! Size of string in characters.
		size_t _capacity; //! Memory usage capacity in characters.
		unsigned char _width; //! Width of character in bytes.

		void release();

	public:
		static const float defaultFac; //! The default factor for dynamic re-allocation.
		static const int defaultOff; //! The default offset for dynamic re-allocation.
		static const size_t npos; //! The returned value of find and rfind if not instance is found.

		/*! \brief Character type.
		 */
		typedef char32_t Char;

		/*! \brief Constructor.
		 * Constructs uninitialized string. 
		 */
		AbstractWidthString() : _data(NULL), _size(0), _capacity(0), _width(1) {}

		/*! \brief Constructor.
		 * Copy constructor to preserve memory management.
		 */
		AbstractWidthString(const AbstractWidthString &s);

		/*! \brief Constructor.
		 * Casting from C++ strings.
		 */
		AbstractWidthString(std::string s);

		/*! \brief Destructor.
		 * Releases and nullifies the current string.
		 */
		~AbstractWidthString();

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

		/*! \brief Gets the raw data pointer of the string.
		 */
		const void *data();

		/*! \brief Gets the number of characters in the string.
		 */
		size_t size();

		/*! \brief Returns true only if the string size is 0.
		 */
		bool empty();

		/*! \brief Gets character width of the string in bytes
		 */
		size_t width();

		/*! \brief Gets the memory size of the string in bytes.
		 * Essentially, size()*width()
		 */
		size_t memsize();

		/*! \brief Gets the capacity of the string in characters.
		 * Although this capacity is governed by memory capacity, it is still given in
		 * characters for consistency.
		 */
		size_t capacity();

		/*! \brief Gets the memory capacity of the string in bytes.
		 * Essentially, capacity()*width()
		 */
		size_t memcapacity();

		/*! \brief Reallocates the memory space with the specified size in characters.
		 * Must be given in characters for abstraction purposes.
		 */
		void reallocate(size_t s);

		/*! \brief Resizes the string length to the specified size in characters.
		 */
		void resize(size_t s);

		/*! \brief Random accessor.
		 * \param n Index of character.
		 * \returns A copy of the character at index n cast to a 32-bit integer.
		 */
		Char operator [] (int n);

		/*! \brief Comparison operation.
		 * \param s String to compare to.
		 * \returns Lexiographical difference between strings (either -1, 0, or 1).
		 */
		int compare(AbstractWidthString s);

		/*! \brief Equal-to operation.
		 * \param s String to compare to.
		 * \returns Result of operation.
		 */
		bool operator == (AbstractWidthString s);

		/*! \brief Equal-to operation.
		 * \param s String to compare to.
		 * \returns Result of operation.
		 */
		bool operator != (AbstractWidthString s);

		/*! \brief Equal-to operation.
		 * \param s String to compare to.
		 * \returns Result of operation.
		 */
		bool operator < (AbstractWidthString s);

		/*! \brief Equal-to operation.
		 * \param s String to compare to.
		 * \returns Result of operation.
		 */
		bool operator <= (AbstractWidthString s);

		/*! \brief Equal-to operation.
		 * \param s String to compare to.
		 * \returns Result of operation.
		 */
		bool operator > (AbstractWidthString s);

		/*! \brief Equal-to operation.
		 * \param s String to compare to.
		 * \returns Result of operation.
		 */
		bool operator >= (AbstractWidthString s);

		/*! \brief Append string to current string.
		 * \param s String to append.
		 * \param fac Factor that the string size will be multiplied by for dynamic re-allocation.
		 * \param off The offset to be applied to the string size for dynamic re-allocation after the factor.
		 * \returns Reference to current string after append.
		 */
		AbstractWidthString &append(AbstractWidthString s, float fac = defaultFac, int off = defaultOff);

		/*! \brief Append string to current string.
		 * \param s String to append.
		 * \returns Reference to current string after append.
		 */
		AbstractWidthString &operator += (AbstractWidthString s);

		/*! \brief Append character to current string.
		 * \param c Character to append.
		 * \param fac Factor that the string size will be multiplied by for dynamic re-allocation.
		 * \param off The offset to be applied to the string size for dynamic re-allocation after the factor.
		 * \returns Reference to current string after append.
		 */
		AbstractWidthString &append(Char c, float fac = defaultFac, int off = defaultOff);

		/*! \brief Append character to current string.
		 * \param c Character to append.
		 * \returns Reference to current string after append.
		 */
		AbstractWidthString &operator += (Char c);

		/*! \brief Returns a new string which is a slice of the current string.
		 * Starts from \p from and goes for \p len characters.
		 * \param from The start point of the substring in characters.
		 * \param len The length of the substring in characters.
		 * \returns The created substring.
		 */
		AbstractWidthString substr(size_t from, size_t len = (size_t)-1);

		/*! \brief Inserts the contents of \p s into the string at position \p pos.
		 * \param pos The position at which to insert the string in characters.
		 * \param s The string to be inserted.
		 * \param fac Factor that the string size will be multiplied by for dynamic re-allocation.
		 * \param off The offset to be applied to the string size for dynamic re-allocation after the factor.
		 * \returns Reference to current string after insert.
		 */
		AbstractWidthString &insert(size_t pos, AbstractWidthString s, float fac = defaultFac, int off = defaultOff);

		/*! \brief Erases \p len characters of the contents of the string from position \p from.
		 * \param from The start point of the erasure in characters.
		 * \param len The length of the erasure in characters.
		 * \returns Reference to the current string after erasure.
		 */
		AbstractWidthString &erase(size_t from, size_t len);

		/*! \brief Finds the first instance of \p s starting from \p from.
		 * \param s The string pattern to look for.
		 * \param from The start point for the find.
		 * \returns The index of the first instance of \p s, AbstractWidthString::npos if not in string.
		 */
		size_t find(AbstractWidthString s, size_t from = 0);

		/*! \brief Finds the last instance of \p s after \p after.
		 * \param s The string pattern to look for.
		 * \param after The first index allowed.
		 * \returns The index of the last instance of \p s, AbstractWidthString::npos if not in string.
		 */
		size_t rfind(AbstractWidthString s, size_t after = 0);

		/*! \brief Finds the first instance of \p c starting from \p from.
		 * \param s The character to look for.
		 * \param from The start point for the find.
		 * \returns The index of the first instance of \p c, AbstractWidthString::npos if not in string.
		 */
		size_t find(Char c, size_t from = 0);

		/*! \brief Finds the last instance of \p c after \p after.
		 * \param s The character to look for.
		 * \param after The first index allowed.
		 * \returns The index of the last instance of \p c, AbstractWidthString::npos if not in string.
		 */
		size_t rfind(Char c, size_t after = 0);

		/*! \brief Evaluates escape codes in a string.
	 	 * Iterates through the input string and converts all C-style escape codes into their equivalent character codes.
	 	 * \returns Evaluated string.
	 	 */
		AbstractWidthString evaluateEscapeCodes();

		/*! \brief Converts all non-printable characters in the string to escape codes.
	 	 * Iterates through the input string and converts all non-printable characters to C-style escape codes.
	 	 * \returns Printable string.
	 	 */
		AbstractWidthString makePrintable();

		/*! \brief Trims whitespace from both ends.
	 	 * This should be in the C++ standard library, but it's not easily accessable.
	 	 * \returns Stripped string.
	 	 */
		AbstractWidthString strip();
	};
}

#endif