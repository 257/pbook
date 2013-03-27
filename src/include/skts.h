#ifndef PBK_SKT_H
#define PBK_SKT_H

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include "skt.h"
#include "pbkd.h"


void  recv_send_2pbk_skt(void);
extern char   *parse_op(char *buf); /* shouldn't be here */

#endif
