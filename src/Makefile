VPATH          = $(wildcard ./*)
SUBDIRS        = .

modules        = fs
modules       += :btree
modules       += :init
modules       += :ui
modules       += :main

MAKEFLAGS      = --no-print-directory
PREFIX        := $(PWD)
CSTD           = c99
CFLAGS         = -I$(include_dirs) \
		 -std=$(CSTD) \
		 -g \
		 -Wall
EXENAME       = pbook
include_dirs  = ./include
objects       = \
		pb_limits.o \
		fs.o \
		fline.o \
		btree.o \
		skts.o \
		pbkd.o \
		init_pbook.o \
		pbook.o

pbook:           $(objects)
	cc -o $@ $(objects) && \
		$(MAKE) -C $(PWD) clean


SRV_PATH      = ./srv
#pbkd.o:
#$(MAKE) -C $(SRV_PATH)
	

.PHONY:         clean cleano distclean
clean:
	-rm $(objects)
distclean:
	-rm $(EXENAME) $(objects)
