#ifndef UI_H
#define UI_H

#define DEL                          1
#define MAX_FILE_TXT_PATH_LEN        128
#define DATA_FILE_TXT                "/phones.txt"

#include "btree.h"

extern int     init_ui(tnode *);
unsigned int enterChoice(void);
void 	addRecord(tnode *);
void 	findPhoneNum(tnode *);
void 	updateRecord(tnode *,int);
void 	deleteRecord(tnode *);
void 	printAllToFile(tnode *);

#endif
