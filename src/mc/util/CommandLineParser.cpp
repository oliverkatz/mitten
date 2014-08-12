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

#include "CommandLineParser.h"

using namespace std;

namespace mitten
{
	CommandLineParser::Option &CommandLineParser::Option::requestArgument()
	{
		takesArgument = true;
		return *this;
	}

	CommandLineParser::Option &CommandLineParser::Option::requestUseNextArgument()
	{
		useNextArgument = true;
		return *this;
	}

	CommandLineParser::Option &CommandLineParser::Option::setDescription(string d)
	{
		description = d;
		return *this;
	}

	CommandLineParser::Option &CommandLineParser::Option::setType(string t)
	{
		type = t;
		return *this;
	}

	CommandLineParser::Option &CommandLineParser::Option::addExample(string e)
	{
		examples.push_back(e);
		return *this;
	}

	CommandLineParser::Option &CommandLineParser::Option::addValue(string v)
	{
		values.push_back(v);
		return *this;
	}

	CommandLineParser::Option &CommandLineParser::operator [] (string s)
	{
		if (s.compare("h") == 0)
		{
			throw runtime_error("option '-h' is reserved for help.");
		}
		else if (s.compare("V") == 0)
		{
			throw runtime_error("option '-V' is reserved for version.");
		}
		else if (options.find(s.size()) == options.end() || options[s.size()].find(s) == options[s.size()].end())
		{
			options[s.size()][s] = Option();
			if (s.size() > maxOptionLength)
				maxOptionLength = s.size();
		}

		return options[s.size()][s];
	}

	bool CommandLineParser::parse(int argc, char *argv[])
	{
		bool errors = false;

		if (name.empty())
		{
			name = argv[0];
			if (name.find("/") != string::npos)
				name = name.substr(name.rfind("/")+1);
		}

		if (usage.empty())
		{
			usage = "[OPTIONS]";
		}

		for (int i = 1; i < argc; i++)
		{
			if (argv[i][0] == '-')
			{
				string tmp = string(argv[i]).substr(1);

				if (tmp.compare("h") == 0)
				{
					cout << "\033[1;32m" << name << " \033[0;0m" << version << "\n";
					if (!copyright.empty())
						cout << copyright << "\n\n";
					if (!description.empty())
						cout << description << "\n\n";
					cout << "usage: \033[1;32m" << argv[0] << "\033[0;0m \033[0;35m" << usage << "\033[0;0m\n\n";
					cout << "Options:\n";
					for (auto i : options)
					{
						for (auto j : i.second)
						{
							if (j.second.takesArgument)
							{
								if (j.second.useNextArgument)
								{
									cout << "\033[1;35m-" << j.first << " <" << j.second.type << ">\n";
								}
								else
								{
									cout << "\033[1;35m-" << j.first << "<" << j.second.type << ">\n";
								}
							}
							else
							{
								cout << "\033[1;35m-" << j.first << "\n";
							}

							cout << "\033[0;0m  " << j.second.description << "\n";
							if (!j.second.examples.empty())
							{
								cout << "    For example:\n";
								for (auto k : j.second.examples)
								{
									cout << "      \033[0;32m" << k << "\033[0;0m\n";
								}
							}

							cout << "\n";
						}
					}

					cout << "\033[1;35m-h\033[0;0m\n";
					cout << "  Display this help.\n";
					cout << "\n";
					cout << "\033[1;35m-V\033[0;0m\n";
					cout << "  Display version info.\n";
					cout << "\n";

					return true;
				}
				else if (tmp.compare("V") == 0)
				{
					cout << "\033[1;32m" << name << "\033[0;0m " << version << "\n";
					if (!copyright.empty())
						cout << copyright << "\n";

					return true;
				}
				else
				{
					bool found = false;

					for (int j = maxOptionLength; j > 0; j--)
					{
						if (j <= tmp.size())
						{
							if (options[j].find(tmp.substr(0, j)) != options[j].end())
							{
								Option &o = options[j][tmp.substr(0, j)];
								found = true;

								if (o.takesArgument)
								{
									if (o.useNextArgument)
									{
										if (i >= argc-1)
										{
											cerr << "error: option expected an argument: -" << tmp.substr(0, j) << "\n";
											errors = true;
										}
										else
										{
											o.values.push_back(argv[i+1]);
											i++;
										}
									}
									else
									{
										o.values.push_back(tmp.substr(j));
									}
								}
							}
						}
					}

					if (!found)
					{
						cerr << "error: no such option: " << tmp << "\n";
						errors = true;
					}
				}
			}
			else
			{
				freeArguments.push_back(argv[i]);
			}
		}

		return errors;
	}
}
