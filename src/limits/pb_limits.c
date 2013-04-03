#include "pb_limits.h"

unsigned short int
isop(long long op) {
	if ((NONE <= op) && (op <= BOP))
		return 1;
	else
		return 0;
}

int
isfield(char *up, char *ph, char *n, char *l) {
	if (isup(up) && isph(ph) && isn(n) && isn(l))
		return TRUE;
	return FALSE;
}

int
no_up() {
	NO_UP();
	return FALSE;
}

int
isup(char *up) {
	if(up == NULL)
		return no_up();
	return TRUE;
}

int
long_phon() {
	LONG_PHON();
	return FALSE;
}

int
bad_phon_dig() {
	BAD_PHON_DIG();
	return FALSE;
}

int
phon_with_zero_start() {
	BAD_PHON_ZERO_START();
	return FALSE;
}

int
isphdigit(char *phon, int len) {
	for(len = 0; len < PHON_LEN; len++)
		if (!(phon[len] >= '0' && phon[len] <= '9'))
			return bad_phon_dig();
	if(phon[0] == '0')
		return phon_with_zero_start();
	return TRUE;
}

int
no_input_phon() {
	NO_INPUT_PHON();
	return FALSE;
}

int
isph(char *phon) {
	if(phon == NULL)
		return no_input_phon();
	int len = strlen(phon);
	if(len != PHON_LEN) {
		return  long_phon();
	}
	else
		return isphdigit(phon, len);
}

int
name_is_long(char *name) {
	LONG_NAME(name);
	return FALSE;
}


int
is_name_alpha(char *name, int len) {
	int i;
	for(i = 0; i < len; i++)
		if(!(isalpha(name[i]))) {
			BAD_NAME_ALPHA();
			return FALSE;
		}
	return TRUE;
}

int
no_name() {
	NO_NAME(name);
	return FALSE;
}

int
isn(char *name) {
	if(name == NULL)
		return no_name();
	else {
		int len = strlen(name);
		if(MAXNAME < len)
			return name_is_long(str(name));
		else
			return is_name_alpha(name, len);
	}
	return TRUE;
}

int
isl(char *last) {
	return isn(last);
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
