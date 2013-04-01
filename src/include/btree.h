#ifndef BTREE_H
#define BTREE_H

#define DELIM     ":"

#include "debug.h"
#include "node_print.h"
#include "pb_limits.h"
#include "pb_line.h"

enum order { PRE, IN, POST };
enum hit   { NOHITS, HITS };

#define BPHN   BOP


#define isnmatch(...)        strcmp(__VA_ARGS__->name, root->name)
#define islmatch(...)        strcmp(__VA_ARGS__->last, root->last)

#define name_up2date(...)    strcpy(__VA_ARGS__->name, "already up2date")
#define last_up2date(...)    strcpy(__VA_ARGS__->last, "already up2date")
#define  all_up2date(...)    (name_up2date(__VA_ARGS__), last_up2date(__VA_ARGS__))



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

extern tnode *root;

extern tnode        *grow_btree(FILE *, tnode *);
extern void          ugrow_btree(tnode *, FILE *);
extern tnode        *talloc(void);
extern tnode        *addnode_2root(tnode *, tnode *);
extern int           ins_node(tnode *, tnode *);
extern tnode        *mk_node(tnode *, int op, int count, long long ph, char *n, char *l);
extern tnode        **lookup(tnode *, tnode *);
extern int           fgetline(FILE *fp, char line[], int max);
extern void          treeprint(tnode *, int);
extern void          tree_fprintf(tnode *, int, FILE *);
extern void          node_fprintf(tnode *, int, FILE *);
extern void          node_printf(tnode *);
extern void          hit_print(tnode *);
extern char         *nodef_print(tnode *, char *, int);
extern void          node2line(tnode *, char *delim, char *l);
extern tnode        *l2node(char *l, char *delim);
extern tnode        *update_node(tnode *, tnode *);
extern char         *mk_btreel(char *l, char *delim, const int op, const char *phon, const char   *name, const char *last);

/* http://users.powernet.co.uk/eton/kandr2/krx412.html */
char *utoa(unsigned long long value, char *digits, int base);
char *itoa(long long value, char *digits, int base);
#endif
