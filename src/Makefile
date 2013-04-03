VPATH          = $(wildcard ./*)
SUBDIRS        = .

modules        = fs
modules       += :btree
modules       += :init
modules       += :ui
modules       += :main

MAKEFLAGS      = --no-print-directory
PREFIX        := $(PWD)
# no fd in c99 and we
# need it for unix sockets
CSTD           = c99 \
		 -std=$(CSTD)
CFLAGS         = -I$(include_dirs) \
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
