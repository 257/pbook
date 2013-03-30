#include "sktc.h"
#include "ansi_colours.h"

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
	int t;
	struct sockaddr_un remote;

	// printf("%7s:%20s:\t%s\n", "sktc", "", "calling socket()...");
	s = mk_socket();
	
	/* TODO: write to log */
	// printf("%7s:%20s:\t%s\n", "sktc", "", "Trying to connect...");

	remote.sun_family = AF_UNIX;
	strcpy(remote.sun_path, SOCK_PATH);
	len = strlen(remote.sun_path) + sizeof(remote.sun_family);
	if (connect(s, (struct sockaddr *)&remote, len) == -1) {
		perror("connect");
		exit(1);
	}
	
	/* TODO: write to log */
	//printf("%7s:%20s:\t%s\n", "sktc", "send()", qstrp);
	if (send(s, qstrp, strlen(qstrp), 0) == -1) {
		perror("send");
		exit(1);
	}
	if ((t = recv(s, qstrp, MAX_QUERYS_LEN, 0)) > 0) {
		qstrp[t] = '\0';
		// TODO: take this out when you're done
		//printf("%7s:%20s:\t%s\n", "sktc", "recv()", qstrp);
		return qstrp;
	} else {
		if (t < 0) perror("recv");
		/* TODO: write to log */
		else printf(RED "pbkc:\tServer closed connection\n" RESET);
		exit(1);
	}
	close(s);
}
