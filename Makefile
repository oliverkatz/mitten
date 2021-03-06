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
	$(MAKE) $(MAKEFLAGS) -C src/munit all
	$(MAKE) $(MAKEFLAGS) -C src/mptk all
	@#$(MAKE) $(MAKEFLAGS) -C src/mdoc all
	$(MAKE) $(MAKEFLAGS) -C src/mc all

docs :
	$(MAKE) $(MAKEFLAGS) -C doc/MittenParsingToolkitAlgorithms all
	$(MAKE) $(MAKEFLAGS) -C doc/TheMittenProgrammingLanguage all
	$(MAKE) $(MAKEFLAGS) -C doc/MittenLanguageSpecification all
	$(MAKE) $(MAKEFLAGS) -C doc/MPTKTutorial html
	$(MAKE) $(MAKEFLAGS) -C doc/MPTKReference all
	$(MAKE) $(MAKEFLAGS) -C doc/MUnitTutorial html

clean :
	$(MAKE) $(MAKEFLAGS) -C src/munit clean
	$(MAKE) $(MAKEFLAGS) -C src/mptk clean
	@#$(MAKE) $(MAKEFLAGS) -C src/mdoc clean
	$(MAKE) $(MAKEFLAGS) -C src/mc clean
	$(MAKE) $(MAKEFLAGS) -C doc/MittenParsingToolkitAlgorithms clean
	$(MAKE) $(MAKEFLAGS) -C doc/TheMittenProgrammingLanguage clean
	$(MAKE) $(MAKEFLAGS) -C doc/MittenLanguageSpecification clean
	$(MAKE) $(MAKEFLAGS) -C doc/MPTKTutorial clean
	$(MAKE) $(MAKEFLAGS) -C doc/MPTKReference clean
	$(MAKE) $(MAKEFLAGS) -C doc/MUnitTutorial clean