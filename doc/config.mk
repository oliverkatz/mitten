#          _ _   _             
#    /\/\ (_) |_| |_ ___ _ __  
#   /    \| | __| __/ _ \ '_ \ 
#  / /\/\ \ | |_| ||  __/ | | |
#  \/    \/_|\__|\__\___|_| |_|

# File:    config.mk
# Author:  Oliver Katz
# Version: 0.01-alpha
# License: Unlicensed

TEX=pdflatex
TEXFLAGS=

DOXYGEN=doxygen
DOXYFLAGS=

RM=rm
RMFLAGS=-f

%.pdf : %.tex
	$(TEX) $(TEXFLAGS) $<
