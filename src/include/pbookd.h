#ifndef PBOOKD_H
#define PBOOKD_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
// open(2) needs
#include <sys/stat.h>
#include <fcntl.h>

#include "pbook_limits.h"
#include "pb_fs.h"
#include "btree.h"
#include "init_pbook.h"

#define MAX_SPATH_LEN  108
#define SOCK_PATH      ".pb_socket"
#define MAX_Q_LEN      5
/* 3 fields, 2 FS, \0 */
#define MAX_QUERYS_LEN ((3*MAXNAME) + 2 + 1)


enum mode { START, KILL };
struct sockaddr_un local, remote;



extern void   pbkd(int);
extern void   mk_socket(void);
extern void   recv_send_2pbkc(void);
extern int    parse_op(tnode *);
extern char * do_treeop(tnode *, tnode *, int);
/* extern int    talk2socket(void); */
#endif
