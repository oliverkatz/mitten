#          _ _   _             
#    /\/\ (_) |_| |_ ___ _ __  
#   /    \| | __| __/ _ \ '_ \ 
#  / /\/\ \ | |_| ||  __/ | | |
#  \/    \/_|\__|\__\___|_| |_|

include ../config.mk

all : 
	$(DOXYGEN) $(DOXYFLAGS) Doxyfile
	@#make -C latex

clean :
	$(RM) $(RMFLAGS) -r html latex
