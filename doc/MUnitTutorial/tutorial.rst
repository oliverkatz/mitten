Unit Testing
============

The principle of unit testing is to test each unit of code to make sure it is functioning correctly. The MUnit library allows you to write unit tests and display the results easily. You need to write the test as a separate program. This program runs the test and then handles the results. The results can be stored in a *.mut file, read from a *.mut file, or printed out to a user with the MUnit library. *.mut files are human-readable, so they themselves can be used to tell the results of a test.

Unit tests consist of a list of assertions - predicates - that can be either true or false. If all the assertions in a test are true, the test passes. If any are false, the entire test fails. This ensures that the unit of source code being tested functions properly in all aspects.

Assertions
==========

The MUnit library declares its own version of the *assert* macro, normally defined within *assert.h*. If you do not wish to use this, for conflicts with *assert.h*, you can include the MUnit library as follows: ::

	#include <MUnit.h>
	#undef assert

	// you can now safely include assert.h with no conflicts
	#include <assert.h>

If you wish to use this macro, as is recommended, you can include MUnit as follows: ::

	#include <MUnit.h>

The results of a unit test are stored in an object of the *Test* class. Let us create a new test in a separate program to the tested code. ::

	Test t = Test("exampleUnitTest");

This means that the results will be stored in *exampleUnitTest.mut*. We can now add assertions to this test. For example, let us say that we are testing C++ to make sure that integer math works correctly. Even though we can safely assume that 2+2 is 4, we should probably check to make sure. ::

	t.assert(2+2 == 4);

Now, let us write the results to a file. ::

	if (t.write())
		cout << "error: could not write results to file!\n";

Review of the file should show that the test passed. If not, please send an angry email to the provider of your C++ compiler with the following words: "All broke. No work. Very bad." This is industry slang for fix your broken C++ compiler.

If you want to read the results back to access them pragmatically, we can write: ::

	Test t2 = Test::read("exampleUnitTest");

Pragmatic Access
================

You can access all the assertions in a test as follows: ::

	for (auto i : t)
	{
		cout << "Assertion '" << i.name << "': " << i.result << "\n";
	}

This will result in the following output: ::

	Assertion '2+2 == 4': 1