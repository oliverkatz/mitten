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
		rtn._capacity = rtn._size;
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
		rtn._capacity = rtn._size;
		rtn._width = 4;
		return rtn;
	}
}