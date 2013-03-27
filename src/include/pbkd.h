#ifndef PBOOKD_H
#define PBOOKD_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "pb_limits.h"
#include "pb_fs.h"
#include "btree.h"
#include "init_pbook.h"
#include "skts.h"
// #include "pb_skt.h"



enum mode { START, KILL };

int s, len;
socklen_t t;
struct sockaddr_un remote;


extern tnode *root;


extern void    pbkd(int);
/* extern int    talk2socket(void); */
#endif
