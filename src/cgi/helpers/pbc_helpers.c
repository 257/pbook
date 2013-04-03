#include "pbc_helpers.h"

int
parse_up(char *qstrp, char *up, char *phon, char *name, char *last) {

	Dlog("parse_up");
	char noalice[]   = "Alice doesn't live here anymore!\n";
	char havealice[] = "now lives here\n";
	char upalice[]   = "up2date\n";
	int upbit = UPDATE;
	DEBUGfunch(parse_up);
	DEBUGd(upbit);
	DEBUGd(LOOKUP);
	/*
	if (phon == NULL) {
		Dlog("phoc is null");
		Dmsg(upbit should be set to 1 now);
		upbit = LOOKUP;
		DEBUGd(upbit);
	}
	*/

	upbit = waz(up);
	DEBUGd(upbit);
	char myphon[] = "5143169147";
	char *myphonp = myphon;
	if(upbit == LOOKUP)
		phon = myphonp;
	if (!(isfield(up, phon, name, last)))
		return -1;
	Dlog("after isfield");
	char buf[MAX_QUERYS_LEN] = {0};
	char *bufp = buf;
	qstrp = mk_btreel(qstrp, delim, upbit, phon, name, last);
	send_recv_2pbk_skt(qstrp, bufp);
	switch (upbit) {
		case LOOKUP:
			if ((buf[0] - '0') == 0)
				printf("%s", noalice);
			//tnode *retnode = l2node(bufp, delim);
			else
				printf("%s\n", bufp);
			break;
		case UPDATE:
			if ((buf[0] - '0') == 0)
				printf("%s %s %s", name, last, havealice);
			else
				printf("%s %s %s %s", name, last, phon, upalice);
			break;
		default:
			break;
	}
	return 0;
}

int
waz(char *up) {
	int upbit;
	upbit = NONE;
	upbit = (strcmp(up , "LOOKUP")) ? upbit : LOOKUP;
	upbit = (strcmp(up , "UPDATE")) ? upbit : UPDATE;
	return upbit;
}

char *
mk_btreel(char *l, char *delim, int op, char *phon, char *name, char *last) {
	Dlog("mk_btreel");
	switch (op) {
		case LOOKUP:
			l    = strcpy(l, "1");
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
