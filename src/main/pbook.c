#include "init_pbook.h"
#include "ui.h"
#include "pbookd.h"

tnode *root = NULL;

int
main() {
	init_pbook();
	/* TODO: put a switch here decide
	 * whether you're client or srv
	 * if running in daemon mode
	 * you need to close the socket
	 */
	treeprint(root, PRE);
	// init_ui(root);
	// pbookd(START);
	// pbookd(KILL);
	uinit_pbook(root);
	return 0;
}
