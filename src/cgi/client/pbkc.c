#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sktc.h"
#include "cgigetval.h"
#include "html.h"

#include "pbc_helpers.h"
#include "debug.h"

int
main()
{
	Dlog("main");
	html_header("pbook");

	char *up    = NULL;
	char *name  = NULL;
	char *last  = NULL;
	char *phon = NULL;

	char qstr[MAX_QUERYS_LEN] = {0};
	char *qstrp;
	qstrp = qstr;

	up    = cgigetval("op");
	name  = cgigetval("name");
	last  = cgigetval("last");
	phon = cgigetval("phon");

	/*
	up             = "LOOKUP";
	name           = "qui";
	last           = "qoo";
	phon          = "1011111111";
	*/
	
	parse_up(qstrp, up, phon, name, last);
	html_footer();
	Dlog("after footer");
	return 0;
}
