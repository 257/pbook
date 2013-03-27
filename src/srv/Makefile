VPATH          = $(wildcard ./*)
SUBDIRS        = .

MAKEFLAGS      = --no-print-directory
PREFIX        := $(PWD)
CFLAGS         = -I$(include_dirs) \
		-g \
		-Wall

EXENAME       = pbd
objects       = $(EXENAME).o

include_dirs  = ../include
objects       = \
		skts.o \
		pbkd.o

pbkd:         $(objects)
	@printf "  DONE:\tpbkd.o\n"
.PHONY:         clean cleano distclean
clean:
	-rm $(EXENAME)
cleano:
	rm $(objects)
distclean:
	rm $(EXENAME) $(objects)
	
