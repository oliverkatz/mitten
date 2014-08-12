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

#include "Test.h"

using namespace std;

namespace mitten
{
	Test Test::read(string n)
	{
		ifstream f(string(n+".mut").c_str());
		string page((istreambuf_iterator<char>(f)),
		            istreambuf_iterator<char>());

		if (page.find("\n") == string::npos || page.find("\n") == page.size()-1)
		{
			cerr << "MUnit: invalid format (no newlines)\n";
			return Test();
		}

		Test rtn = Test();

		if (page.substr(0, page.find("\n")).compare("MUnit 0.01-alpha") == 0)
		{
			page = page.substr(page.find("\n")+1);

			if (page.find("\n") == string::npos || page.find("\n") == page.size()-1)
			{
				cerr << "MUnit: expected field not provided: Test\n";
				return Test();
			}
			else
			{
				rtn.name = page.substr(11, page.find("\n")-11);
				page = page.substr(page.find("\n")+1);
			}

			if (page.find("\n") == string::npos || page.find("\n") == page.size()-1)
			{
				cerr << "MUnit: expected field not provided: Result\n";
				return Test();
			}
			else
			{
				rtn.currentlyPassing = stoi(page.substr(11, page.find("\n")-11));
				page = page.substr(page.find("\n")+1);
			}

			if (page.find("\n") == string::npos || page.find("\n") == page.size()-1)
			{
				cerr << "MUnit: expected field not provided: Timestamp\n";
				return Test();
			}
			else
			{
				page = page.substr(page.find("\n")+2);
			}

			if (page.find("\n") == string::npos || page.find("\n") == page.size()-1)
			{
				cerr << "MUnit: expected table split not found\n";
				return Test();
			}
			else
			{
				page = page.substr(page.find("\n")+1);
			}

			if (page.find("\n") == string::npos || page.find("\n") == page.size()-1)
			{
				cerr << "MUnit: expected table header not found\n";
				return Test();
			}
			else
			{
				page = page.substr(page.find("\n")+1);
			}

			if (page.find("\n") == string::npos || page.find("\n") == page.size()-1)
			{
				cerr << "MUnit: expected table split not found\n";
				return Test();
			}
			else
			{
				page = page.substr(page.find("\n")+1);
			}

			while (!page.empty() && page[0] != '+')
			{
				if (page.find("|") == string::npos)
				{
					cerr << "MUnit: expected table divider not found\n";
					return Test();
				}
				else if (page.find("\n") == string::npos)
				{
					cerr << "MUnit: table ended prematurely\n";
					return Test();
				}

				string name = page.substr(2, page.substr(2).find("|")).substr(0, page.find("\n"));
				while (name.back() == ' ')
					name = name.substr(0, name.size()-1);
				string result = page.substr(page.substr(1).find("|")+1);

				rtn.assertProto(name, result[0] == '1');

				page = page.substr(page.find("\n")+1);
			}
		}
		else
		{
			cerr << "MUnit: no support for version: " << page.substr(0, page.find("\n")) << "\n";
			return Test();
		}

		return rtn;
	}

	void Test::assertProto(string n, bool r)
	{
		data.push_back(Assertion(n, r));
		if (r == false)
			currentlyPassing = false;
		if (n.size() > longestName)
			longestName = n.size();

		cout << "  " << n << "... " << (r ? "\033[0;32mpassed.\033[0;0m" : "\033[0;31mfailed!\033[0;0m") << "\n";
	}

	bool Test::pass()
	{
		return currentlyPassing;
	}

	bool Test::write()
	{
		ofstream f;
		f.open(name+".mut");
		if (!f.good())
			return true;

		f << "MUnit 0.01-alpha\n";
		f << "Test:      " << name << "\n";
		f << "Result:    " << (currentlyPassing ? "1" : "0") << "\n";

		time_t rawtime;
		time (&rawtime);
		f << "Timestamp: " << asctime(localtime(&rawtime)) << "\n";

		int n = longestName+1;
		if (n < 5)
			n = 5;

		f << "+-" << string(n, '-') << "+--------+\n";
		f << "| Name" << string(n-4, ' ') << "| Result |\n";
		f << "+-" << string(n, '-') << "+--------+\n";
		for (auto i : data)
			f << "| " << i.name << string(n-i.name.size(), ' ') << "| " << (i.result ? "1" : "0") << "      |\n";
		f << "+-" << string(n, '-') << "+--------+\n\n";

		f.close();
		return false;
	}

	size_t Test::size()
	{
		return data.size();
	}

	list<Assertion>::iterator Test::begin()
	{
		return data.begin();
	}

	list<Assertion>::iterator Test::end()
	{
		return data.end();
	}
}
