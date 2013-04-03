#include "pb_str.h"
#include "btree.h"

char  *delim = DELIM;

tnode *
grow_btree(FILE *dbfp, tnode *root) {
	DEBUGfunch(grow_btree);
	char entry[MAX_ENTL];
	while (fgetline(dbfp, entry, MAX_ENTL) != EOF)
		if(l2node(entry, delim) != NULL)
			root = addnode_2root(root, l2node(entry, delim));
	Done();
	return root;
}

tnode *
l2node(char *l, char *delim) {
	tnode *node = NULL;
	char *phon;
	char *name;
	char *last;
	char *tokenp;
	int i  = OP;
	int op = NONE;
	int hasop = 0;
	if(l[1] == ':') {
		Dmsg(hasop);
		hasop = 1;
	}
	if (isdigit(l[0])) {
		for(tokenp = strtok(l, delim);
				tokenp != NULL && i <= LAST;
				i++, tokenp = strtok(NULL, delim)) {
			switch (i) {
				case OP:
					if(hasop == 0) {
						phon = tokenp;
						i = PHON;
					} else {
						op = atoi(tokenp);
						DEBUGd(op);
					}
					break;
				case PHON:
					phon = tokenp;
					break;
				case NAME:
					name = tokenp;
					break;
				case NAME_PHON:
				case LAST:
					last = tokenp;
					break;
				default:
					break;
			}
		}
		node = mk_node(node, op, NONE, phon, name, last);
	}
	return  node;
}
void
ugrow_btree(tnode *root, FILE *dbfp) {
	Dmsg(Writing to file...);
	tree_fprintf(root, PRE, dbfp);
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

/* caller of ins_node _must_ mk_node(node) before the call */
/* TODO: node here should be const node */

int
ins_node(tnode *root, tnode *node) {
	int insbit;
	tnode **place_in_tree = lookup(root, node);
	if ((*place_in_tree) == NULL) {
		Dmsg(NO match inserting here);
		tnode *nnode = NULL;
		nnode = mk_node(nnode, NONE, NONE, node->phon, node->name, node->last);
		root = addnode_2root(root, nnode);
		// (*place_in_tree) = nnode;
		treeprint(root, IN);
		insbit  = INS;
	} else {
		Dmsg(found a match updating);
		(*place_in_tree)->phon = node->phon;
		strcpy((*place_in_tree)->phon, node->phon);
		insbit  = UPDATE;
	}
	return insbit;
}

tnode **
lookup(tnode *root, tnode *q) {
	tnode **rootp = NULL;
	if (root == NULL)
		return (rootp = &root);
	int nmatched;
	int lmatched;
	if ((nmatched = isnmatch(q)) == 0)
		if ((lmatched = islmatch(q)) == 0)
			return (rootp = &root);
		else
			if (lmatched < 0)
				return lookup(root->left, q);
			else
				return lookup(root->right, q);
	else if (nmatched < 0)
		return lookup(root->left, q);
	else
		return lookup(root->right, q);
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
	DEBUGfunch(node2line);
	DEBUGd(node->op);
	lbuf = strcpy(lbuf, nodef_print(node, lbuf, OP));
	lbuf = strcat(lbuf, delim);
	DEBUGs(lbuf);
	lbuf = strcat(lbuf, nodef_print(node, lbuf, PHON));
	lbuf = strcat(lbuf, delim);
	DEBUGs(lbuf);
	lbuf = strcat(lbuf, nodef_print(node, lbuf, NAME));
	lbuf = strcat(lbuf, delim);
	DEBUGs(lbuf);
	lbuf = strcat(lbuf, nodef_print(node, lbuf, LAST));
	return lbuf;
}

char *
nodef_print(tnode *node, char *nodef, int prm) {
	if (node == NULL)
		return NULL;
	switch (prm) {
		case OP:
			nodef = itoa(node->op, nodef, 10);
			break;
		case PHON:
			nodef = node->phon;
			break;
		case NAME:
			nodef = node->name;
			break;
		/*
		case NAME_PHON:
			nodef_print(node, NAME);
			nodef_print(node, PHON);
			break;
			*/
		case LAST:
			nodef = node->last;
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
			nodef = node->name;
			break;
	}
	return nodef;
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

tnode *
mk_node(tnode *node, int op, int count, char *ph, char *n, char *l)  {
	node         = talloc();
	node->op     = op;
	node->count  = count;
	node->left   = node->right = NULL;
	(ph != NULL) ? (node->phon = strdup(ph)) : (node->phon = ph)   ;
	(n  != NULL) ? (node->name = strdup(n))  : (node->name = n)    ;
	(l  != NULL) ? (node->last = strdup(l))  : (node->last = l)    ;
	return node;
}

char *kr_strdup(char *s)
{
     char *p;

      p = (char *) malloc(strlen(s)+1);
      if (p != NULL)
          strcpy(p, s);
      return p;
}

/* talloc: make a tnode */
tnode *
talloc(void) {
	return (tnode *) malloc(sizeof(tnode));
}
