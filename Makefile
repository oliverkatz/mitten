#          _ _   _             
#    /\/\ (_) |_| |_ ___ _ __  
#   /    \| | __| __/ _ \ '_ \ 
#  / /\/\ \ | |_| ||  __/ | | |
#  \/    \/_|\__|\__\___|_| |_|

# File:    config.mk
# Author:  Oliver Katz
# Version: 0.01-alpha
# License: Unlicensed

MAKE=make
MAKEFLAGS=

all :
	$(MAKE) $(MAKEFLAGS) -C src/mptk all
	$(MAKE) $(MAKEFLAGS) -C src/mc all

docs :
	$(MAKE) $(MAKEFLAGS) -C doc/MittenParsingToolkitAlgorithms all

clean :
	$(MAKE) $(MAKEFLAGS) -C src/mptk clean
	$(MAKE) $(MAKEFLAGS) -C src/mc clean
	$(MAKE) $(MAKEFLAGS) -C doc/MittenParsingToolkitAlgorithms clean