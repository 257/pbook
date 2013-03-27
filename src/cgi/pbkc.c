// #include "pb_skt.h"
#include "pbkd.h"

// #define MAX_Q_LEN ((3*MAXNAME) + 2 + 1) /* 3 fields, 2 FS, \0 */

char *
send_recv_2pbkd(char *qstrp)
{
    int s, len;
    socklen_t t;
    struct sockaddr_un remote;
    char qstr[MAX_Q_LEN];
    char *qstrp;
    qstrp = qstr;

    if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    /* TODO: write to log */
    printf("pbkc:\tTrying to connect...\n");

    remote.sun_family = AF_UNIX;
    strcpy(remote.sun_path, SOCK_PATH);
    len = strlen(remote.sun_path) + sizeof(remote.sun_family);
    if (connect(s, (struct sockaddr *)&remote, len) == -1) {
        perror("connect");
        exit(1);
    }

    /* TODO: write to log */
    printf("pbkc:\tConnected.\n");


    if (send(s, qstrp, strlen(qstrp), 0) == -1) {
            perror("send");
            exit(1);
        }
    if ((t=recv(s, qstrp, 100, 0)) > 0) {
	    qstrp[t] = '\0';
	    // TODO: take this out when you're done
	    printf("%s\n", qstr);
	    return qstrp;
    } else {
	    if (t < 0) perror("recv");
	    /* TODO: write to log */
	    else printf("pbkc:\tServer closed connection\n");
	    exit(1);
    }
    close(s);
}
