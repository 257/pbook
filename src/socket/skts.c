#include "skts.h"
#include "ansi_colours.h"


int
mk_socket() {
	if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}
	return s;
}

void
recv_send_2pbk_skt() {
	socklen_t t;
	struct sockaddr_un local, remote;
	char buf[MAX_QUERYS_LEN];
	char *bufp = buf;
	int s;

	s = mk_socket();
	
	local.sun_family = AF_UNIX;
	strcpy(local.sun_path, SOCK_PATH);
	unlink(local.sun_path);
	len = strlen(local.sun_path) + sizeof(local.sun_family);

	if (bind(s, (struct sockaddr *)&local, len) == -1) {
		perror("bind");
		exit(1);
	}

	if (listen(s, MAX_Q_LEN) == -1) {
		perror("listen");
		exit(1);
	}
	/*
	 * This will accept a connection from a client.
	 * This function returns another socket descriptor!
	 * The old descriptor is still listening for new connections,
	 * but this new one is connected to the client:
	 */
	for(;;) {
		int done, n, s2;
		printf("\t\nWaiting for a connection...\n");
		t = sizeof(remote);
		/*
		 * When accept() returns,
		 * the remote variable will be filled
		 * with the remote side's struct sockaddr_un,
		 * and len will be set to its length.
		 * The descriptor s2 is connected to the client,
		 * and is ready for send() and recv()
		 */
		if ((s2 = accept(s, (struct sockaddr *)&remote, &t)) == -1) {
			perror("accept");
			exit(1);
		}
		printf("\t\nConnected.\n");
		done = 0;
		do {
			n = recv(s2, bufp, MAX_QUERYS_LEN, 0);
			bufp[n] = '\0';
			printf("%7s:%20s:\t%s\n", "skts", "recv()", bufp);
			if (n <= 0) {
				if (n < 0) perror("recv");
				done = 1;
			}
			if (!done) {
				bufp   = parse_op(bufp);
				printf("%7s:%20s:\t%s\n", "skts", "send()", bufp);
				if (send(s2, bufp, n, 0) < 0) {
					perror("send");
					done = 1;
				}
			}
		} while (!done);
	}
}

char *
parse_op(char *buf) {
	tnode *qnode = NULL;
	qnode = l2node(buf, delim);
	switch (qnode->op) {
		case UPDATE:
			qnode = update_node(root, qnode);
			break;
		case LOOKUP:
			qnode = lookup(root, qnode);
			break;
		default:
			break;
	}
	buf = node2line(qnode, delim, buf);
	return buf;
}
