#include "pb_limits.h"

unsigned short int
isphon(long long phon) {
	if ((F_PHON <= phon) && (phon <= S_PHON))
		return 1;
	else
		return 0;
}
