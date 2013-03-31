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
		Dmsg("Waiting for a connection...\n");
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
		Dmsg("Connected.\n");
		done = 0;
		do {
			n = recv(s2, bufp, MAX_QUERYS_LEN, 0);
			bufp[n] = '\0';
			Dmsg("recv()\n");
			DEBUGs(bufp);
			if (n <= 0) {
				if (n < 0) perror("recv");
				done = 1;
			}
			if (!done) {
				DEBUGs(bufp);
				bufp   = parse_op(bufp);
				Dmsg("send()\n");
				if (send(s2, bufp, n, 0) < 0) {
					perror("send");
					done = 1;
				}
			}
		} while (!done);
	}
}

// TODO: this doesn't belong here
char *
parse_op(char *buf) {
	Dmsg("in pars_op\n");
	tnode *qnode = NULL;
	qnode = l2node(buf, delim);
	switch (qnode->op) {
		case LOOKUP:
			Dmsg("calling lookup from parse_op\n");
			if ((qnode = lookup(root, qnode)) != NULL)
				buf = node2line(qnode, delim, buf);
			break;
		case UPDATE: /* update will lookup */
			qnode = update_node(root, qnode);
			break;
		default:
			break;
	}
	return buf;
}
