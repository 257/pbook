#ifndef    PB_HELPERS_H
#define    PB_HELPERS_H

#include "debug.h"
#include "node_print.h"
#include "pb_limits.h"
#include "btree.h"
#include "sktc.h"
#include "ansi_colours.h"

#define str(s) #s




enum boolean { FALSE, TRUE };
extern int   isfield(char *, int);
extern char *mk_btreel(char *l, char *delim, const int op, const char *phon, const char *name, const char *last);
extern void  parse_up(char *, char *up, char *phonc, char *name, char *last);
extern int   waz(char *);

#endif
