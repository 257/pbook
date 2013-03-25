VPATH          = pbookd
SUBDIRS        = .

MAKEFLAGS      = --no-print-directory
PREFIX        := $(PWD)
CFLAGS         = -I$(include_dirs) \
		-g \
		-Wall

EXENAME       = pbd
objects       = $(EXENAME).o

include_dirs  = ./include
objects       = \
		pbd.o

pbd:         
	cc $(CFLAGS) -c $@.c


.PHONY:         clean
clean:
	        rm $(EXENAME) $(objects)
