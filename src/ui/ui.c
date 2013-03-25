#include "ui.h"

unsigned int enterChoice(void)
{
    unsigned int menuChoice; //variable to store user's choice

   // display available options
   printf("Enter your choice:\n");
   printf("1 --- add a new phone record\n");
   printf("2 --- find a phone number of a given user \n");
   printf("3 --- update the phone record \n");
   printf("4 --- delete a phone record\n");
   printf("5 --- list all phone records in a text file \"phones.txt\" for printing \n");
   printf("6 --- end program\n");

   scanf(" %u", &menuChoice); //receive choice from user
   return menuChoice;

}
int
init_ui(tnode *root) {
	int ret = 0;
	unsigned int choice;
	while( (choice = enterChoice() ) !=6 ) {
		switch(choice) {
			case 1:
				addRecord(root);
				break;
			case 2:
				findPhoneNum(root);
				break;
			case 3:
				updateRecord(root, !DEL);
				break;
			case 4:
				deleteRecord(root);
				break;
			case 5:
				printAllToFile(root);
				break;
			default:
				puts("Incorrect choice.");
				ret = 1;
				break;
		}
	}
	return ret;
}

void addRecord(tnode *root) {
	/* TODO: abstracted out this storage allocation */
	tnode *prot, *q;
	prot = q = NULL;
	char name[MAXNAME];
	char last[MAXNAME];
	char phon[MAXNAME];
	printf("Last\t: ");
	while(!pb_getline(last, MAXNAME));
	printf("Name\t: ");
	while(!pb_getline(name, MAXNAME));
	printf("Phone\t: ");
	while(!pb_getline(phon, MAXNAME));
	prot = mk_node(prot, phon, name, last, NOHITS);
	q = prot;
	q = lookup(root, q);
	/* TODO: put a switch here for god's sake */
	if (q->count == 0) {
		prot->count++;
		if (ins_node(root, prot) == 0)
			printf("\nrecord was added for:\t%s %s\n\n", prot->last, prot->name);
	} else if (q->count == 1) {
		printf("Notice:\tFound %d exact match!\n", q->count);
		printf("Name\t: %s\n", node_print(q, NAME));
		printf("Last\t: %s\n", node_print(q, LAST));
		if (strcmp(q->phon, prot->phon) == 0) {
			printf("the phone number you \n");
			printf("entered is the _same_\n");
			printf("as the one on the record\n");
			printf("choose 3 from menu to update\n");
		} else {
			printf("the phone number you \n");
			printf("entered is the _different_\n");
			printf("as the one on the record\n");
			printf("choose 3 from menu to update\n");
		}
	} else if (q->count > 1) {
		printf("Notice:\tFound 0 exact match!\n");
		printf("Notice:\tFound %d name matches!\n", q->count);
	}
}

void findPhoneNum(tnode *root) {
	/* TODO: abstracted out this storage allocation */
	tnode *q;
	q = NULL;
	char name[MAXNAME];
	char last[MAXNAME];
	char phon[MAXNAME];
	printf("Last\t: ");
	while(!pb_getline(last, MAXNAME));
	printf("Name\t: ");
	while(!pb_getline(name, MAXNAME));
	q = mk_node(q, phon, name, last, NOHITS);
	q = lookup(root, q);
	if (q->count == 1) {
		printf("Phone\t: %s\n", node_print(q, PHON));
	}
	else if (q->count == 0) {
		printf("\n\nno record was found!\n\n");
	}
}

void updateRecord(tnode *root, int dbit) {
	/* TODO: abstracted out this storage allocation */
	tnode *prot, *q;
	prot = q = NULL;
	char name[MAXNAME];
	char last[MAXNAME];
	char phon[MAXNAME];
	printf("Last\t: ");
	while(!pb_getline(last, MAXNAME));
	printf("Name\t: ");
	while(!pb_getline(name, MAXNAME));
	switch (dbit) {
		case (!DEL):
			printf("Phone\t: ");
			while(!pb_getline(phon, MAXNAME));
			break;
		case (DEL):
			strcpy(phon, "deleted");
			break;
		default:
			break;
	}
	prot = mk_node(prot, phon, name, last, NOHITS);
	q = prot;
	q = lookup(root, q);
	switch (q->count) {
		case HITS:
			if (strcmp(prot->phon, q->phon) == 0) {
				printf("the phone number you ");
				printf("entered is the _same_ ");
				printf("as the one on the record\n");
				printf("\nno update is required.\n\n");
			} else {
				q->phon = strdup(prot->phon);
				printf("\nrecord has been updated for:\t%s %s\n\n", prot->last, prot->name);
			}
			break;
		case NOHITS:
		default:
			printf("\nno record was found for:\t%s %s\n\n", prot->last, prot->name);
			printf("choose 1 from menu if you want to add a new record\n");
			break;
	}
}
void deleteRecord(tnode *root) {
	updateRecord(root, DEL);
}
void printAllToFile(tnode *root) {
	/*
	char datafile_txt[DATAFILE_PNM_LEN];
	char pwd[DATAFILE_PTH_LEN] = getenv("PWD"); we use PWD since we want user
				       have the txt file handy for print.
				       */
	char pwd[MAX_FILE_TXT_PATH_LEN];
	char *pwdp   = NULL;
	char *txtfnp = NULL;
	FILE *txtffp = NULL;

	pwdp  = strcpy(pwd, getenv("PWD"));
	txtfnp = strcat(pwdp, DATA_FILE_TXT);
	txtffp = fopen(txtfnp, "wb");
	// fclose(txtffp);
	tree_fprintf(root, IN, stdout);
	tree_fprintf(root, IN, txtffp);
	printf("\tthe data was written into\n" );
	printf("\t%s\n\tfor printing\n", txtfnp);
	fclose(txtffp);
}
