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

EXENAME       = pbook

include_dirs  = ./include
objects       = \
		fs.o \
		fline.o \
		btree.o \
		init_pbook.o \
		ui.o \
		pbd.o \
		pbook.o

SRV_PATH     = srv

pbook:           $(objects)
	cc -o $(EXENAME) $(objects)
	
	

cgi:            pbook
	cp pbook pbook.cgi

.PHONY:         clean
clean:
	        -rm $(EXENAME) $(objects)
