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

#include <iostream>
#include <MUnit.h>

#include "../Core/AbstractWidthString.h"

using namespace std;
using namespace mitten;

int main()
{
	Test test = Test("AbstractWidthStringTest");

	AbstractWidthString tmp8 = AbstractWidthString::fromCString8("hello, world");
	AbstractWidthString tmp16 = AbstractWidthString::fromCString16(u"hello, world");
	AbstractWidthString tmp32 = AbstractWidthString::fromCString32(U"hello, world");
	AbstractWidthString slice = AbstractWidthString(tmp8);

	test.assert(tmp32.toString8().compare("hello, world") == 0);
	test.assert(tmp32[0] == 'h');
	test.assert(slice.isSlice());
	test.assert(tmp32.isResource());
	test.assert(tmp32.size() == string("hello, world").size());
	test.assert(tmp32.width() == 4);
	test.assert(tmp32.memsize() == string("hello, world").size()*4);
	tmp32.reallocate(1024);
	tmp32.resize(1024);
	test.assert(tmp32.size() == string("hello, world").size());
	test.assert(tmp32.toString8().compare("hello, world") == 0);
	tmp32.resize(1);
	test.assert(tmp32.toString8().compare("h") == 0);
	test.assert(tmp8.compare(tmp16) == 0);
	test.assert(tmp8 == tmp16);

	tmp8.append(AbstractWidthString::fromString8("hi"));
	test.assert(tmp8.toString8().compare("hello, worldhi") == 0);
	test.assert(tmp8.substr(1).toString8().compare("ello, worldhi") == 0);
	test.assert(tmp8.substr(1, 2).toString8().compare("el") == 0);

	AbstractWidthString tmp8b = AbstractWidthString::fromString8("hi");
	tmp8b.insert(1, AbstractWidthString::fromString8("_"));
	test.assert(tmp8b.toString8().compare("h_i") == 0);
	tmp8b.erase(1, 1);
	test.assert(tmp8b.toString8().compare("hi") == 0);

	test.assert(tmp16.find(AbstractWidthString::fromString8("e")) == 1);
	test.assert(tmp16.find(AbstractWidthString::fromString8("_")) == AbstractWidthString::npos);
	test.assert(tmp16.rfind(AbstractWidthString::fromString8("e")) == 1);

	return (int)(test.write());
}