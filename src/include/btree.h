#ifndef BTREE_H
#define BTREE_H

#define DELIM         :

#include "pb_line.h"

enum order { PRE, IN, POST };
enum hit   { NOHITS, HITS };
enum op    { LOOKUP, INS, UPDATE };
enum filed {
	PHON = 1 /* for perm */,
	NAME,
	NAME_PHON,
	LAST,
	LAST_PHON,
	LAST_NAME,
	ALL
};

typedef struct tnode tnode;
struct tnode {                    /* the tree node: */
	char *name;               /* points to the text */
	char *last;
	char *phon;
	int count;                /* number of occurrences */
	int op;                   /* operation directive */
	tnode *left;              /* left child */
	tnode *parent;            /* parent for proper deletion but notime */
	tnode *right;             /* right child */
};

extern tnode        *grow_btree(FILE *, tnode *);
extern void         ugrow_btree(tnode *, FILE *);
extern tnode        *talloc(void);
extern tnode        *addnode_2root(tnode *, tnode *);
extern unsigned int ins_node(tnode *, tnode *);
extern tnode        *mk_node(tnode *, char *, char *, char *, int count, int op);
extern tnode        *lookup(tnode *, tnode *);
extern int          fgetline(FILE *fp, char line[], int max);
extern void         treeprint(tnode *, int);
/* void         tree_fwrite(tnode *, int, FILE *); */
extern void         tree_fprintf(tnode *, int, FILE *);
extern void         node_fprintf(tnode *, int, FILE *);
extern void         node_printf(tnode *);
/* void         node_fwrite(FILE *, tnode *); */
extern void         hit_print(tnode *);
extern char  *       node_print(tnode *, int);
extern char  *      node2line(tnode *);
extern tnode *      line2node(char *);
extern tnode *      update_node(tnode *, tnode *);
#endif
