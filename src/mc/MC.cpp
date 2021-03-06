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
#include <MPTK.h>

#include "util/CommandLineParser.h"
#include "language/MittenErrorHandler.h"
#include "language/MittenSource.h"

using namespace std;
using namespace mitten;

int main(int argc, char *argv[])
{
	CommandLineParser clp;

	clp.name = "Mitten Compiler (MC)";
	clp.version = "0.01-alpha";
	clp.copyright = "Copyright 2014 Oliver Katz";

	clp["I"].setDescription("Adds its argument to the include path.").setType("path").addExample("-I.").addExample("-I/opt/usr/include").addValue("/usr/include").requestArgument();
	clp["o"].setDescription("Sets the output file path.").setType("path").addExample("-o a.out").requestArgument().requestUseNextArgument();

	if (clp.parse(argc, argv))
	{
		return 1;
	}

	if (clp.freeArguments.empty())
	{
		cerr << "error: no input files\n";
		return 2;
	}

	for (auto i : clp.freeArguments)
	{
		MittenSource source = MittenSource::fromFile(i);

		if (source.compile())
		{
			return 3;
		}
	}

	return 0;
}
