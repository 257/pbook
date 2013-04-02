VPATH          = $(wildcard ./*):$(wildcard ../*)
SUBDIRS        = .

MAKEFLAGS      = --no-print-directory
PREFIX        := $(PWD)
CSTD           = c99
CFLAGS         = -I$(include_dirs) \
		 -std=$(CSTD) \
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
		xctod.o \
		pbc_helpers.o

EXENAME        = pbkc.cgi
pbkc.cgi:           $(objects)
	cc -o $@ $(objects) && $(MAKE) -C . cleano
	
	

CGI_PATH      = public_html/cgi-bin
install:      pbkc.cgi
	cp $(EXENAME) $(HOME)/$(CGI_PATH)/$(EXENAME)


.PHONY:         clean cleano distclean
clean:
	-rm $(EXENAME)
cleano:
	-rm $(objects)
distclean:
	-rm $(EXENAME) $(objects)
