#include "xctod.h"
static int xctod(int);

char *unescstring(char *src, int srclen, char *dest, int destsize)
{
	char *endp = src + srclen;
	char *srcp;
	char *destp = dest;
	int nwrote = 0;

	for(srcp = src; srcp < endp; srcp++)
	{
		if(nwrote > destsize)
			return 0;
		if(*srcp == '+')
			*destp++ = ' ';
		else if(*srcp == '%')
		{
			*destp++ = 16 * xctod(*(srcp+1)) + xctod(*(srcp+2));
			srcp += 2;
		}
		else
			*destp++ = *srcp;
		nwrote++;
	}
	
	*destp = '\0';

	return dest;
}

static int xctod(int c)
{
	if(isdigit(c))
		return c - '0';
	else if(isupper(c))
		return c - 'A' + 10;
	else if(islower(c))
		return c - 'a' + 10;
	else
		return 0;
}
