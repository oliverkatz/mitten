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

#ifndef __MITTEN_STRUCTURE_PARSER_H
#define __MITTEN_STRUCTURE_PARSER_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stdexcept>

#include "../Core/Token.h"
#include "../Core/AST.h"
#include "../Core/ASTBuilder.h"
#include "../Core/ErrorHandler.h"

namespace mitten
{
	/*! \brief Parser which parses initial structure from a token vector to an AST.
	 * Uses a combination of bounds and splits to parse the tokens into a tree structure. See the MPTK Algorithms pamphlet for more details.
	 */
	class StructureParser
	{
	protected:
		/*! \brief Declaration for a bound/split pairing.
		 * Contains the end point, the split point, and the names for both the bound and an element of the bound. The start point is not given because Bound declarations are organized by start point.
		*/
		typedef struct Bound
		{
			std::string end; //! End-point token value.
			std::string split; //! Split-point token value.
			std::string boundName; //! AST node name for the bound.
			std::string elementName; //! AST node name for an element of the bound.
			bool endIsParentSplit; //! Set to true to enable end-is-parent-split. See the MPTK Algorithms pamphlet for more details.

			/*! \brief Constructor.
			 * Initializes an empty bound.
			 */
			Bound() : endIsParentSplit(false) {}

			/*! \brief Constructor.
			 * Initializes a bound with no split.
			 */
			Bound(std::string n, std::string e) : boundName(n), end(e) {}

			/*! \brief Constructor.
			 * Initializes a full bound/split pairing.
			 */
			Bound(std::string n, std::string e, std::string en, std::string s) : boundName(n), end(e), elementName(en), split(s) {}

			/*! \brief Configures the end-is-parent-split option.
			 * Can be used easily, as references to bound declarations are returned by the bind method of the parent class.
			 */
			Bound &setEndIsParentSplit(bool v);
		} Bound;

		std::string globalBoundName; //! AST node name for the global bound (often 'global').
		std::string globalSplitName; //! AST node name for the global bound element (i.e. a line of code).
		std::unordered_map<std::string, Bound> bounds; //! List of bounds sorted by start-point.
		std::unordered_set<std::string> boundEnds; //! Set of all bound end-points - used for error checking.

	public:
		/*! \brief Constructor.
		 * Creates a new structure parser with no bounds.
		 * \param en Global node name.
		 * \param sp Global element node name.
		 */
		StructureParser(std::string en = "", std::string sp = "");

		/*! \brief Declares a new bound.
		 * Adds a bound with specified configuration to the bound declaration map.
		 * \param n Node name.
		 * \param st Start point.
		 * \param e End point.
		 * \param en Node name.
		 * \param sp Node element name.
		 * \returns A reference to the newly created bound declaration.
		 */
		Bound &bind(std::string n, std::string st, std::string e, std::string en = "", std::string sp = "");

		/*! \brief Runs parser.
		 * Requires the use of an input token vector and an error handler with which to store errors.
		 * \param toks Input token vector.
		 * \param e Error handler to use.
		 * \returns Resultant AST.
		 */
		AST parse(std::vector<Token> toks, ErrorHandler &e);
	};
}

#endif