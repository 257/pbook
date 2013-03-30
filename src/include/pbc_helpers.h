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
extern int   parse_up(char *, int);
extern int   waz(char *);

#endif
