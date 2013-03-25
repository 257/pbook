/* some limits are defined in pb_fs.h */
#ifndef PB_LIMITS_H
#define PB_LIMITS_H
/* #define MAXNAME		782 */
#define MAXNAME		20
// #define MAX_ENTL		782
/* this defined in pbookd.h as well */
#define MAX_ENTL        ((3*MAXNAME) + 2 + 1) /* 3 fields, 2 FS, \0 */

#include "std_libc.h"

#endif
