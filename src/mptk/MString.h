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

/* File:    MString.h
 * Author:  Oliver Katz
 * Version: 0.01-alpha
 * License: BSD 2-Clause
 * ========================================================================== *
 * Width-abstracted string class. Supports:
 * - ASCII
 * - UTF-8
 * - UTF-16
 * - UTF-32
 *
 * Steps away from the C++ naming conventions used by the other files to keep
 * with the STL C++11 standard for usability.
 */

/* Changelog:
 * ========================================================================= *
 * 0.01-alpha ------------------------------------------------ July 20, 2014 *
 * Initial release.
 */

#ifndef __MITTEN_MSTRING_H
#define __MITTEN_MSTRING_H

#include <iostream>
#include <stdexcept>

namespace mitten
{
	class MString
	{
	protected:
		int _width;
		bool _source;
		void *_data;
		int _size;
		int _capacity;

	public:
		const static size_t npos = (size_t) -1;

		typedef unsigned char CharC;
		typedef unsigned short CharD;
		typedef unsigned int CharQ;

		typedef struct StringC
		{
			CharC *data;

			StringC() : data(NULL) {}
			StringC(MString &p) : data((CharC *)p.data()) {}
			CharC &operator [] (int n);
		} StringC;

		typedef struct StringD
		{
			CharD *data;

			StringD() : data(NULL) {}
			StringD(MString &p) : data((CharD *)p.data()) {}
			CharD &operator [] (int n);
		} StringD;

		typedef struct StringQ
		{
			CharQ *data;

			StringQ() : data(NULL) {}
			StringQ(MString &p) : data((CharQ *)p.data()) {}
			CharQ &operator [] (int n);
		} StringQ;

		typedef struct iterator
		{
			int _width;
			void *_pos;

			iterator() : _width(1), _pos(NULL) {}
			CharQ &operator * ();
			iterator &operator ++ ();
			iterator &operator -- ();
			iterator operator + (int o);
			iterator &operator += (int o);
			int operator - (iterator i);
			iterator &operator -= (int o);
			bool operator < (iterator i);
			bool operator <= (iterator i);
			bool operator > (iterator i);
			bool operator >= (iterator i);
			bool operator == (iterator i);
			bool operator != (iterator i);
			CharQ &operator [] (int n);
		} iterator;

		MString();
		MString(const MString &res);
		MString(const char *s);
		MString(const void *s, int w);
		MString(const std::string s);
		MString(const std::wstring s);
		MString(const std::u16string s);
		MString(const std::u32string s);
		~MString();

		iterator begin();
		iterator end();
		
		size_t size();
		size_t length();
		void resize(size_t n);
		void resize(size_t n, CharQ c);
		size_t capacity();
		void reserve(size_t n);
		void clear();
		bool empty();
		void shrink_to_fit();

		CharQ &operator [] (int n);
		CharQ &at(int n);
		CharQ &back();
		CharQ &front();

		MString &operator += (MString s);
		MString &append(MString s);
		MString &append(size_t n, CharQ c);
		MString &insert(size_t pos, MString str);
		MString &insert(size_t pos, MString str, size_t subpos, size_t sublen);
		MString &insert(size_t pos, size_t n, CharQ c);
		MString &insert(iterator p, size_t n, CharQ c);
		MString &insert(iterator p, CharQ c);
		MString &erase(size_t pos = 0, size_t len = npos);
		MString &erase(iterator p);
		MString &erase(iterator first, iterator last);
		MString &replace(size_t pos, size_t len, MString s);
		MString &replace(iterator start, iterator end, MString s);
		void swap(MString &s);
		CharQ pop_back();

		const CharC *c_str_8();
		const CharD *c_str_16();
		const CharQ *c_str_32();
		const void *data();

		size_t find(MString s, size_t from = 0);
		size_t rfind(MString s, size_t before = npos);
		MString substr(size_t pos, size_t len = npos);
		int compare(MString s);

		MString operator + (MString s);
		bool operator == (MString s);
		bool operator != (MString s);
		bool operator < (MString s);
		bool operator <= (MString s);
		bool operator > (MString s);
		bool operator >= (MString s);
	};
}

#endif