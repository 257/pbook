#include "pb_fs.h"

char *dir;
char *datafile;

char *
fs_house_keeping() {
	create_pbook_directory();
	set_filename();
	return datafile;

}

/* TODO: return int for debug */
void
create_pbook_directory()
{
	/*
	 * TODO: check for perms, ifexist()
	 * struct stat s;
	 */

	dir = NULL;
	dir = datafile_path;
	strcpy(dir, PREFIX_CONF);
	strcat(dir, DIR_CONF);
	mkdir(dir, 0700);
	strcat(dir, DIR_IN_CONF);
	mkdir(dir, 0700);
}

void
set_filename() {
	datafile = NULL;
	datafile = datafile_path_name;
	datafile = strcat(dir, DATA_FILE);
}

