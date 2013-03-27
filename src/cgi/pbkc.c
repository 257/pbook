#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pb_skt.h"
#include "cgigetval.h"
#include "btree.h"
#include "html.h"

/* only thing we need from btree.h, so far */
/* TODO: there is more define delim */
enum op    { NONE, LOOKUP, INS, UPDATE, DEL, BOP};

extern char *cgigetval(char *);


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

main()
{
	html_header("pbook");

	char *op;
	char *name;
	char *last;
	char *phon;

	char qstr[MAX_Q_LEN];
	char *qstrp;
	qstrp = qstr;


	op   = cgigetval("op");
	name = cgigetval("name");
	last = cgigetval("last");
	phon = cgigetval("phon");

	/* i could just pass query pbkd for *root and then
	 * do btree operations on right here, right now
	 * but that needs a shared memory implementation
	 * again notime.
	 * we're gonna use unix domain sockets, simpler
	 */

	if(name == NULL) {
		printf("You didn't enter any name!\n");
	}
	else if(last == NULL) {
		printf("You didn't enter any last name!\n");
	} else if(op != NULL && strcmp(op , "Lookup") == 0) {
		qstrp = mk_btreel(qstrp, LOOKUP, phon, name, last);
		qstrp = send_recv_2pkd(qstrp);
		// TODO: need wrapper here to print fields
	} else if(op != NULL && strcmp(op, "Update") == 0) {
		qstrp = mk_btreel(qstrp, UPDATE, phon, name, last);
		send_recv_2pkd(qstrp);
	}
	else {
		printf("something's wrong!\n");
	}

	html_footer();
	return 0;
}
