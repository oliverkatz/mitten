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

#include "Utils.h"

using namespace std;

namespace mitten
{
	/*AbstractWidthString readFile(string path, size_t width)
	{
		FILE *f = fopen(path.c_str(), "r");
		if (f == NULL)
			throw runtime_error("cannot open file for reading: "+path);

		fseek(f, 0, SEEK_END);
		long l = ftell(f);
		fseek(f, 0, SEEK_SET);

		AbstractWidthString rtn = AbstractWidthString();
		rtn.reallocate(l);
		fread((void *)rtn.data(), width, l/width, f);
		rtn.resize(l/width);

		fclose(f);
		return rtn;
	}*/

	string readFile8(string path)
	{
		ifstream f(path.c_str());
		string rtn((istreambuf_iterator<char>(f)), istreambuf_iterator<char>());
		return rtn;
	}

	string evaluateEscapeCodes(string s)
	{
		string rtn;

		for (int i = 0; i < s.size(); i++)
		{
			if (s[i] == '\\')
			{
				if (i == s.size()-1)
				{
					throw runtime_error("escape code ended prematurely");
				}
				else
				{
					if (s[i+1] == 'a')
					{
						rtn += '\a';
						i++;
					}
					else if (s[i+1] == 'b')
					{
						rtn += '\b';
						i++;
					}
					else if (s[i+1] == 'f')
					{
						rtn += '\f';
						i++;
					}
					else if (s[i+1] == 'n')
					{
						rtn += '\n';
						i++;
					}
					else if (s[i+1] == 'r')
					{
						rtn += '\r';
						i++;
					}
					else if (s[i+1] == 't')
					{
						rtn += '\t';
						i++;
					}
					else if (s[i+1] == 'v')
					{
						rtn += '\v';
						i++;
					}
					else if (s[i+1] == '\\')
					{
						rtn += '\\';
						i++;
					}
					else if (s[i+1] == '\'')
					{
						rtn += '\'';
						i++;
					}
					else if (s[i+1] == '\"')
					{
						rtn += '\"';
						i++;
					}
					else if (s[i+1] == '?')
					{
						rtn += '\?';
						i++;
					}
					else if (s[i+1] >= '0' && s[i+1] <= '7')
					{
						if (i+3 < s.size())
						{
							char tmp = stoi(s.substr(i+1, 3), NULL, 8);
							rtn += tmp;
							i += 3;
						}
						else
						{
							throw runtime_error("escape code ended prematurely");
						}
					}
					else if (s[i+1] == 'x')
					{
						if (i+3 < s.size())
						{
							char tmp = stoi(s.substr(i+2, 2), NULL, 16);
							rtn += tmp;
							i += 3;
						}
						else
						{
							throw runtime_error("escape code ended prematurely");
						}
					}
					else
					{
						throw runtime_error("unexpected character");
					}
				}
			}
			else
			{
				rtn += s[i];
			}
		}

		return rtn;
	}
}
