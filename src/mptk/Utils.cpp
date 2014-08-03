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

/* File:    Utils.cpp
 * Author:  Oliver Katz
 * Version: 0.01-alpha
 * License: BSD 2-Clause
 * ========================================================================== *
 * Various utility functions used by MPTK.
 */

/* Changelog:
 * ========================================================================= *
 * 0.01-alpha ------------------------------------------------ July 20, 2014 *
 * Initial release.
 */

#include "Utils.h"

using namespace std;

namespace mitten
{
	string readFile(string path)
	{
		ifstream f(path.c_str());
		string str((istreambuf_iterator<char>(f)),
		            istreambuf_iterator<char>());
		return str;
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
							/*char d16 = s[i+2]-'0';
							switch(s[i+2])
							{
								case 'a': d16 = 10; break;
								case 'A': d16 = 10; break;
								case 'b': d16 = 11; break;
								case 'B': d16 = 11; break;
								case 'c': d16 = 12; break;
								case 'C': d16 = 12; break;
								case 'd': d16 = 13; break;
								case 'D': d16 = 13; break;
								case 'e': d16 = 14; break;
								case 'E': d16 = 14; break;
								case 'f': d16 = 15; break;
								case 'F': d16 = 15; break;
								default: break;
							}

							char d1 = s[i+3]-'0';
							switch(s[i+3])
							{
								case 'a': d1 = 10; break;
								case 'A': d1 = 10; break;
								case 'b': d1 = 11; break;
								case 'B': d1 = 11; break;
								case 'c': d1 = 12; break;
								case 'C': d1 = 12; break;
								case 'd': d1 = 13; break;
								case 'D': d1 = 13; break;
								case 'e': d1 = 14; break;
								case 'E': d1 = 14; break;
								case 'f': d1 = 15; break;
								case 'F': d1 = 15; break;
								default: break;
							}

							char tmp = d1 + d16*16;*/
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

	string stripString(string s)
	{
		int o = 0;
		int n = s.size();

		while ((s[o] == ' ' || s[o] == '\t' || s[o] == '\n') && n > 0)
		{
			o++;
			n--;
		}

		while ((s[o+n-1] == ' ' || s[o+n-1] == '\t' || s[o+n-1] == '\n') && n > 0)
		{
			n--;
		}

		return s.substr(o, n);
	}
}
