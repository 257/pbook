#ifndef  DEBUG_H
#define  DEBUG_H

#include "ansi_colours.h"

#define str(s) #s
#define MAX_FNC_NAME         8
#define DFNC_VAR_N(...)      MAX_FNC_NAME, __VA_ARGS__
#define DSTR(...)            (MAX_QUERYS_LEN/3), __VA_ARGS__
#define DEBUGn(...)          DFNC_VAR_N(str(__VA_ARGS__))
#define DEBUGfunch(...)      (DEBUGh, fprintf(stderr, str(ENTERED:  __VA_ARGS__ \n)))
#define DEBUGfunc(...)       stderr, "%*s:%*s\n", DEBUGn(__VA_ARGS__)
#define DIDEN_VALs(...)      fprintf(stderr, "%*s:%*s\n", DFNC_VAR_N(str(__VA_ARGS__)), DFNC_VAR_N(__VA_ARGS__))
#define DIDEN_VALd(...)      fprintf(stderr, "%*s:%*d\n", DFNC_VAR_N(str(__VA_ARGS__)), DFNC_VAR_N(__VA_ARGS__))
#define DEBUGh               fprintf(stderr, BOLDWHITE "  [DEBUG]  " RESET)
#define DEBUGs(...)          (DEBUGh, DIDEN_VALs(__VA_ARGS__))
#define DEBUGd(...)          (DEBUGh, DIDEN_VALd(__VA_ARGS__))
#define Dmsg(...)            (DEBUGh, fprintf(stderr, str(__VA_ARGS__\n)))

#endif
