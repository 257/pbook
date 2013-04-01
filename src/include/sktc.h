#ifndef PBK_SKTC_H
#define PBK_SKTC_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include "skt.h"


extern char *send_recv_2pbk_skt(char *, char*);

#endif
