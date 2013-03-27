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
	treeprint(root, PRE);
	// init_ui(root);
	pbkd(START);
	// pbkd(KILL);
	treeprint(root, PRE);
	uinit_pbook(root);
	return 0;
}
