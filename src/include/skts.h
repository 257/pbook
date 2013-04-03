#ifndef PBK_SKTS_H
#define PBK_SKTS_H

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
//#include <netinet/in.h>
//#include <netdb.h>

#include "skt.h"
#include "pbkd.h"
extern void    recv_send_2pbk_skt(void);
extern int     parse_op(char *buf); /* shouldn't be here */

#endif
