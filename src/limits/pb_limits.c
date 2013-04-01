#include "pb_limits.h"

unsigned short int
isop(long long op) {
	if ((NONE <= op) && (op <= BOP))
		return 1;
	else
		return 0;
}

unsigned short int
isphon(long long phon) {
	if ((F_PHON <= phon) && (phon <= S_PHON))
		return 1;
	else
		return 0;
}
