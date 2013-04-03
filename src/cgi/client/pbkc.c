#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sktc.h"
#include "cgigetval.h"
#include "html.h"

#include "ansi_colours.h"
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
	char *phonc = NULL;

	char qstr[MAX_QUERYS_LEN] = {0};
	char *qstrp;
	qstrp = qstr;

	up    = cgigetval("op");
	name  = cgigetval("name");
	last  = cgigetval("last");
	phonc = cgigetval("phon");

	up             = "LOOKUP";
	name           = "qui";
	last           = "qoo";
	phonc          = "1011111111";

	/* TODO: what is this? wrap this away */
	if ((!isfield(up, OP) || !isfield(name, NAME) || !isfield(last, LAST)))
		goto footer;
	Dlog("calling parse_up");
	parse_up(qstrp, up, phonc, name, last);
footer:
	html_footer();
	return 0;
}
