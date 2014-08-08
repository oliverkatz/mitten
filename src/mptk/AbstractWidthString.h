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

/* File:    AbstractWidthString.h
 * Author:  Oliver Katz
 * Version: 0.01-alpha
 * License: BSD 2-Clause
 * ========================================================================== *
 * Abstract width string class to be used for all strings in MPTK.
 */

/* Changelog:
 * ========================================================================= *
 * 0.01-alpha ------------------------------------------------ July 20, 2014 *
 * Initial release.
 */

#ifndef __MITTEN_ABSTRACT_WIDTH_STRING_H
#define __MITTEN_ABSTRACT_WIDTH_STRING_H

#include <iostream>
#include <string>
#include <stdexcept>

#include <string.h>

namespace mitten
{
	class AbstractWidthString
	{
	protected:
		void *_data;
		size_t _size;
		size_t _capacity;
		unsigned char _width;

	public:
		AbstractWidthString() : _data(NULL), _size(0), _capacity(0), _width(1) {}
		AbstractWidthString(const AbstractWidthString &s) : _data(s._data), _size(s._size), _capacity(0), _width(s._width) {}

		static AbstractWidthString fromCString8(const char *s);
		static AbstractWidthString fromCString16(const char16_t *s);
		static AbstractWidthString fromCString32(const char32_t *s);
		static AbstractWidthString fromString8(std::string s);
		static AbstractWidthString fromString16(std::u16string s);
		static AbstractWidthString fromString32(std::u32string s);

		bool isResource();
		bool isSlice();

		AbstractWidthString copy();
		AbstractWidthString castToWidth(unsigned char w);

		const char *toCString8();
		const char16_t *toCString16();
		const char32_t *toCString32();
		std::string toString8();
		std::u16string toString16();
		std::u32string toString32();
	};
}

#endif