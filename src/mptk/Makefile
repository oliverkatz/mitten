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

OBJ=Utils.o Lexer.o AST.o ASTBuilder.o Error.o StructureParser.o

all : libMPTK.a

libMPTK.a : $(OBJ)
	$(AR) $(ARFLAGS) libMPTK.a $^

clean :
	$(RM) $(RMFLAGS) $(OBJ) libMPTK.a