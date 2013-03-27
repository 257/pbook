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

// #include "pbkd.h"

#define MAX_SPATH_LEN  108
#define SOCK_PATH      ".pb_socket"
#define MAX_Q_LEN      5
/* 3 fields, 2 FS, \0 */
#define MAX_QUERYS_LEN ((3*MAXNAME) + 2 + 1)

int   mk_socket(void);
char *send_recv_2pbk_skt(char *);

#endif
