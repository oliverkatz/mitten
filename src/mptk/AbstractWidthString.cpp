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

/* File:    AbstractWidthString.cpp
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

#include "AbstractWidthString.h"

using namespace std;

namespace mitten
{
	AbstractWidthString AbstractWidthString::fromCString8(const char *s)
	{
		AbstractWidthString rtn;
		rtn._size = 0;
		while (s[rtn._size] != 0)
			rtn._size++;
		rtn._data = (void *)new char[rtn._size];
		memcpy(rtn._data, s, rtn._size);
		rtn._capacity = rtn._size;
		rtn._width = 1;
		return rtn;
	}

	AbstractWidthString AbstractWidthString::fromCString16(const char16_t *s)
	{
		AbstractWidthString rtn;
		rtn._size = 0;
		while (s[rtn._size] != 0)
			rtn._size++;
		rtn._data = (void *)new char16_t[rtn._size];
		memcpy(rtn._data, s, rtn._size*2);
		rtn._capacity = rtn._size*2;
		rtn._width = 2;
		return rtn;
	}

	AbstractWidthString AbstractWidthString::fromCString32(const char32_t *s)
	{
		AbstractWidthString rtn;
		rtn._size = 0;
		while (s[rtn._size] != 0)
			rtn._size++;
		rtn._data = (void *)new char32_t[rtn._size];
		memcpy(rtn._data, s, rtn._size*4);
		rtn._capacity = rtn._size*4;
		rtn._width = 4;
		return rtn;
	}

	AbstractWidthString AbstractWidthString::fromString8(string s)
	{
		AbstractWidthString rtn;
		rtn._size = s.size();
		rtn._data = (void *)new char[rtn._size];
		memcpy(rtn._data, s.data(), rtn._size);
		rtn._capacity = rtn._size;
		rtn._width = 1;
		return rtn;
	}

	AbstractWidthString AbstractWidthString::fromString16(u16string s)
	{
		AbstractWidthString rtn;
		rtn._size = s.size();
		rtn._data = (void *)new char16_t[rtn._size];
		memcpy(rtn._data, s.data(), rtn._size*2);
		rtn._capacity = rtn._size*2;
		rtn._width = 2;
		return rtn;
	}

	AbstractWidthString AbstractWidthString::fromString32(u32string s)
	{
		AbstractWidthString rtn;
		rtn._size = s.size();
		rtn._data = (void *)new char32_t[rtn._size];
		memcpy(rtn._data, s.data(), rtn._size*4);
		rtn._capacity = rtn._size*4;
		rtn._width = 4;
		return rtn;
	}

	bool AbstractWidthString::isResource()
	{
		return (_capacity > 0);
	}

	bool AbstractWidthString::isSlice()
	{
		return (_capacity == 0);
	}

	AbstractWidthString AbstractWidthString::copy()
	{
		AbstractWidthString rtn;
		rtn._size = _size;
		rtn._data = (void *)new char[rtn._size*_width];
		memcpy(rtn._data, _data, rtn._size*_width);
		rtn._capacity = rtn._size*_width;
		rtn._width = _width;
		return rtn;
	}

	AbstractWidthString AbstractWidthString::castToWidth(unsigned char w)
	{
		AbstractWidthString rtn;
		rtn._size = _size;
		rtn._data = (void *)new char[rtn._size*w];
		
		if (_width == 1)
		{
			char *src = (char *)_data;
			if (w == 1)
			{
				char *dst = (char *)rtn._data;
				for (int i = 0; i < _size; i++)
					dst[i] = (char)src[i];
			}
			else if (w == 2)
			{
				char16_t *dst = (char16_t *)rtn._data;
				for (int i = 0; i < _size; i++)
					dst[i] = (char16_t)src[i];
			}
			else if (w == 4)
			{
				char32_t *dst = (char32_t *)rtn._data;
				for (int i = 0; i < _size; i++)
					dst[i] = (char32_t)src[i];
			}
		}
		else if (_width == 2)
		{
			char16_t *src = (char16_t *)_data;
			if (w == 1)
			{
				char *dst = (char *)rtn._data;
				for (int i = 0; i < _size; i++)
					dst[i] = (char)src[i];
			}
			else if (w == 2)
			{
				char16_t *dst = (char16_t *)rtn._data;
				for (int i = 0; i < _size; i++)
					dst[i] = (char16_t)src[i];
			}
			else if (w == 4)
			{
				char32_t *dst = (char32_t *)rtn._data;
				for (int i = 0; i < _size; i++)
					dst[i] = (char32_t)src[i];
			}
		}
		else if (_width == 4)
		{
			char32_t *src = (char32_t *)_data;
			if (w == 1)
			{
				char *dst = (char *)rtn._data;
				for (int i = 0; i < _size; i++)
					dst[i] = (char)src[i];
			}
			else if (w == 2)
			{
				char16_t *dst = (char16_t *)rtn._data;
				for (int i = 0; i < _size; i++)
					dst[i] = (char16_t)src[i];
			}
			else if (w == 4)
			{
				char32_t *dst = (char32_t *)rtn._data;
				for (int i = 0; i < _size; i++)
					dst[i] = (char32_t)src[i];
			}
		}

		rtn._capacity = rtn._size*w;
		rtn._width = w;
		return rtn;
	}

	const char *AbstractWidthString::toCString8()
	{
		char *dst = new char[_size];
		for (int i = 0; i < _size; i++)
			dst[i] = (char)this->operator [] (i);
		return dst;
	}

	const char16_t *AbstractWidthString::toCString16()
	{
		char16_t *dst = new char16_t[_size];
		for (int i = 0; i < _size; i++)
			dst[i] = (char16_t)this->operator [] (i);
		return dst;
	}

	const char32_t *AbstractWidthString::toCString32()
	{
		char32_t *dst = new char32_t[_size];
		for (int i = 0; i < _size; i++)
			dst[i] = (char32_t)this->operator [] (i);
		return dst;
	}

	std::string AbstractWidthString::toString8()
	{
		std::string dst;
		for (int i = 0; i < _size; i++)
			dst.push_back((char)this->operator [] (i));
		return dst;
	}

	std::u16string AbstractWidthString::toString16()
	{
		std::u16string dst;
		for (int i = 0; i < _size; i++)
			dst.push_back((char16_t)this->operator [] (i));
		return dst;
	}

	std::u32string AbstractWidthString::toString32()
	{
		std::u32string dst;
		for (int i = 0; i < _size; i++)
			dst.push_back((char32_t)this->operator [] (i));
		return dst;
	}

	char32_t AbstractWidthString::operator [] (int n)
	{
		if (_width == 1)
		{
			return ((char *)_data)[n];
		}
		else if (_width == 2)
		{
			return ((char16_t *)_data)[n];
		}
		else if (_width == 4)
		{
			return ((char32_t *)_data)[n];
		}
	}
}
