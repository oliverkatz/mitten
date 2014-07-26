#include <iostream>
#include "MUnit.h"

using namespace std;
using namespace mitten;

int main()
{
	Test t = Test("test");
	t.assert(1 == 1);
	t.assert(1 == 5);
	t.assertProto("this should be true, but it isn't", false);
	if (t.write())
		cout << "could not write!\n";

	Test::read("test");

	return 0;
}