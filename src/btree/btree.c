#include "pb_str.h"
#include "btree.h"

char  *delim = DELIM;

tnode *
grow_btree(FILE *dbfp, tnode *root) {
	char entry[MAX_ENTL];
	while (fgetline(dbfp, entry, MAX_ENTL) != EOF)
		if(l2node(entry, delim) != NULL)
			/* TODO: addnode_2root is hereby marked as redundent
			 * use the better ins_node() function.
			 */
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
	long long phon = NONE;
	char *name;
	char *last;
	char *tokenp;
	int i  = OP;
	int op = NONE;
	if (isdigit(l[0])) {
		for(tokenp = strtok(l, delim);
				tokenp != NULL && i <= LAST;
				i++, tokenp = strtok(NULL, delim)) {
			switch (i) {
				case OP:
					phon = atoll(tokenp);
					if (isphon(phon)) {
						Dmsg(!isop);
						op   = NONE;
						i    = PHON;
					} else {
						op = tokenp[0] - '0';
					}
					break;
				case PHON:
					phon = atoll(tokenp);
					if (isphon(phon)) {
						;
					}
				case NAME:
					//strcpy(name, tokenp);
					name = tokenp;
					break;
				case NAME_PHON:
				case LAST:
					// strcpy(last, tokenp);
					last = tokenp;
					break;
				default:
					break;
			}
		}
		/* TODO: TOASK: is the cast here called for? */
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
	int ret;
	DEBUGfunch(ins_node);
	tnode **place_in_tree = lookup(root, node);
	if ((*place_in_tree) == NULL) {
		Dmsg(NO match inserting here);
		tnode *nnode = NULL;
		nnode = mk_node(nnode, NONE, 1, node->phon, node->name, node->last);
		(*place_in_tree) = nnode;
		ret  = INS;
	} else {
		Dmsg(found a match updating);
		// printf("%lld\n", node->phon);
		(*place_in_tree)->phon = node->phon;
		// printf("%lld\n", (*place_in_tree)->phon);
		ret  = UPDATE;
	}
	return ret;
}
/*
tnode *
update_node(tnode *root, tnode *update_node) {
	tnode **q = NULL;
	q = update_node;
	q = lookup(root, q);
	switch (q->count) {
		case HITS:
			if (q->phon == update_node->phon)
				all_up2date(update_node);
			else
				q->phon = update_node->phon;
			break;
		case NOHITS:
		default:
			update_node->name = strcpy(update_node->name, "record !here");
			update_node->last = strcpy(update_node->last, "record !here");
			break;
	}
	return update_node;
}
*/

tnode **
lookup(tnode *root, tnode *q) {
	tnode **rootp = NULL;
	// DEBUGs(q->name);
	// DEBUGs(q->last);
	// Dmsg(tree from here);
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

void
node2line(tnode *node, char *delim, char *lbuf) {
	DEBUGfunch(node2line);
	DEBUGs(lbuf);
	DEBUGd(node->op);
	strcpy(lbuf, nodef_print(node, lbuf, OP));
	DEBUGs(lbuf);
	strcat(lbuf, delim);
	DEBUGs(lbuf);
	//strcat(lbuf, nodef_print(node, lbuf, PHON));
	DEBUGs(lbuf);
	strcat(lbuf, delim);
	DEBUGs(lbuf);
	strcat(lbuf, nodef_print(node, lbuf, NAME));
	strcat(lbuf, delim);
	DEBUGs(lbuf);
	strcat(lbuf, nodef_print(node, lbuf, LAST));
}

char *
nodef_print(tnode *node, char *nodefb, int prm) {
	if (node == NULL)
		return NULL;
	switch (prm) {
		case OP:
			itoa(node->op, nodefb, 10);
			break;
		case PHON:
			itoa(node->phon, nodefb, 10);
			break;
		case NAME:
			nodefb = node->name;
			break;
		/*
		case NAME_PHON:
			nodefb_print(node, NAME);
			nodefb_print(node, PHON);
			break;
			*/
		case LAST:
			nodefb = node->last;
			break;
		/*
		case LAST_PHON:
			nodefb_print(node, LAST);
			nodefb_print(node, PHON);
			break;
		case LAST_NAME:
			nodefb_print(node, LAST);
			nodefb_print(node, NAME);
			break;
		case ALL:
			nodefb_print(node, LAST_NAME);
			nodefb_print(node, PHON);
			break;
			*/
		default:
			nodefb = node->name;
			break;
	}
	return nodefb;
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
mk_node(tnode *node, int op, int count, long long ph, char *n, char *l)  {
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
