#include "init_pbook.h"
#include "ui.h"
#include "pbkd.h"

tnode *root = NULL;

int
main() {
	root = init_pbook(root);
	/* TODO: put a switch here decide
	 * whether you're client or srv
	 * if running in daemon mode
	 * you need to close the socket
	 */
	// init_ui(root);
	treeprint(root, PRE);
	pbkd(START);
	// pbkd(root, KILL);
	treeprint(root, PRE);
	uinit_pbook(root);
	return 0;
}
