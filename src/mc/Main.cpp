#include <iostream>
#include <MPTK.h>

using namespace std;
using namespace mptk;

int main(int argc, char *argv[])
{
	string path = argv[1];

	string page = readFile(path);

	Lexer lexer;
	lexer.deliminate("{");
	lexer.deliminate("}");
	lexer.deliminate(";");
	lexer.deliminate("(");
	lexer.deliminate(")");
	lexer.deliminate(",");
	lexer.deliminate(" ") = Filtered;
	lexer.deliminate("\t") = Filtered;
	lexer.deliminate("\n") = Filtered;
	lexer.deliminate("'", "'");
	lexer.deliminate("\"", "\"");

	vector<Token> toks = lexer.lex(page);
	for (auto i : toks)
		cout << "'" << i.value << "'\n";

	return 0;
}
