#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cgigetval.h"

/* only thing we need from btree.h, so far */
/* TODO: there is more define delim */
enum op    { NONE, LOOKUP, INS, UPDATE, DEL, BOP};

extern char *cgigetval(char *);

char *mk_btreel(char *, char *, char *, char *);

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

char *
mk_btreel(char *l, int op, char *phon, char *name, char *last) {
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
	l = strcat(l, ":");
	l = strcat(l, phon);
	l = strcat(l, ":" );
	l = strcat(l, name);
	l = strcat(l, ":" );
	l = strcat(l, last);
	return l;
}
main()
{
	char *op;
	char *name;
	char *last;
	char *phon;

	char qstr[MAX_Q_LEN];
	char *qstrp;
	qstrp = qstr;

	printf("Content-Type: text/html; charset=us-ascii\n\n");

	printf("<html>\n");
	printf("<head>\n");
	printf("<title>CGI test result</title>\n");
	printf("</head>\n");
	printf("<body>\n");

	op   = cgigetval("op");
	name = cgigetval("name");
	last = cgigetval("last");
	phon = cgigetval("phon");

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
	printf("</body>\n");
	printf("</html>\n");
}
