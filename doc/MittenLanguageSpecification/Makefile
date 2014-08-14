#          _ _   _             
#    /\/\ (_) |_| |_ ___ _ __  
#   /    \| | __| __/ _ \ '_ \ 
#  / /\/\ \ | |_| ||  __/ | | |
#  \/    \/_|\__|\__\___|_| |_|

include ../config.mk

all : 
	$(TEX) $(TEXFLAGS) MittenLanguageSpecification.tex

clean :
	$(RM) $(RMFLAGS) $(shell echo *.aux *.log *.pdf *.toc *.out)
