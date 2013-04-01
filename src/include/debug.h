#ifndef  DEBUG_H
#define  DEBUG_H

#include "ansi_colours.h"

#define str(s) #s
#define MAX_FNC_NAME         12
#define MAX_NAME_NAME        10
#define DFNC_VAR_N(...)      MAX_NAME_NAME, __VA_ARGS__
#define DSTR(...)            (MAX_QUERYS_LEN/3), __VA_ARGS__
#define DEBUGn(...)          DFNC_VAR_N(str(__VA_ARGS__))
#define DEBUGfunch(...)      (DEBUGh, fprintf(stderr, "ENTERED: %-*s: ", MAX_FNC_NAME, str(__VA_ARGS__)))
#define DEBUGfunc(...)       stderr, "%*s:%*s\n", DEBUGn(__VA_ARGS__)
#define DIDEN_VALs(...)      fprintf(stderr, "%-*s = %-*s\n", DFNC_VAR_N(str(__VA_ARGS__)), DFNC_VAR_N(__VA_ARGS__))
#define DIDEN_VALd(...)      fprintf(stderr, "%-*s = %-*d\n", DFNC_VAR_N(str(__VA_ARGS__)), DFNC_VAR_N(__VA_ARGS__))
#define DIDEN_VALlld(...)    fprintf(stderr, "%-*s = %-*lld\n", DFNC_VAR_N(str(__VA_ARGS__)), DFNC_VAR_N(__VA_ARGS__))
#define DEBUGh               fprintf(stderr, BOLDWHITE "  [DEBUG]  " RESET)
#define DEBUGs(...)          (DIDEN_VALs(__VA_ARGS__))
#define DEBUGd(...)          (DIDEN_VALd(__VA_ARGS__))
#define DEBUGlld(...)        (DIDEN_VALlld(__VA_ARGS__))
#define Dmsg(...)            (DEBUGh, fprintf(stderr, str(__VA_ARGS__\n)))

#endif
