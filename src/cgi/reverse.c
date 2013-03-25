#include <ctype.h>
#include <string.h>

upperstring(char *str)
{
	char *p;

	for(p = str; *p != '\0'; p++)
	{
		if(islower(*p))
			*p = toupper(*p);
	}
}

lowerstring(char *str)
{
	char *p;

	for(p = str; *p != '\0'; p++)
	{
		if(isupper(*p))
			*p = tolower(*p);
	}
}

int reverse(char string[])
{
	int len = strlen(string);
	int i;
	char tmp;
	
	for(i = 0; i < len / 2; i = i + 1)
	{
		tmp = string[i];
		string[i] = string[len - i - 1];
		string[len - i - 1] = tmp;
	}
	return 0;
}

