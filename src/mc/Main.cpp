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
	
	StructureParser structureParser = StructureParser("block", ";");
	structureParser.bind("scope", "{", "}", "line", ";").setEndIsParentSplit(true);
	structureParser.bind("arglist", "(", ")", "arg", ",");

	vector<Error> errors;
	AST ast = structureParser.parse(toks, errors);

	cout << ast.display() << "\n";

	return 0;
}
