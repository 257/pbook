VPATH          = $(wildcard ./*)
SUBDIRS        = .

modules        = fs
modules       += :btree
modules       += :init
modules       += :ui
modules       += :main

MAKEFLAGS      = --no-print-directory
PREFIX        := $(PWD)
CFLAGS         = -I$(include_dirs) \
		-g \
		-Wall

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
	cc -o $@ $(objects) && $(MAKE) -C . clean

SRV_PATH      = ./srv
#pbkd.o:
#$(MAKE) -C $(SRV_PATH)
	

.PHONY:         clean cleano distclean
clean:
	$(MAKE) -C $(SRV_PATH) $@ && rm $(objects)
distclean:
	$(MAKE) -C $(SRV_PATH) $@ && rm $(EXENAME) $(objects)
	
