#include "sktc.h"
#include "ansi_colours.h"

/* TODO: move to skt.c */
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
send_recv_2pbk_skt(char *qstrp, char *bufp) {
	int s, len;
	int t;
	struct sockaddr_un remote;

	s = mk_socket();
	
	remote.sun_family = AF_UNIX;
	strcpy(remote.sun_path, SOCK_PATH);
	len = strlen(remote.sun_path) + sizeof(remote.sun_family);
	if (connect(s, (struct sockaddr *)&remote, len) == -1) {
		perror("connect");
		exit(1);
	}
	DEBUGfunch(send());
	DEBUGs(qstrp);
	if (send(s, qstrp, strlen(qstrp), 0) == -1) {
		perror("send");
		exit(1);
	}
	DEBUGs(bufp);
	if ((t = recv(s, bufp, MAX_QUERYS_LEN, 0)) > 0) {
		DEBUGfunch(recv());
		bufp[t] = '\0';
		DEBUGs(bufp);
		return bufp;
	} else {
		if (t < 0) perror("recv");
		/* TODO: write to log */
		else printf(RED "pbkc:\tServer closed connection\n" RESET);
		exit(1);
	}
	close(s);
}
