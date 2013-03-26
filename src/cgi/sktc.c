#include "pbkc.h"

pbkc(void)
{
    int s, len;
    socklen_t t;
    struct sockaddr_un remote;
    char str[MAX_QUERYS_LEN];

    if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    /* TODO: write to log file */
    printf("Trying to connect...\n");

    remote.sun_family = AF_UNIX;
    strcpy(remote.sun_path, SOCK_PATH);
    len = strlen(remote.sun_path) + sizeof(remote.sun_family);
    if (connect(s, (struct sockaddr *)&remote, len) == -1) {
        perror("connect");
        exit(1);
    }

    /* TODO: write to log file */
    printf("pbkc:\tConnected.\n");
    
    if (send(s, str, strlen(str), 0) == -1) {
	    perror("send");
	    exit(1);
    }
    if ((t=recv(s, str, 100, 0)) > 0) {
	    str[t] = '\0';
	    printf("echo> %s\n", str);
    } else {
	    if (t < 0) perror("recv");
	    /* TODO: write to log file */
	    else printf("pbkc:\tServer closed connection\n");
	    exit(1);
    }
    
    close(s);
    
    return 0;
}
