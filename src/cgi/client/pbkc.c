#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sktc.h"
#include "cgigetval.h"
#include "btree.h"
#include "html.h"

#include "ansi_colours.h"
#include "pbc_helpers.h"

/* only thing we need from btree.h, so far */
/* TODO: there is more define delim */
// enum op    { NONE, LOOKUP, INS, UPDATE, DEL, BOP};


/* TODO: ntime, ideally this should be hidden
 * away to keep main() only talking to 
 * http srv and hand stuff to modules that
 * know how to speak btree
 * that module would use a fairly general
 * socket module to communicate with
 * btree's socket
 * then we don't have to write code with
 * crap like ":" in it.
 */

int wazup(char *);
int
main()
{
	html_header("pbook");

	char *op    = NULL;
	char *name  = NULL;
	char *last  = NULL;
	char *phonc = NULL;

	char qstr[MAX_QUERYS_LEN];
	char *qstrp;
	qstrp = qstr;
	// int op = NONE;
	// long long phon = atoll(input);


	op    = cgigetval("op");
	name  = cgigetval("name");
	last  = cgigetval("last");
	phonc = cgigetval("phon");

	// tnode *pbc_node = mk_node(qnode, op, NONE, phon, name, last);

	op             = "LOOKUP";
	name           = "biz";
	last           = "biz";
	phonc          = "1000000000";

	if ((!isfield(op, OP) || !isfield(phonc, PHON) || !isfield(name, NAME) || !isfield(last, LAST)))
		goto footer;

	int upbit = wazup(op);
	qstrp = mk_btreel(qstrp, delim, LOOKUP, phonc, name, last);
	parse_up(qstrp, upbit);
	/* i could just pass query pbkd for *root and then
	 * do btree operations on right here, right now
	 * but that needs a shared memory implementation
	 * again notime.
	 * we're gonna use unix domain sockets, simpler
	 */
footer:
	html_footer();
	return 0;
}
int
wazup(char *op) {
	int upbit = NONE;
	upbit = (strcmp(op , "LOOKUP")) ? upbit : LOOKUP;
	upbit = (strcmp(op , "UPDATE")) ? upbit : UPDATE;
	return upbit;
}
