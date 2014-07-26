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

OBJ=Utils.o BooleanLiteralTagger.o CharacterLiteralTagger.o FloatingLiteralTagger.o IntegerLiteralTagger.o StringLiteralTagger.o Lexer.o AST.o ASTBuilder.o ErrorHandler.o StructureParser.o ExpressionParser.o

all : libMPTK.a

libMPTK.a : $(OBJ)
	$(AR) $(ARFLAGS) libMPTK.a $^

clean :
	$(RM) $(RMFLAGS) $(OBJ) libMPTK.a