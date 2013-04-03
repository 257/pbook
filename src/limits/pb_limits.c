#include "pb_limits.h"

unsigned short int
isop(long long op) {
	if ((NONE <= op) && (op <= BOP))
		return 1;
	else
		return 0;
}

/*
unsigned short int
isphon(long long phon) {


	if ((S_PHON <= phon) && (phon <= 1000000000))
		return 1;
	else
		return 0;
}
*/
