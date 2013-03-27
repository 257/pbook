#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "xctod.h"

char *cgigetval(char *fieldname)
{
	int fnamelen;
	char *p, *p2, *p3;
	int len1, len2;
	static char *querystring = NULL;
	if(querystring == NULL)
	{
		querystring = getenv("QUERY_STRING");
		if(querystring == NULL)
			return NULL;
	}
	
	if(fieldname == NULL)
		return NULL;
	fnamelen = strlen(fieldname);
	
	for(p = querystring; *p != '\0';)
	{
		p2 = strchr(p, '=');
		p3 = strchr(p, '&');
		if(p3 != NULL)
			len2 = p3 - p;
		else
			len2 = strlen(p);
		
		if(p2 == NULL || p3 != NULL && p2 > p3)
		{
			/* no = present in this field */
			p3 += len2;
			continue;
		}
		len1 = p2 - p;
		
		if(len1 == fnamelen && strncmp(fieldname, p, len1) == 0)
		{
			/* found it */
			int retlen = len2 - len1 - 1;
			char *retbuf = malloc(retlen + 1);
			if(retbuf == NULL)
				return NULL;
			unescstring(p2 + 1, retlen, retbuf, retlen+1);
			return retbuf;
		}
		
		p += len2;
		if(*p == '&')
			p++;
	}

	/* never found it */
	return NULL;
}
