#          _ _   _             
#    /\/\ (_) |_| |_ ___ _ __  
#   /    \| | __| __/ _ \ '_ \ 
#  / /\/\ \ | |_| ||  __/ | | |
#  \/    \/_|\__|\__\___|_| |_|

# File:    config.mk
# Author:  Oliver Katz
# Version: 0.01-alpha
# License: Unlicensed

CXX=g++
CXXFLAGS=-g -O0 -std=c++11 -fdiagnostics-color=auto

AR=ar
ARFLAGS=rcs

RM=rm
RMFLAGS=-f

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@
