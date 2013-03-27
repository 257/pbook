#include "skts.h"


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
	char str[MAX_QUERYS_LEN] = {0};
	char *strp = str;
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
		printf("Connected.\n");
		done = 0;
		do {
			n = recv(s2, strp, 100, 0);
			if (n <= 0) {
				if (n < 0) perror("recv");
				done = 1;
			}
			if (!done) {
				strp   = parse_op(strp);
				if (send(s2, str, n, 0) < 0) {
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
	return node2line(qnode);
}
