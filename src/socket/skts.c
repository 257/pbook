#include "skts.h"
#include "ansi_colours.h"
#include "init_pbook.h"

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

void
recv_send_2pbk_skt() {
	DEBUGfunch(recv_send_2pbk_skt);
	Done();
	int len;
	socklen_t t;
	struct sockaddr_un local, remote;
	char buf[MAX_QUERYS_LEN] = {0};
	char *bufp = buf;
	int s;

	Dmsg(creating the socket);
	s = mk_socket();
	Done();
	
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
	Dmsg(send 'EOF' with Ctrl-D to stop the daemon or);
	Dmsg(Press any other key to continue);
	//int c;
	int done, n, s2;
	Dmsg(Waiting for a connection...);
	t = sizeof(remote);
	/*
	 * When accept() returns,
	 * the remote variable will be filled
	 * with the remote side's struct sockaddr_un,
	 * and len will be set to its length.
	 * The descriptor s2 is connected to the client,
	 * and is ready for send() and recv()
	 */
	if (((s2 = accept(s, (struct sockaddr *)&remote, &t)) != -1) && ((c=getchar()) != EOF)) {
	Dmsg(Connected.);
	done = 0;
	do {
		DEBUGfunch(recv());
		n = recv(s2, bufp, MAX_QUERYS_LEN, 0);
		bufp[n] = '\0';
		DEBUGs(bufp);
		if (n <= 0) {
			if (n < 0) perror("recv");
			done = 1;
		}
		if (!done) {
			if (parse_op(bufp) == NONE) {
				char none[] = "0";
				char *nonep = none;
				strcpy(bufp, nonep);
			}
			DEBUGfunch(send());
			DEBUGs(bufp);
			if (send(s2, bufp, (strlen(bufp)+1), 0) < 0) {
				perror("send");
				done = 1;
			}
		}
	} while (!done);

		perror("accept");
		exit(1);
	close(s2);
}

// TODO: this doesn't belong here
int
parse_op(char *bufp) {
	int insbit;
	tnode *qn   = NULL;
	tnode **qnp = NULL;

	qn = l2node(bufp, delim);
	switch (qn->op) {
		case LOOKUP:
			if ((*(qnp = lookup(root, qn))) != NULL)
				bufp = nodef_print((*qnp), bufp, PHON);
			else
				insbit = NONE;
			break;
		case UPDATE:
			insbit = ins_node(root, qn);
			uinit_pbook(root);
			switch (insbit) {
				case INS:
					insbit = NONE;
					break;
				case UPDATE:
					insbit = UPDATE;
					break;
				default:
					break;
			}
		default:
			break;
	}
	free(qn);
	return insbit;
}
