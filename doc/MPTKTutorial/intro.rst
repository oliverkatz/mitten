Introduction
============

The Mitten Parsing ToolKit (MPTK) is a simple library for parsing programming languages. Unlike a lot of other parser generators like yacc or bison, it does not generate any new code - it is a library for parsing. Also, yacc and bison handle every aspect of parsing while MPTK is more of a set of utilities for writing your own parser.

Overview
--------

The first step of parsing any language is spliting the input text into tokens. Think of this process as splitting the letters and symbols that make up a sentence into the different words and punctuation. For example::

	"hello, world"

Might be converted into::

	"hello",
	",",
	" ",
	"world"

This process is called tokenization, or *lexical analysis*. Lexical analysis is done by a *lexer*. After this is done, you can organize the tokens into a structured AST tree. For example::

	"f(x+2, 5)"

After tokenization might be structured into::

	"f",
	argument list
	{
		argument
		{
			"x",
			"+",
			"2"
		},
		argument
		{
			"5"
		}
	}

This makes working with the source code much easier and makes writing a parser much simpler. This process is called *structuring* and is done by a *structure parser*. Most parser generaters would consider structuring to be a small component of *semantic analysis*, but MPTK provides a set of semantic analysis classes that you can use to accomplish this. The first, and most important, of these is the structure parser.

Installing
----------

You can download Mitten from its GIT_ repository:

1. Download the master branch::

	$ git clone https://github.com/oliverkatz/mitten.git

2. From the download directory, go into the MPTK source directory::

	$ cd mitten/src/mptk

3. Build MPTK::

	$ make all

4. Install MPTK::

	$ sudo make install

.. _GIT: https://github.com/oliverkatz/mitten


Using MPTK in your Code
-----------------------

First you need to include the MPTK header file::

	#include <MPTK.h>

It's default download location should be */usr/include/MPTK.h*, while the rest of the MPTK headers should be stored in */usr/include/mptk*. To link the MPTK static library, use the following g++ flags::

	$ g++ some.o object.o files.o -o program -lMPTK

The static library's default location should be */usr/lib/libMPTK.a*. That's it!