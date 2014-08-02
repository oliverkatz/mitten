#include <iostream>
#include <MPTK.h>

using namespace std;
using namespace mitten;

int main(int argc, char *argv[])
{
	//string path = argv[1];

	string page = "f(2, x+2)";

	Lexer lexer;
	lexer.deliminate("{");
	lexer.deliminate("}");
	lexer.deliminate(";");
	lexer.deliminate("(");
	lexer.deliminate(")");
	lexer.deliminate(",");
	lexer.deliminate("+");
	lexer.deliminate(" ") = Filtered;
	lexer.deliminate("\t") = Filtered;
	lexer.deliminate("\n") = Filtered;
	lexer.deliminate("'", "'");
	lexer.deliminate("\"", "\"");

	vector<Token> toks = lexer.lex(page);
	for (auto i : toks)
		cout << "'" << i.value << "' ";
	cout << "\n";
	
	StructureParser structureParser = StructureParser("block", ";");
	structureParser.bind("scope", "{", "}", "line", ";").setEndIsParentSplit(true);
	structureParser.bind("arglist", "(", ")", "arg", ",");

	InternalErrorHandler eh;
	eh.setFileName("--");
	eh.setFileBody(page);
	AST res = structureParser.parse(toks, eh);
	cout << res.display() << "\n";

	if (eh.dump())
		return 1;

	ExpressionParser ep = ExpressionParser();
	ep.setExpressionBound("arglist");
	ep.setExpressionElement("arg");
	ep.setFunctionNode("function");
	ep.setOperationUnaryLeftNode("op_ul");
	ep.setOperationUnaryRightNode("op_ur");
	ep.setOperationBinaryNode("op_b");
	ep.addBinaryOperator("+");

	res = ep.parse(res, eh);
	cout << res.display() << "\n";

	if (eh.dump())
		return 2;

	return 0;
}
