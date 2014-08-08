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

/* File:    CommandLineParser.h
 * Author:  Oliver Katz
 * Version: 0.01-alpha
 * License: BSD 2-Clause
 * ========================================================================== *
 * Command-line parser for the Mitten Compiler (MC).
 */

/* Changelog:
 * ========================================================================= *
 * 0.01-alpha ------------------------------------------------ July 20, 2014 *
 * Initial release.
 */

#ifndef __MITTEN_UTILS_COMMAND_LINE_PARSER_H
#define __MITTEN_UTILS_COMMAND_LINE_PARSER_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

namespace mitten
{
	class CommandLineParser
	{
	public:
		typedef struct Option
		{
			std::string description;
			std::string type;
			std::vector<std::string> examples;
			bool takesArgument;
			bool useNextArgument;
			bool flagged;
			std::vector<std::string> values;

			Option() : type("value"), takesArgument(false), useNextArgument(false), flagged(false) {}

			Option &requestArgument();
			Option &requestUseNextArgument();
			Option &setDescription(std::string d);
			Option &setType(std::string t);
			Option &addExample(std::string e);
			Option &addValue(std::string v);
		} Option;

	protected:
		std::unordered_map<int, std::unordered_map<std::string, Option> > options;
		int maxOptionLength;

	public:
		std::string name, version, copyright, description, usage;
		std::vector<std::string> freeArguments;

		CommandLineParser() : maxOptionLength(0) {}

		Option &operator [] (std::string s);

		bool parse(int argc, char *argv[]);
	};
}

#endif