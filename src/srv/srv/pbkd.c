#include "pbkd.h"



/* backgroud mode, needs signal(), no time sorry */
void
pbkd(int mode) {
	int c;
	// static int s2;
	char qstr[MAX_QUERYS_LEN];
	char *qstrp = qstr;
	switch (mode) {
		case START:
			printf("\tsend EOF with Ctrl-D to stop pbd\n");
			while ((c = getchar()) != EOF) {
				recv_send_2pbk_skt(qstrp);
			}
			printf("\tcaught EOF, closing pbd\n");
			break;
		case KILL: /* for signal(), not implemented */
			// close(s2);
			break;
		default:
			break;
	}
}

