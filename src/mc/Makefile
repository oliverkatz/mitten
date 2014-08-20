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

CXXFLAGS+=-I../mptk -L../mptk

OBJ=util/CommandLineParser.o language/MittenErrorHandler.o language/MittenSource.o

all : mc

mc : $(OBJ) MC.o
	$(CXX) $(CXXFLAGS) $^ -o $@ -lMPTK

clean :
	$(RM) $(RMFLAGS) -r $(OBJ) MC.o mc MPP.o mc.dSYM