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
	int ret;
	qstrp = send_recv_2pbk_skt(qstrp);
	tnode *retnode = l2node(qstrp, delim);
	switch (upbit) {
		case LOOKUP:
			/* TODO: handle other cases */
			if (retnode->count == 1) {
				// DEBUGs(qstrp);
				PPHON(retnode);
				ret = 0;
				break;
			}
			else {
				ret = NONE;
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
