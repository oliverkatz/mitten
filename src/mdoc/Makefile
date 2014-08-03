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

CXXFLAGS+=-I../mptk -L../mptk -L.

OBJ=DocumentParser.o

all : libMDoc.a mdocdump

libMDoc.a : $(OBJ)
	$(AR) $(ARFLAGS) libMDoc.a $^

mdocdump : $(OBJ) MDocDump.o
	$(CXX) $(CXXFLAGS) $^ -o $@ -lMPTK

clean :
	$(RM) $(RMFLAGS) $(OBJ) libMDoc.a MDocDump.o mdocdump