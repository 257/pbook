/* some limits are defined in pb_fs.h */
#ifndef PB_LIMITS_H
#define PB_LIMITS_H

/* #define MAXNAME		782 */
#define MAXNAME                 20
#define MAX_ENTL                ((4*MAXNAME) + 2 + 1) /* 3 fields, 2 FS, \0 */
// #define MAX_ENTL		782
/* this defined in pbookd.h as well */

#include "std_libc.h"

#include "ansi_colours.h"
#include "debug.h"

#define S_PHON    10000000000
#define F_PHON    1000000000

#define PHON_LEN  10

enum op    { NONE, LOOKUP, INS, UPDATE, DEL, BOP};

extern unsigned short int   isop(long long);
/*#define isop(...)   ((__VA_ARGS__ <= NONE) || (BOP <= __VA_ARGS__)) ? NONE : __VA_ARGS__ 
 */

//extern unsigned short int  isphon(long long);
/*
 * #define isphon(...)   ((__VA_ARGS__ <= F_PHON) || (S_PHON <= __VA_ARGS__)) ? NONE : __VA_ARGS__ 
 */

#define str(s) #s
#define BAD_NAME_ALPHA()    printf("only alpha chars!\n")
#define NO_UP()            printf("Naughty Naughty srv!\n")
#define NO_INPUT_PHON(...) printf("No %s !\n", str(__VA_ARGS__))
#define LONG_PHON()        printf("Bad phone!\nneed exactly %d digits!\n", PHON_LEN)
#define BAD_PHON_DIG()     printf("Only digits for phon, please!\n")
#define BAD_PHON_ZERO_START() printf("No phon starts with 0\n")
#define LONG_NAME(...)     printf("long long %s !\n" , str(__VA_ARGS__))
#define NO_NAME(...)       printf("No %s!, No man! Naland\n", str(__VA_ARGS__))

enum boolean { FALSE, TRUE };
extern int    isfield(char *, char *, char *, char *);
extern int    no_up(void);
extern int    isup(char *up);
extern int    long_phon(void);
extern int    bad_phon_dig(void);
extern int    isphdigit(char *, int);
extern int    phon_with_zero_start(void);
extern int    no_input_phon(void);
extern int    isph(char *);
extern int    name_is_long(char *);
extern int    is_name_alpha(char *, int);
extern int    isn(char *);
extern int    isl(char *);
extern int    no_name(void);

extern char  *mk_btreel(char *l, char *delim, int op, char *phon, char *name, char *last);
extern int    parse_up(char *, char *up, char *phonc, char *name, char *last);
extern int    waz(char *);

#endif
