#include "pbkd.h"



/* backgroud mode, needs signal(), no time sorry */
void
pbkd(int mode) {
	DEBUGfunch(pbkd);
	Done();
	switch (mode) {
		case START:
			//while ((c = getchar()) != EOF) {
				Dmsg(started pbd in foreground mode);
				Dmsg(calling recv_send_2pbk_skt);
				recv_send_2pbk_skt();
			//}
			Dmsg(caught EOF closing pbd);
			break;
		case KILL: // for signal(), not implemented 
			// close(s2);
			break;
		default:
			break;
	}
}
