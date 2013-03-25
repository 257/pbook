#include "pbookd.h"


extern int s, s2;
int s, s2;

/* backgroud mode, needs signal() */
void
pbookd(int mode) {
	int c;
	switch (mode) {
		case START:
			mk_socket();
			printf("send EOF, Ctrl-D, to stop pbd\n");
			while ((c = getchar()) != EOF)
				recv_send_2pbc();
			printf("caught EOF, closing pbd\n");
			break;
		case KILL:
			close(s2);
			break;
		default:
			close(s2);
			break;
	}
}

/* TODO: put in ./socket/ */

void
mk_socket() {
	int len;

	if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}

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
}

void
recv_send_2pbc() {
	socklen_t t;
	char qstr[MAX_QUERYS_LEN];
	char *rstr;
	/*
	 * This will accept a connection from a client.
	 * This function returns another socket descriptor!
	 * The old descriptor is still listening for new connections,
	 * but this new one is connected to the client:
	 */
	for(;;) {
		int done, n;
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
			n = recv(s2, qstr, 100, 0);
			if (n <= 0) {
				if (n < 0) perror("recv");
				done = 1;
			}
			if (!done) {
				tnode *cgi_node = NULL;
				cgi_node = line2node(qstr);
				int treeop;
				treeop = parse_op(cgi_node);
				rstr   = do_treeop(root, cgi_node, treeop);
				if (send(s2, rstr, n, 0) < 0) {
					perror("send");
					done = 1;
				}
			}
		} while (!done);
	}
}

/*TODO: put in ./ui/ */

int
parse_op(tnode *node) {
	return (strcmp(node->phon, "0") == 0) ? LOOKUP : UPDATE;
}

char *
do_treeop(tnode *root, tnode *node, int treeop) {
	switch (treeop) {
		case UPDATE:
			node = update_node(root, node);
			break;
		case LOOKUP:
			node = lookup(root, node);
			break;
		default:
			break;
	}
	return node2line(node);
}

