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

/* File:    AST.h
 * Author:  Oliver Katz
 * Version: 0.01-alpha
 * License: BSD 2-Clause
 * ========================================================================== *
 * Abstract Syntax Tree (AST) data is stored in this class.
 */

/* Changelog:
 * ========================================================================= *
 * 0.01-alpha ------------------------------------------------ July 20, 2014 *
 * Initial release.
 */

#ifndef __MPTK_AST_H
#define __MPTK_AST_H

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

#include "Token.h"

namespace mptk
{
	class AST
	{
	protected:
		bool isBranched;
		Token leafValue;
		std::string nameValue;
		std::vector<AST> branchValues;

	public:
		AST() : isBranched(false) {}
	
		static AST createLeaf(Token t);
		static AST createNode(std::string n);

		std::string &name();
		Token &leaf();
		size_t size();
		AST &operator [] (size_t n);
		std::vector<AST>::iterator begin();
		std::vector<AST>::iterator end();

		void append(AST a);
		void append(Token t);
	};
}

#endif