#ifndef  DEBUG_H
#define  DEBUG_H

#define MAX_FNC_NAME         8
#define DFNC_VAR_N(...)      MAX_FNC_NAME, __VA_ARGS__
#define DSTR(...)            (MAX_QUERYS_LEN/3), __VA_ARGS__
#define DIDEN_VAL(...)       fprintf(stderr, "%*s:%*s\n", DFNC_VAR_N(str(__VA_ARGS__)) , DFNC_VAR_N(__VA_ARGS__))
#define DIDEN_VALD(...)      fprintf(stderr, "%*s:%*d\n", DFNC_VAR_N(str(__VA_ARGS__)) , DFNC_VAR_N(__VA_ARGS__))
#define DHEAD                fprintf(stderr, BOLDWHITE "  [DEBUG]  " RESET)
#define DEBUG(...)           (DHEAD, DIDEN_VAL(__VA_ARGS__))
#define DEBUGd(...)          (DHEAD, DIDEN_VALD(__VA_ARGS__))

#endif
