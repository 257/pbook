#ifndef PBK_SKT_H
#define PBK_SKT_H

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include "pbkd.h"

#define MAX_SPATH_LEN  108
#define SOCK_PATH      ".pb_socket"
#define MAX_Q_LEN      5
/* 3 fields, 2 FS, \0 */
#define MAX_QUERYS_LEN ((3*MAXNAME) + 2 + 1)

int   mk_socket(void);
char *send_recv_2pbk_skt(char *);
void recv_send_2pbk_skt(char *);
extern char   *parse_op(char *buf); /* shouldn't be here */

#endif
