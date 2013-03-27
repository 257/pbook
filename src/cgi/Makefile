VPATH          = $(wildcard ./*)
SUBDIRS        = .

MAKEFLAGS      = --no-print-directory
PREFIX        := $(PWD)
CFLAGS         = -I$(include_dirs) \
		-g \
		-Wall

include_dirs  = ../include
objects       = \
		fline.o \
		pb_limits.o \
		btree.o \
		cgigetval.o \
		pbkc.o \
		sktc.o \
		htmlf.o \
		xctod.o

pbkc:           $(objects)
	cc -o $@ $(objects) && $(MAKE) -C . cleano
	
	

cgi:            pbook
	cp pbook pbook.cgi

.PHONY:         clean cleano distclean
clean:
	-rm $(EXENAME)
cleano:
	rm $(objects)
distclean:
	rm $(EXENAME) $(objects)
	
