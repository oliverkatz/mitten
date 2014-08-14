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

OBJ=Core/AST.o Core/ASTBuilder.o Core/ErrorHandler.o Core/Reconstruction.o Core/Token.o Core/Utils.o \
	Lexing/Latin/BooleanLiteralTagger.o Lexing/Latin/CharacterLiteralTagger.o Lexing/Latin/FloatingLiteralTagger.o Lexing/Latin/IntegerLiteralTagger.o Lexing/Latin/StringLiteralTagger.o Lexing/Latin/SymbolTagger.o \
	Lexing/Lexer.o \
	Parsing/ExpressionParser.o Parsing/StructureParser.o \

all : libMPTK.a

libMPTK.a : $(OBJ)
	$(AR) $(ARFLAGS) libMPTK.a $^

clean :
	$(RM) $(RMFLAGS) $(OBJ) libMPTK.a Test/AbstractWidthStringTest Test/LiteralTaggerTest Test/UtilsTest $(shell rm -rf *.mut Test/*.mut Test/*.dSYM)

tests : Test/LiteralTaggerTest Test/UtilsTest
	./Test/LiteralTaggerTest
	./Test/UtilsTest

Test/UtilsTest : Test/UtilsTest.cpp libMPTK.a
	$(CXX) $(CXXFLAGS) $< -o $@ -lMUnit -lMPTK

Test/LiteralTaggerTest : Test/LiteralTaggerTest.cpp libMPTK.a
	$(CXX) $(CXXFLAGS) $< -o $@ -lMUnit -lMPTK