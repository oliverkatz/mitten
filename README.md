Mitten 0.01-alpha
=================

Mitten is a high-level programming language intended for use in large projects. It is object-oriented, but has the power of some functional programming features. It runs natively for efficency, but it implements an automatic memory management system without relying on garbage collection. Here are some of Mitten's features:
  * Namespaces and Classes with a predictable symbol naming convention, so you don't need an unmangler to access symbols from C.
  * Functional programming features such as currying and higher-order functions.
  * An extended standard library with all the necesary data types and algorithms.
  * Ability to dynamically compile source code and generate functions from the Mitten IR API.
  * Automatic documentation generation.
  * Direct (no bindings required) interfacing with C.

Mitten is comprised of a set of programs and libraries, as well as extensive documentation (i.e. the language specification). The most important library contained within this project is the Mitten Parsing ToolKit (MPTK). This is what Mitten uses to parse its source code. Although MPTK is currently only used for Mitten, it is applicable to any programming language.

Todo for MPTK 0.02-alpha
------------------------
* Add character width abstraction for 8, 16, and 32 bit character encodings.
* Decrease TokenVector class's memory footprint (proposed method uses ~20% of original memory).
* Decrease AST class's memory footprint (proposed method uses ~50% of original memory).
* Add indent parser.
