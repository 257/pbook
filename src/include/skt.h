#ifndef PBK_SKTS_H
#define PBK_SKTS_H

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include "pbkd.h"

#define MAX_SPATH_LEN  108
#define UID            getuid()
#define SOCK_PATH      "/tmp/22294"
#define MAX_Q_LEN      5
/* 3 fields, 2 FS, \0 */
#define MAX_QUERYS_LEN ((3*MAXNAME) + 2 + 1)

int   mk_socket(void);
extern char   *parse_op(char *buf); /* shouldn't be here */

#endif
