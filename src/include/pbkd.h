#ifndef PBD_H
#define PBD_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "pb_limits.h"
#include "pb_fs.h"
#include "btree.h"
#include "init_pbook.h"
#include "skts.h"


enum mode { START, KILL };

extern void    pbkd(int);
/* extern int    talk2socket(void); */
#endif
