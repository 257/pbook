#include "init_pbook.h"
#include "debug.h"

char *dir;
char *datafile;

FILE  *dbfp;

tnode *
init_pbook(tnode *root) { /* this root will ``shadow'' global root */
	//load_pbook(datafile, RB)
	datafile = fs_house_keeping();
	dbfp = fopen(datafile, "r");
	if(dbfp == NULL) {
		Dmsg(dbfp is null);
		exit(EXIT_FAILURE);
	}
	root = grow_btree(dbfp, root);
	fclose(dbfp);
	return root;
}
/* TODO: return int for debug */
char *
uinit_pbook(tnode *root) {
	// load_pbook(datafile, WB);
	datafile = fs_house_keeping();
	dbfp = fopen(datafile, "wb");
	ugrow_btree(root, dbfp);
	fclose(dbfp);
	return datafile;
}
int
load_pbook(char *datafile, int prm) {
	int ret = 0;
	/* if(database != NULL)
		close_database();
		*/
	switch (prm) {
		case RB:
			if ((dbfp = fopen(datafile, "r+b")) == NULL) {
				puts("File cannot be opened.\n");
				// printf("in load_pbook RB\n");
				ret = RB;
			}
			break;
		case WB:
			if ((dbfp = fopen(datafile, "wb")) == NULL) {
				puts("File cannot be opened.\n");
				// printf("in load_pbook WB\n");
				ret = WB;
			}
			break;
		default:
			break;
	}
	return ret;
}
