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

#include "StructureParser.h"

using namespace std;

namespace mitten
{
	StructureParser::Bound &StructureParser::Bound::setEndIsParentSplit(bool v)
	{
		endIsParentSplit = v;
		return *this;
	}

	StructureParser::StructureParser(string en, string sp)
	{
		globalBoundName = en;
		globalSplitName = sp;
	}

	StructureParser::Bound &StructureParser::bind(string n, string st, string e, string en, string sp)
	{
		bounds[st] = Bound(n, e, en, sp);
		boundEnds.insert(e);
		return bounds[st];
	}
	
	void StructureParser::defineMacro(string s, AST v)
	{
		semanticMacros[s] = v;
	}
	
	void StructureParser::undefineMacro(string s)
	{
		semanticMacros.erase(s);
	}
	
	bool StructureParser::isMacroDefined(string s)
	{
		return (semanticMacros.find(s) != semanticMacros.end());
	}

	AST StructureParser::parse(vector<Token> toks, ErrorHandler &e)
	{
		ASTBuilder builder;
		stack<string> boundStack;

		for (auto i : toks)
		{
			if (i.filtered())
				continue;

			if (bounds.find(i.value()) != bounds.end())
			{
				builder.append(AST::createNode(bounds[i.value()].boundName));
				builder.descend();
				builder.append(AST::createNode(bounds[i.value()].elementName));
				builder.descend();
				boundStack.push(i.value());
			}
			else if (!boundStack.empty() && bounds[boundStack.top()].end.compare(i.value()) == 0)
			{
				AST *head = &(builder.head());
				builder.ascend();
				builder.ascend();
				boundStack.pop();
				onNode(builder.head(), builder, eh);
				if (!boundStack.empty() && (head->size() > 0 && bounds[boundStack.top()].endIsParentSplit))
				{
					builder.append(AST::createNode(bounds[boundStack.top()].elementName));
					builder.descend();
				}
			}
			else if (!boundStack.empty() && bounds[boundStack.top()].split.compare(i.value()) == 0)
			{
				builder.ascend();
				onNode(builder.head(), builder, eh);
				builder.append(AST::createNode(bounds[boundStack.top()].elementName));
				builder.descend();
			}
			else if (boundEnds.find(i.value()) != boundEnds.end())
			{
				bool found = false;
				for (auto j : bounds)
				{
					if (j.second.end.compare(i.value()) == 0)
					{
						e.mismatchedStructureBounds(i, j.first, i.value());
						found = true;
						break;
					}
				}

				if (!found)
					throw runtime_error("bound set improperly configured");
			}
			else
			{
				builder.append(i);
				onNode(builder.head(), builder, eh);
			}
		}

		if (!toks.empty() && boundStack.size() > 1)
		{
			e.incompleteStructureBound(toks[0], boundStack.top(), bounds[boundStack.top()].end);
		}

		onNode(builder.root(), builder, eh);
		return builder.root();
	}
}
