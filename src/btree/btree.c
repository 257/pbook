#include "btree.h"

tnode *
grow_btree(FILE *dbfp, tnode *root) {
	char entry[MAX_ENTL];
	while (fgetline(dbfp, entry, MAX_ENTL) != EOF)
		if(line2node(entry) != NULL)
			root = addnode_2root(root, line2node(entry));
	// treeprint(root, PRE);
	return root;
}

tnode *
line2node(char *line) {
	tnode *node = NULL;
	char name[MAXNAME];
	char last[MAXNAME];
	char phon[MAXNAME];
	char *tokenp;
	int i = PHON;
	if (isdigit(line[0])) {
		for(tokenp = strtok(line, ":");
				tokenp != NULL && i <= LAST;
				i++, tokenp = strtok(NULL, ":")) {
			switch (i) {
				case PHON:
					strcpy(phon, tokenp);
					break;
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
		node = mk_node(node, phon, name, last, HITS);
	}
	return  node;
}
void
ugrow_btree(tnode *root, FILE *dbfp) {
	// treeprint(root, PRE);
	printf("\n\twriting data to file...\n\n");
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
/* TODO: make another struct for q to hold hits' nodes */
tnode *
lookup(tnode *root, tnode *q) {
	int cond;
	/* DEBUG:
	 * treeprint(root, PRE);
	 * printf("lookup: tree\n");
	 */
	if (root == NULL) {
		q = mk_node(root, NULL, NULL, NULL, q->count);
		/* CLEANUP:
		 * q = mk_node(root, root->phon, root->name, root->last, q->count);
		 */
		return q;
	} else if ((cond = strcmp(q->name, root->name)) == 0) { /* got a hit, keep track */
		q->count++;
		if ((cond = strcmp(q->last, root->last)) == 0) { /* got a match return */
			return (q = root);
		} else if (cond < 0)
			return lookup(root->left, q);
		else
			return lookup(root->right, q);
	} else if (cond < 0)
		return lookup(root->left, q);
	else
		return lookup(root->right, q);
}

tnode *
update_node(tnode *root, tnode *node) {
	tnode *q = NULL;
	q = node;
	q = lookup(root, q);
	switch (q->count) {
		case HITS:
			if (strcmp(node->phon, q->phon) == 0) {
				printf("the phone number you ");
				printf("entered is the _same_ ");
				printf("as the one on the record\n");
				printf("\nno update is required.\n\n");
			} else {
				q->phon = strdup(node->phon);
				printf("\nrecord has been updated for:\t%s %s\n\n", node->last, node->name);
			}
			return q;
			break;
		case NOHITS:
		default:
			printf("\nno record was found for:\t%s %s\n\n", node->last, node->name);
			return q;
			break;
	}
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
	printf("%s:%s:%s\n",
	node_print(node, PHON),
	node_print(node, NAME),
	node_print(node, LAST));
}

char *
node2line(tnode *node) {
	char l[MAX_ENTL];
	char *lp = l;
	strcpy(lp, node_print(node, PHON));
	strcat(lp, node_print(node, NAME));
	strcat(lp, node_print(node, LAST));
	return lp;
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
	switch (order) {
		case IN:
			fprintf(dbfp, "%*s\t%*s\t%*s\n", /* TODO: pass DELIM to fprintf */
					MAXNAME,
			node_print(node, NAME),
					MAXNAME,
			node_print(node, LAST),
					MAXNAME,
			node_print(node, PHON));
			break;
		default:
			fprintf(dbfp,"%s:%s:%s\n",
			node_print(node, PHON),
			node_print(node, NAME),
			node_print(node, LAST));
			break;
	}
}
/*
void tree_fwrite(tnode *root, int order, FILE *datafile) {
	if (root != NULL) {
		switch (order) {
			case PRE:
				node_fwrite(root, datafile);
				tree_fwrite(root->left, order);
				tree_fwrite(root->right, order);
				break;
			case IN:
				tree_fwrite(root->left, order);
				node_fwrite(root, datafile);
				tree_fwrite(root->right, order);
				break;
			case POST:
				tree_fwrite(root->left, order);
				tree_fwrite(root->right, order);
				node_fwrite(root, datafile);
				break;
			default:
				break;
		}
	}
}
void
node_fwrite(FILE *datafile, tnode *node) {
	fwrite(node->phon, sizeof(node->phon), srtlen(node->phon), datafile),
	fwrite("DELIM", sizeof("DELIM"), 1, datafile),
	fwrite(node->name, sizeof(node->name), srtlen(node->name), datafile),
	fwrite("DELIM", sizeof("DELIM"), 1, datafile),
	fwrite(node->last, sizeof(node->last), srtlen(node->last), datafile),
	fwrite('\n', sizeof('\n'), 1, datafile),
	fwrite('\0', sizeof('\0'), 1, datafile),
}
*/
void
hit_print(tnode *node) {
	printf("%d\n", node->count);
}
/* broken i know, would have been a nice analogy */
char *
node_print(tnode *node, int prm) {
	if (node->name != NULL)
		switch (prm) {
			case PHON:
				return node->phon;
				break;
			case NAME:
				return node->name;
				break;
			/*
			case NAME_PHON:
				node_print(node, NAME);
				node_print(node, PHON);
				break;
				*/
			case LAST:
				return node->last;
				break;
			/*
			case LAST_PHON:
				node_print(node, LAST);
				node_print(node, PHON);
				break;
			case LAST_NAME:
				node_print(node, LAST);
				node_print(node, NAME);
				break;
			case ALL:
				node_print(node, LAST_NAME);
				node_print(node, PHON);
				break;
				*/
			default:
				return node->name;
				break;
		}
	else
		return node->name;
}

tnode *
mk_node(tnode *node, char *ph, char *n, char *l, int h) {
	node = talloc();
	(ph != NULL) ? (node->phon = strdup(ph)) : (node->phon = ph);
	(n  != NULL) ? (node->name = strdup(n))  : (node->name = n) ;
	(l  != NULL) ? (node->last = strdup(l))  : (node->last = l) ;
	node->count = h;
	node->left  = node->right = NULL;
	return node;
}


/* talloc: make a tnode */
tnode *
talloc(void) {
	return (tnode *) malloc(sizeof(tnode));
}
