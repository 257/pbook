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
	size_t size;
	struct sockaddr_un local, pbkc;
	char buf[MAX_QUERYS_LEN] = {0};
	char *bufp = buf;
	int sock;

	fd_set active_fd_set, read_fd_set;

	Dmsg(creating the socket);
	sock = mk_socket();
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
		exit(EXIT_FAILURE);
	}
	/* Initialize the set of active sockets. */
	FD_ZERO (&active_fd_set);
	FD_SET (stdin, &active_fd_set);
	FD_SET (pbkc, &active_fd_set);
	int c;

	int done, n, s2;
	Dmsg(send 'EOF' with Ctrl-D to stop the daemon or);
	Dmsg(Press any other key to continue);

	while(1) {
		//if (((s2 = accept(s, (struct sockaddr *)&pbkc, &t)) == -1))
		read_fd_set = active_fd_set;
		Dmsg(Waiting for a connection...);
		/* Block until input arrives on one or more active sockets. */
		if (select (FD_SETSIZE, &read_fd_set, NULL, NULL, NULL) < 0) {
			perror ("select");
			exit (EXIT_FAILURE);
		}
		/* Service all the sockets with input pending. */
		for (i = 0; i < FD_SETSIZE; ++i)
			if (FD_ISSET (i, &read_fd_set)) {
				if (i == pbkc) {
					/* Connection request on original socket. */
					int new;
					size = sizeof(pbkc);
					new = accept (sock,
							(struct sockaddr *) &pbkc,
							&size);
					if (new < 0) {
						perror ("accept");
						exit (EXIT_FAILURE);
					}
					Dmsg(Connected.);
					FD_SET (new, &active_fd_set);

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
				} else {
					/* Data arriving on an already-connected socket. */
					if (read_from_client (i) < 0) {
						close (i);
						FD_CLR (i, &active_fd_set);
					}
				}
			}
	}

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
