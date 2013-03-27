#include "sktc.h"


int
mk_socket() {
	int s;
	if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}
	return s;
}

char *
send_recv_2pbk_skt(char *qstrp) {
	int s, len;
	socklen_t t;
	struct sockaddr_un remote;

	s = mk_socket();
	
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
		printf("%s\n", qstrp);
		return qstrp;
	} else {
		if (t < 0) perror("recv");
		/* TODO: write to log */
		else printf("pbkc:\tServer closed connection\n");
		exit(1);
	}
	close(s);
}
