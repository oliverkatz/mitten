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

OBJ=Test.o

all : libMPTK.a

libMPTK.a : $(OBJ)
	$(AR) $(ARFLAGS) libMUnit.a $^

clean :
	$(RM) $(RMFLAGS) -r $(OBJ) libMUnit.a TestUnit test.mut TestUnit.dSYM

test :
	$(CXX) $(CXXFLAGS) TestUnit.cpp -o TestUnit -L. -lMUnit