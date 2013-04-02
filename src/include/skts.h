#ifndef PBK_SKT_H
#define PBK_SKT_H

#include "skt.h"
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
//#include <netinet/in.h>
//#include <netdb.h>

extern void    recv_send_2pbk_skt(void);
extern int     parse_op(char *buf); /* shouldn't be here */

#endif
