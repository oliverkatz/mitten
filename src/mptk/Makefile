#          _ _   _             
#    /\/\ (_) |_| |_ ___ _ __  
#   /    \| | __| __/ _ \ '_ \ 
#  / /\/\ \ | |_| ||  __/ | | |
#  \/    \/_|\__|\__\___|_| |_|

# File:    config.mk
# Author:  Oliver Katz
# Version: 0.01-alpha
# License: Unlicensed

include ../config.mk

CXXFLAGS+=-I../munit -L../munit -L.

OBJ=AbstractWidthString.o Utils.o BooleanLiteralTagger.o CharacterLiteralTagger.o FloatingLiteralTagger.o IntegerLiteralTagger.o StringLiteralTagger.o SymbolTagger.o Token.o Lexer.o AST.o ASTBuilder.o ErrorHandler.o StructureParser.o ExpressionParser.o Reconstruction.o
TEST=AbstractWidthStringTest UtilsTest LiteralTaggerTest

all : libMPTK.a

libMPTK.a : $(OBJ)
	$(AR) $(ARFLAGS) libMPTK.a $^

clean :
	$(RM) $(RMFLAGS) $(OBJ) libMPTK.a
	for i in $(TEST); do $(RM) $(RMFLAGS) $$i $$i.mut; $(RM) $(RMFLAGS) -r $$i.dSYM; done

test : $(TEST)
	@for i in $(TEST); do echo "Running $$i:"; ./$$i; echo; done

AbstractWidthStringTest : AbstractWidthStringTest.cpp libMPTK.a
	$(CXX) $(CXXFLAGS) $< -o $@ -lMUnit -lMPTK

UtilsTest : UtilsTest.cpp libMPTK.a
	$(CXX) $(CXXFLAGS) $< -o $@ -lMUnit -lMPTK

LiteralTaggerTest : LiteralTaggerTest.cpp libMPTK.a
	$(CXX) $(CXXFLAGS) $< -o $@ -lMUnit -lMPTK