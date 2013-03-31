#include "pb_str.h"
#include "btree.h"

char *delim = DELIM;

tnode *
grow_btree(FILE *dbfp, tnode *root) {
	char entry[MAX_ENTL];
	while (fgetline(dbfp, entry, MAX_ENTL) != EOF)
		if(l2node(entry, delim) != NULL)
			root = addnode_2root(root, l2node(entry, delim));
	// treeprint(root, PRE);
	return root;
}

/* TODO: this doeesn't belong here; client side stuff*/
char *
mk_btreel(char *l, char *delim, const int op, const char *phon, const char *name, const char *last) {
	switch (op) {
		case LOOKUP:
			l = strcpy(l, "1");
			break;
		case UPDATE:
			l = strcpy(l, "3");
			break;
		default:
			break;
	}
	l = strcat(l, delim);
	l = strcat(l, phon);
	l = strcat(l, delim);
	l = strcat(l, name);
	l = strcat(l, delim);
	l = strcat(l, last);
	return l;
}

// TODO: isline()

tnode *
l2node(char *l, char *delim) {
	tnode *node = NULL;
	char name[MAXNAME];
	char last[MAXNAME];
	long long phon = NONE;
	char *tokenp;
	int i  = OP;
	long long op = NONE;
	if (isdigit(l[0])) {
		for(tokenp = strtok(l, delim);
				tokenp != NULL && i <= LAST;
				i++, tokenp = strtok(NULL, delim)) {
			switch (i) {
				case OP:
					op = atoll(tokenp);
					/* every input goes
					 * through this point
					 * or does it?
					 * so we check for sanity
					 * once and for all here
					 */
					if (isphon(op)) {
						phon = op;
						op   = NONE;
						i    = PHON;
					} else if (isop(op))
						;
					else
						op   = NONE;
					break;
				case PHON:
					if (isphon(op)) {
						phon = op;
						op   = NONE;
					}
				case NAME:
					strcpy(name, tokenp);
					break;
				case NAME_PHON:
				case LAST:
					strcpy(last, tokenp);
					break;
				default:
					break;
			}
		}
		/* TODO: TOASK: is the cast here called for? */
		node = mk_node(node, (unsigned short) op, HITS, phon, name, last);
	}
	return  node;
}
void
ugrow_btree(tnode *root, FILE *dbfp) {
	// treeprint(root, PRE);
	Dmsg("Writing to file...\n");
	tree_fprintf(root, PRE, dbfp);
}


unsigned short int
isop(long long op) {
	if ((NONE <= op) && (op < BOP))
		return 1;
	else
		return 0;
}
/* addnode_2root: add a node with n, at or below p */

tnode *
addnode_2root(tnode *root, tnode *node) {
	int cond;
	if (root == NULL) {         /* a new name has arrived */
		root = node;
	} else if ((cond = strcmp(node->name, root->name)) == 0) {
		root->count++;      /* repeated name */
		if ((cond = strcmp(node->last, root->last)) == 0) {
			return root;
		} else if (cond < 0)       /* less than into left subtree */
			root->left  = addnode_2root(root->left, node);
		else             /* greater than into right subtree */
			root->right = addnode_2root(root->right, node);
		return root;
	} else if (cond < 0)       /* less than into left subtree */
		root->left  = addnode_2root(root->left, node);
	else             /* greater than into right subtree */
		root->right = addnode_2root(root->right, node);
	return root;
}
unsigned int
ins_node(tnode *root, tnode *node) {
	int cond;
	if (root == NULL) {         /* a new name has arrived */
		root = node;
		return 0;
	} else if ((cond = strcmp(node->name, root->name)) == 0) {
		node->count++;
		if ((cond = strcmp(node->last, root->last)) == 0) {
			printf("can't insert duplicate\n");
			return 1;
		} else if (cond < 0) {
			if (root->left == NULL)
				root->left = node;
			else
				ins_node(root->left, node);
		} else {
			if (root->right == NULL)
				root->right = node;
			else
				ins_node(root->right, node);
		}
	} else if (cond < 0) {
		if (root->left == NULL)
			root->left = node;
		else
			ins_node(root->left, node);
	} else {
		if (root->right == NULL)
			root->right = node;
		else
			ins_node(root->right, node);
	}
	return 0;
}

/* TODO: caller has to make sure lookup
 * is handed a q node with
 * q->op == LOOKUP
 * for invetory reasons
 */


tnode *
lookup(tnode *root, tnode *q) {
	if (root == NULL)
		return root;
	int matched;
	DEBUGs(q->name);
	DEBUGs(q->last);
	Dmsg("tree from here\n");
	treeprint(root, PRE);
	matched = isnmatch(root, q);
	if (matched == 0)
		if ((matched = islmatch(root, q)) == 0)
			return root;
		else
			if (matched < 0)
				return lookup(root->left, q);
			else
				return lookup(root->right, q);
	else if (matched < 0)
		return lookup(root->left, q);
	else
		return lookup(root->right, q);
}

/* TODO: !function */
unsigned int
isnmatch(tnode *root, tnode *q) {
	return strcmp(q->name, root->name);
}
/* TODO: !function */
unsigned int
islmatch(tnode *root, tnode *q) {
	return strcmp(q->last, root->last);
}

tnode *
update_node(tnode *root, tnode *update_node) {
	tnode *q = NULL;
	q = update_node;
	q = lookup(root, q);
	switch (q->count) {
		case HITS:
			if (q->phon == update_node->phon) {
				strcpy(update_node->name, "already up2date");
				strcpy(update_node->last, "already up2date");
			} else {
				q->phon = update_node->phon;
			}
			break;
			/* TODO: *commit* after update */
		case NOHITS:
		default:
			update_node->name = strcpy(update_node->name, "record !here");
			update_node->last = strcpy(update_node->last, "record !here");
			break;
	}
	return update_node;
}
void
treeprint(tnode *root, int order) {
	if (root != NULL) {
		switch (order) {
			case PRE:
				node_printf(root);
				treeprint(root->left, order);
				treeprint(root->right, order);
				break;
			case IN:
				treeprint(root->left, order);
				node_printf(root);
				treeprint(root->right, order);
				break;
			case POST:
				treeprint(root->left, order);
				treeprint(root->right, order);
				node_printf(root);
				break;
			default:
				break;
		}
	}
}
void
node_printf(tnode *node) {
	char phon[MAXNAME];
	char *phonp = phon;
	printf("%s:%s:%s\n",
	nodef_print(node, phonp, PHON),
	nodef_print(node, NULL, NAME),
	nodef_print(node, NULL, LAST));
}

char *
node2line(tnode *node, char *delim, char *lbuf) {
	if (node == NULL)
		return NULL;
	lbuf = strcpy(lbuf, nodef_print(node, lbuf, PHON));
	lbuf = strcat(lbuf, delim);
	lbuf = strcat(lbuf, nodef_print(node, NULL, NAME));
	lbuf = strcat(lbuf, delim);
	lbuf = strcat(lbuf, nodef_print(node, NULL, LAST));
	return lbuf;
}

char *
nodef_print(tnode *node, char *phon, int prm) {
	if (node == NULL)
		return NULL;
	if (node->name != NULL)
		switch (prm) {
			case PHON:
				phon = itoa(node->phon, phon, 10);
				return phon;
				break;
			case NAME:
				return node->name;
				break;
			/*
			case NAME_PHON:
				nodef_print(node, NAME);
				nodef_print(node, PHON);
				break;
				*/
			case LAST:
				return node->last;
				break;
			/*
			case LAST_PHON:
				nodef_print(node, LAST);
				nodef_print(node, PHON);
				break;
			case LAST_NAME:
				nodef_print(node, LAST);
				nodef_print(node, NAME);
				break;
			case ALL:
				nodef_print(node, LAST_NAME);
				nodef_print(node, PHON);
				break;
				*/
			default:
				return node->name;
				break;
		}
	else
		return node->name;
}
void
tree_fprintf(tnode *root, int order, FILE *dbfp) {
	if (root != NULL) {
		switch (order) {
			case PRE:
				node_fprintf(root, order, dbfp);
				tree_fprintf(root->left, order, dbfp);
				tree_fprintf(root->right, order, dbfp);
				break;
			case IN:
				tree_fprintf(root->left, order, dbfp);
				node_fprintf(root, order, dbfp);
				tree_fprintf(root->right, order, dbfp);
				break;
			case POST:
				tree_fprintf(root->left, order, dbfp);
				tree_fprintf(root->right, order, dbfp);
				node_fprintf(root, order, dbfp);
				break;
			default:
				break;
		}
	}
}
void
node_fprintf(tnode *node, int order, FILE *dbfp) {
	char phon[MAXNAME];
	char *phonp = phon;
	switch (order) {
		case IN:
			fprintf(dbfp, "%*s\t%*s\t%*s\n",
					MAXNAME,
			nodef_print(node, NULL, NAME),
					MAXNAME,
			nodef_print(node, NULL, LAST),
					MAXNAME,
			nodef_print(node, phonp, PHON));
			break;
		default:
			fprintf(dbfp,"%s:%s:%s\n",
			nodef_print(node, phonp, PHON),
			nodef_print(node, NULL, NAME),
			nodef_print(node, NULL, LAST));
			break;
	}
}

void
hit_print(tnode *node) {
	printf("%d\n", node->count);
}

char *utoa(unsigned long long value, char *digits, int base)
{
    char *s, *p;

    s = "0123456789abcdefghijklmnopqrstuvwxyz"; /* don't care if s is in
                                                 * read-only memory
                                                 */
    if (base == 0)
        base = 10;
    if (digits == NULL || base < 2 || base > 36)
        return NULL;
    if (value < (unsigned) base) {
        digits[0] = s[value];
        digits[1] = '\0';
    } else {
        for (p = utoa(value / ((unsigned)base), digits, base);
             *p;
             p++);
        utoa( value % ((unsigned)base), p, base);
    }
    return digits;
}   

char *itoa(long long value, char *digits, int base)
{
    char *d;
    unsigned long long u; /* assume unsigned is big enough to hold all the
                           * unsigned values -x could possibly be -- don't
                           * know how well this assumption holds on the
                           * DeathStation 9000, so beware of nasal demons
                           */

    d = digits;
    if (base == 0)
        base = 10;
    if (digits == NULL || base < 2 || base > 36)
        return NULL;
    if (value < 0) {
        *d++ = '-';
        u = -value;
    } else
        u = value;
    utoa(u, d, base);
    return digits;
}

/* broken i know, would have been a nice analogy */

tnode *
mk_node(tnode *node, unsigned short op, int count, long long ph, char *n, char *l)  {
	node         = talloc();
	node->op     = op;
	node->phon   = ph; /* we don't care about BPHN, caller's job */
	node->count  = count;
	node->left   = node->right = NULL;
	(n  != NULL) ? (node->name = strdup(n))  : (node->name = n)    ;
	(l  != NULL) ? (node->last = strdup(l))  : (node->last = l)    ;
	return node;
}

char *strdup(char *s)         /* make a duplicate of s */
{
     char *p;

      p = (char *) malloc(strlen(s)+1); /* +1 for '\0' */
      if (p != NULL)
          strcpy(p, s);
      return p;
}

/* talloc: make a tnode */
tnode *
talloc(void) {
	return (tnode *) malloc(sizeof(tnode));
}
