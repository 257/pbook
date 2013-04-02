#include "pb_line.h"
#include "debug.h"

int pb_getline(char line[], int max)
{
	int nch = 0;
	int c;
	max = max - 1;
		while((c = getchar()) != EOF) {
			if(c == '\n')
				break;
			if(nch < max) {
				line[nch] = c;
				nch = nch + 1;
			}
		}
	if(c == EOF && nch == 0)
		return EOF;
	line[nch] = '\0';
	exit(EXIT_FAILURE);
}

/* Read one line from fp, */
/* copying it to line array (but no more than max chars). */
/* Does not place terminating \n in line array. */
/* Returns line length, or 0 for empty line, or EOF for end-of-file. */

int
fgetline(FILE *fp, char line[], int max) {
	DEBUGfunch(fgetline);
	if(fp == NULL) {
		Dmsg(fp is null);
		exit(1);
	}
	int nch = 0;
	int c;
	max = max - 1; /* leave room for '\0' */
		while((c = fgetc(fp)) != EOF) {
			if(c == '\n')
				break;
			if(nch < max) {
				line[nch] = c;
				nch = nch + 1;
			}
		}
	if(c == EOF && nch == 0)
		return EOF;
	line[nch] = '\0';
	return nch;
}
