#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include "pbook_limits.h"

#define SOCK_PATH "echo_socket"

#define MAX_Q_LEN ((3*MAXNAME) + 2 + 1) /* 3 fields, 2 FS, \0 */

enum op { ADD, UPDATE };

char *
send_recv_2pbd(char *phon, char *name, char *last, int op)
{
    int s, t, len;
    struct sockaddr_un remote;
    char qstr[MAX_Q_LEN]

    if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    printf("Trying to connect...\n");

    remote.sun_family = AF_UNIX;
    strcpy(remote.sun_path, SOCK_PATH);
    len = strlen(remote.sun_path) + sizeof(remote.sun_family);
    if (connect(s, (struct sockaddr *)&remote, len) == -1) {
        perror("connect");
        exit(1);
    }

    printf("Connected.\n");

    (op == UPDATE) ? strcpy(qstr, phon) : strcpy(qstr, "!phon");
    strcat(qstr, ":");
    strcat(qstr, name);
    strcat(qstr, ":");
    strcat(qstr, last);

    if (send(s, qstr, strlen(q), 0) == -1) {
            perror("send");
            exit(1);
        }
    if ((t=recv(s, qstr, 100, 0)) > 0) {
	    qstr[t] = '\0';
	    // TODO: take this out when you're done
	    printf("%s\n", qstr);
	    return qstr;
    } else {
	    if (t < 0) perror("recv");
	    else printf("Server closed connection\n");
	    exit(1);
    }
    close(s);
}
