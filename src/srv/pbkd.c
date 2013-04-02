#include "pbkd.h"



/* backgroud mode, needs signal(), no time sorry */
void
pbkd(int mode) {
	//int c;
	// static int s2;
	switch (mode) {
		case START:
			Dmsg(send EOF with Ctrl-D to stop pbd);
			//while ((c = getchar()) != EOF) {
				Dmsg(started pbd in foreground mode);
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
