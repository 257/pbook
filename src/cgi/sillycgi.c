#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cgigetval.h"

extern char *cgigetval(char *);

main()
{
	char *op;
	char *name;
	char *last;
	char *phon;

	printf("Content-Type: text/html; charset=us-ascii\n\n");

	printf("<html>\n");
	printf("<head>\n");
	printf("<title>CGI test result</title>\n");
	printf("</head>\n");
	printf("<body>\n");

	op   = cgigetval("op");
	name = cgigetval("name");
	last = cgigetval("last");
	phon = cgigetval("phon");

	if(name == NULL) {
		printf("You didn't enter any name!\n");
	}
	else if(last == NULL) {
		printf("You didn't enter any last name!\n");
	} else if(op != NULL && strcmp(op , "Lookup") == 0) {
		//TODO: lookup
		//printf("%s\n", text);
	} else if(op != NULL && strcmp(op, "Update") == 0) {
		//TODO: update
	}
	else {
		printf("something's wrong!\n");
	}
	printf("</body>\n");
	printf("</html>\n");
}
