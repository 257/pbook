#ifndef BTREE_H
#define BTREE_H

#define DELIM     ":"

#include "pb_limits.h"
#include "pb_line.h"

enum order { PRE, IN, POST };
enum hit   { NOHITS, HITS };
enum op    { NONE, LOOKUP, INS, UPDATE, DEL, BOP};

#define BPHN   BOP

// #define isop(op)   ((op <= NONE) || (BADOP <= op)) ? NONE : op


extern char *delim;

enum filed {
	OP,
	PHON,
	NAME,
	NAME_PHON,
	LAST,
	LAST_PHON,
	LAST_NAME,
	ALL
};

typedef struct tnode tnode;
struct tnode {                    /* the tree node: */
	unsigned int op;          /* operation directive */
	char *name;               
	char *last;
	long long phon;
	int count;                /* number of occurrences */
	tnode *left;              /* left child */
	tnode *parent;            /* parent for proper deletion but notime */
	tnode *right;             /* right child */
};

extern tnode        *grow_btree(FILE *, tnode *);
extern void         ugrow_btree(tnode *, FILE *);
extern tnode        *talloc(void);
extern tnode        *addnode_2root(tnode *, tnode *);
extern unsigned int ins_node(tnode *, tnode *);
extern tnode        *mk_node(tnode *, unsigned short op, long long ph, char *, char *, int count);
extern tnode        *lookup(tnode *, tnode *);
extern int          fgetline(FILE *fp, char line[], int max);
extern void         treeprint(tnode *, int);
/* void         tree_fwrite(tnode *, int, FILE *); */
extern void         tree_fprintf(tnode *, int, FILE *);
extern void         node_fprintf(tnode *, int, FILE *);
extern void         node_printf(tnode *);
/* void         node_fwrite(FILE *, tnode *); */
extern void         hit_print(tnode *);
extern char  *       nodef_print(tnode *, char *, int);
extern char  *      node2line(tnode *);
extern tnode *      l2node(char *l, char *);
extern tnode *      update_node(tnode *, tnode *);
unsigned short int  isop(long long);
extern char  *      mk_btreel(char *l, const int op, const char *phon, const char *name, const char *last);

/* http://users.powernet.co.uk/eton/kandr2/krx412.html */
char *utoa(unsigned long long value, char *digits, int base);
char *itoa(long long value, char *digits, int base);
#endif
