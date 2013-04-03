/* some limits are defined in pb_fs.h */
#ifndef PB_LIMITS_H
#define PB_LIMITS_H
/* #define MAXNAME		782 */
#define MAXNAME                 20
#define MAX_ENTL                ((4*MAXNAME) + 2 + 1) /* 3 fields, 2 FS, \0 */
// #define MAX_ENTL		782
/* this defined in pbookd.h as well */

#include "std_libc.h"

#define S_PHON    10000000000
#define F_PHON    1000000000

enum op    { NONE, LOOKUP, INS, UPDATE, DEL, BOP};

extern unsigned short int   isop(long long);
/*#define isop(...)   ((__VA_ARGS__ <= NONE) || (BOP <= __VA_ARGS__)) ? NONE : __VA_ARGS__ 
 */

//extern unsigned short int  isphon(long long);
/*
 * #define isphon(...)   ((__VA_ARGS__ <= F_PHON) || (S_PHON <= __VA_ARGS__)) ? NONE : __VA_ARGS__ 
 */

#endif
