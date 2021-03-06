#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>
#include <string.h>

#define MAXLINE 100
#define MAXROWS 10
#define MAXCOLS 10

/* Read one line from fp, */
/* copying it to line array (but no more than max chars). */
/* Does not place terminating \n in line array. */
/* Returns line length, or 0 for empty line, or EOF for end-of-file. */

int
getwords(char *line, char *words[], int maxwords)
{
char *p = line;
int nwords = 0;

while(1)
	{
	while(isspace(*p))
		p++;

	if(*p == '\0')
		return nwords;

	words[nwords++] = p;

	while(!isspace(*p) && *p != '\0')
		p++;

	if(*p == '\0')
		return nwords;

	*p++ = '\0';

	if(nwords >= maxwords)
		return nwords;
	}
}

int fgetline(FILE *fp, char line[], int max)
{
int nch = 0;
int c;
max = max - 1;

while((c = getc(fp)) != EOF)
	{
	if(c == '\n')
		break;

	if(nch < max)
		{
		line[nch] = c;
		nch = nch + 1;
		}
	}

if(c == EOF && nch == 0)
	return EOF;

line[nch] = '\0';
return nch;
}


int array[MAXROWS][MAXCOLS];
//char *filename = "input.dat";
char *filename = "phonebook";
FILE *ifp;
char line[MAXLINE];
char *words;
int nrows = 0;
int n;
int i;

char *delim = ":";

int
main() {
ifp = fopen(filename, "r");
if(ifp == NULL)
	{
	fprintf(stderr, "can't open %s\n", filename);
	exit(EXIT_FAILURE);
	}

while(fgetline(ifp, line, MAXLINE) != EOF)
	{
	if(nrows >= MAXROWS)
		{
		fprintf(stderr, "too many rows\n");
		exit(EXIT_FAILURE);
		}

	// n = getwords(line, words, MAXCOLS);
	/* for(words = strtok(l, " ");
				words != NULL && i <= LAST;
				i++, tokenp = strtok(NULL, delim)) {
				*/
		
	/*for(i = 0; i < n; i++)
		array[nrows][i] = atoi(words[i]);
	nrows++;
	*/
	for(words = strtok(line, delim); words != NULL;
						words = strtok(NULL, delim))
			printf("%s\n", words);
	}
return 0;
}
