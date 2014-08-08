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

all : 
	$(TEX) $(TEXFLAGS) TheMittenProgrammingLanguage.tex

clean :
	$(RM) $(RMFLAGS) $(shell echo *.aux *.log *.pdf *.toc *.out)
