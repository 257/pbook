#ifndef INIT_PBOOK_H
#define INIT_PBOOK_H
#include "pb_fs.h"
#include "btree.h"


enum { RB = 1, WB };

extern int load_pbook(char *, int);
extern tnode *init_pbook(tnode *);
extern char  *uinit_pbook(tnode *);



extern FILE *dbfp;
extern tnode *root;

#endif
