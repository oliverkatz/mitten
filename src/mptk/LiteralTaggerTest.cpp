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

/* File:    LiteralTaggerTest.cpp
 * Author:  Oliver Katz
 * Version: 0.01-alpha
 * License: BSD 2-Clause
 * ========================================================================== *
 * Unit test using MUnit.
 */

/* Changelog:
 * ========================================================================= *
 * 0.01-alpha ------------------------------------------------ July 20, 2014 *
 * Initial release.
 */

#include <iostream>
#include <MUnit.h>

#include "BooleanLiteralTagger.h"
#include "CharacterLiteralTagger.h"
#include "FloatingLiteralTagger.h"
#include "IntegerLiteralTagger.h"
#include "StringLiteralTagger.h"

using namespace std;
using namespace mitten;

int main()
{
	Test test = Test("LiteralTaggerTest");

	BooleanLiteralTagger blt;
	CharacterLiteralTagger clt;
	FloatingLiteralTagger flt;
	IntegerLiteralTagger ilt;
	StringLiteralTagger slt;

	test.assert(blt.isBooleanLiteral("true"));
	test.assert(blt.isBooleanLiteral("false"));
	test.assert(!blt.isBooleanLiteral("blah"));
	test.assert(blt.parse("true"));
	test.assert(!blt.parse("false"));

	test.assert(clt.isCharacterLiteral("'a'"));
	test.assert(!clt.isCharacterLiteral("'a"));
	test.assert(!clt.isCharacterLiteral("a'"));
	test.assert(!clt.isCharacterLiteral("a"));
	test.assert(!clt.isCharacterLiteral(""));
	test.assert(clt.isCharacterLiteral("'\\a'"));
	test.assert(clt.parse("'a'") == 'a');
	test.assert(clt.parse("'\\a'") == '\a');

	test.assert(flt.isFloatingLiteral("0"));
	test.assert(flt.isFloatingLiteral("0.1"));
	test.assert(!flt.isFloatingLiteral("0.a"));
	test.assert(flt.isFloatingLiteral("-5000"));
	test.assert(flt.isFloatingLiteral("3.5e2"));
	test.assert(!flt.isFloatingLiteral("3.5e"));
	test.assert(!flt.isFloatingLiteral("e5"));
	test.assert(flt.parse("5.0") == 5.0);
	test.assert(flt.parse("5.0e2") == 500.0);

	test.assert(ilt.isIntegerLiteral("0"));
	test.assert(!ilt.isIntegerLiteral("a"));
	test.assert(ilt.isIntegerLiteral("0x0"));
	test.assert(!ilt.isIntegerLiteral("0x"));
	test.assert(ilt.isIntegerLiteral("0x050FA"));
	test.assert(ilt.isIntegerLiteral("003"));
	test.assert(ilt.isIntegerLiteral("00"));
	test.assert(ilt.isIntegerLiteral("FFFFh"));
	test.assert(ilt.isIntegerLiteral("-25"));
	test.assert(ilt.parse("0") == 0);
	test.assert(ilt.parse("0x20") == 0x20);
	test.assert(ilt.parse("20h") == 0x20);
	test.assert(ilt.parse("033") == 033);
	test.assert(ilt.parse("-25") == -25);

	test.assert(slt.isStringLiteral("\"\""));
	test.assert(slt.isStringLiteral("\"hi\""));
	test.assert(slt.isStringLiteral("\"hello, world\\n\""));
	test.assert(!slt.isStringLiteral("\"hello, world\\n"));
	test.assert(!slt.isStringLiteral("hello, world\\n\""));
	test.assert(slt.parse("\"hi\\n\"").compare("hi\n") == 0);

	return (int)(test.write());
}
