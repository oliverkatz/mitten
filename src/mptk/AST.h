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

#ifndef __MITTEN_AST_H
#define __MITTEN_AST_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>

#include "Token.h"

namespace mitten
{
	/*! \brief Class for storing Abstract Syntax Tree (AST) node data.
	 */
	class AST
	{
	protected:
		bool isBranched; //! True only if the current node has branches.
		Token leafValue; //! The token to use if the current node is a leaf.
		std::string nameValue; //! The name of the node if it is a branch.
		std::vector<AST> branchValues; //! The branches if the current node is not a leaf.

	public:
		/*! \brief Constructor.
		 * Initializes an empty AST node.
		 */
		AST() : isBranched(false) {}
	
		/*! \brief Constructor.
		 * Creates an AST leaf node from token \p t.
		 */
		static AST createLeaf(Token t);

		/*! \brief Constructor.
		 * Creates an AST branch node with name \p n.
		 */
		static AST createNode(std::string n);

		/*! \brief Checks if the node is a leaf. 
		 */
		bool isLeaf();

		/*! \brief Checks if the node is a branch. 
		 */
		bool isBranch();

		/*! \brief Gets a reference to the name of the node.
		 */
		std::string &name();

		/*! \brief Gets a reference to the leaf's token value.
		 */
		Token &leaf();

		/*! \brief Returns the number of branches, 0 if none.
		 */
		size_t size();

		/*! \brief Gets a reference to the nth branch.
		 */
		AST &operator [] (size_t n);

		/*! \brief Creates a begin iterator.
		 */
		std::vector<AST>::iterator begin();

		/*! \brief Creates an end iterator.
		 */
		std::vector<AST>::iterator end();

		/*! \brief Retusn a reference to the rightmost node of the AST.
		 */
		AST &rightmost();

		/*! \brief Appends a branch node as a branch.
		 */
		void append(AST a);

		/*! \brief Appends a leaf node as a branch.
		 */
		void append(Token t);

		/*! \brief Displays the AST.
		 * \returns Formatted string representing the AST.
		 */
		std::string display();
	};
}

#endif