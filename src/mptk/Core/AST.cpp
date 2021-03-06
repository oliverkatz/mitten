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

#include "AST.h"

using namespace std;

namespace mitten
{
	AST AST::createLeaf(Token t)
	{
		AST tmp;
		tmp.isBranched = false;
		tmp.leafValue = t;
		return tmp;
	}

	AST AST::createNode(string n)
	{
		AST tmp;
		tmp.isBranched = true;
		tmp.nameValue = n;
		return tmp;
	}

	bool AST::isLeaf()
	{
		return !isBranched;
	}

	bool AST::isBranch()
	{
		return isBranched;
	}

	string &AST::name()
	{
		return nameValue;
	}

	Token &AST::leaf()
	{
		if (isBranched)
			throw runtime_error("cannot get leaf value of branched AST node");
		return leafValue;
	}

	size_t AST::size()
	{
		if (!isBranched)
			throw runtime_error("cannot get size of AST leaf");
		return branchValues.size();
	}

	AST &AST::operator [] (size_t n)
	{
		if (!isBranched)
			throw runtime_error("cannot get element from AST leaf");
		return branchValues[n];
	}

	vector<AST>::iterator AST::begin()
	{
		if (!isBranched)
			throw runtime_error("cannot get iterator for AST leaf");
		return branchValues.begin();
	}

	vector<AST>::iterator AST::end()
	{
		if (!isBranched)
			throw runtime_error("cannot get iterator for AST leaf");
		return branchValues.end();
	}

	AST &AST::rightmost()
	{
		if (!isBranched || branchValues.empty())
			return *this;
		else
			return branchValues.back().rightmost();
	}

	void AST::append(AST a)
	{
		branchValues.push_back(a);
	}

	void AST::append(Token t)
	{
		append(createLeaf(t));
	}

	string AST::display()
	{
		stringstream ss;

		if (isBranched)
		{
			ss << "(" << nameValue << ":";
			for (auto i : branchValues)
				ss << " " << i.display();
			if (branchValues.empty())
				ss << "null";
			ss << ")";
		}
		else
		{
			ss << "'" << leafValue.value() << "'";
		}

		return ss.str();
	}
}
