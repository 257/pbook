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

int
read_from_client(int filedes) {
	char buf[MAX_QUERYS_LEN] = {0};
	char *bufp = buf;
	int nbytes;
	DEBUGfunch(read());
	nbytes = read (filedes, buf, MAX_QUERYS_LEN);
	// nbytes = recv(filedes, bufffer, MAX_QUERYS_LEN, 0);
	// bufp[n] = '\0';
	if (nbytes < 0) {
	   /* Read error. */
	   perror ("read");
	   exit (EXIT_FAILURE);
	}
	else if (nbytes == 0)
	 /* End-of-file. */
	 return -1;
	else {
		DEBUGs(bufp);
		if (parse_op(bufp) == NONE) {
			char none[] = "0";
			char *nonep = none;
			strcpy(bufp, nonep);
		}
		DEBUGfunch(send());
		DEBUGs(bufp);
		if (send(filedes, bufp, (strlen(bufp)+1), 0) < 0) {
			perror("send");
		}
		return 0;
	}
}

void
recv_send_2pbk_skt() {
	DEBUGfunch(recv_send_2pbk_skt);
	Done();
	int len;
	size_t size;
	struct sockaddr_un local, pbkc;
	int sock;

	fd_set active_fd_set, read_fd_set, write_fd_set;

	Dmsg(creating the socket);
	sock = mk_socket();
	Done();
	
	local.sun_family = AF_UNIX;
	strcpy(local.sun_path, SOCK_PATH);
	unlink(local.sun_path);
	len = strlen(local.sun_path) + sizeof(local.sun_family);

	if (bind(sock, (struct sockaddr *)&local, len) == -1) {
		perror("bind");
		exit(1);
	}

	if (listen(sock, MAX_Q_LEN) == -1) {
		perror("listen");
		exit(EXIT_FAILURE);
	}
	/* Initialize the set of active sockets. */
	FD_ZERO (&active_fd_set);
	int stdinfd = fileno(stdin);
	FD_SET (stdinfd, &active_fd_set);
	FD_SET (sock, &active_fd_set);

	FD_ZERO (&write_fd_set);
	FD_SET (sock, &write_fd_set);
	Dmsg(send "EOF" with Ctrl-D to stop the daemon or);
	//Dmsg(Press any other key to continue);
	//if (((s2 = accept(s, (struct sockaddr *)&pbkc, &t)) == -1))
	read_fd_set = active_fd_set;
	Dmsg(Waiting for a connection...);
	/* Block until input arrives on one or more active sockets. */
	int sig = START;
	while(sig != EOF) {
	if (select (FD_SETSIZE, &read_fd_set, NULL, NULL, NULL) < 0) {
		perror ("select");
		exit (EXIT_FAILURE);
	}
	/* Service all the sockets with input pending. */
	int i;
	for (i = 0; i < FD_SETSIZE; ++i)
		if (FD_ISSET (i, &read_fd_set)) {
			if (i == sock) {
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
				if (read_from_client (i) < 0) {
					close (i);
					FD_SET (new, &active_fd_set);
				}
			} else if (i == stdinfd) {
				/* Data arriving on stdin. */
				int c;
				if((c=getc(stdin)) == EOF) {
					close(sock);
					i   = FD_SETSIZE;
					sig = EOF;
				}
				else
					i = 0;
			}
		}
	}
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
