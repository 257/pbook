#include "pbkd.h"



/* backgroud mode, needs signal(), no time sorry */
void
pbkd(int mode) {
	DEBUGfunch(pbkd);
	Done();
	switch (mode) {
		case START:
			Dmsg(started pbd in foreground mode);
			Dmsg(calling recv_send_2pbk_skt);
			recv_send_2pbk_skt();
			break;
		case KILL:
			break;
		default:
			break;
	}
}
