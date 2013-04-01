#include "pbc_helpers.h"
#include "node_print.h"

int
isfield(char *input, int field) {
	int ret = TRUE;
	if (input != NULL) {
		if (field == PHON) {
			long long phon = atoll(input);
			if (isphon(phon))
				;
		}
	} else {
		ret = FALSE;
		switch (field) {
			case OP:
				printf("Naughty naughty srv!\n");
			case PHON:
				printf("Bad phone!\n");
				break;
			case NAME:
				printf("You didn't enter any name!\n");
				break;
			case LAST:
				printf("You didn't enter any last name!\n");
				break;
			default:
				break;
		}
	}
	return ret;
}

int
parse_up(char *qstrp, int upbit) {
	DEBUGfunch(parse_up);
	int ret;
	char buf[MAX_QUERYS_LEN] = {0};
	char *bufp = buf;
	send_recv_2pbk_skt(qstrp, bufp);
	tnode *retnode = l2node(bufp, delim);
	switch (upbit) {
		case LOOKUP:
			/* TODO: handle other cases */
			switch (retnode->op) {
				case NONE:
					ret = 0;
					break;
				case LOOKUP:
					Dmsg(treeprinting retnode);
					treeprint(retnode, PRE);
					PPHON(retnode);
					ret = NONE;
					break;
				default:
					break;
			}
		case UPDATE:
			// DEBUGs(qstrp);
			ret = NONE;
			break;
		default:
			break;
	}
	return ret;
}

int
waz(char *up) {
	int upbit;
	upbit = NONE;
	upbit = (strcmp(up , "LOOKUP")) ? upbit : LOOKUP;
	upbit = (strcmp(up , "UPDATE")) ? upbit : UPDATE;
	return upbit;
}
