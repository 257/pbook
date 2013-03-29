VPATH          = $(wildcard ./*)

MAKEFLAGS      = --no-print-directory
PREFIX        := $(PWD)
CFLAGS         = -I$(include_dirs) \
		-g \
		-Wall


#include_dirs  = ../include
objects       = \
		skts.o \
		pbkd.o

pbkd:         $(objects)
	@printf "  DONE:  pbkd.o\n"
.PHONY:         clean cleano distclean
clean:
	-rm $(objects)
distclean:
	$(MAKE) -C $(PREFIX) clean

	
