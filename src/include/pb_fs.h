#ifndef PB_FS_H
#define PB_FS_H
#include "std_libc.h"

#define PREFIX_CONF        getenv("PWD") /* should be modular via Makefile */
#define DIR_CONF           "/.config"
#define DIR_IN_CONF        "/pbook"
#define DATA_FILE          "/phonebook"
#define DATAFILE_PTH_LEN   (sizeof(PREFIX_CONF) + sizeof(DIR_CONF) + sizeof(DIR_IN_CONF))
#define DATAFILE_PNM_LEN   (sizeof(DATAFILE_PTH_LEN) + sizeof(DATA_FILE))

char datafile_path[DATAFILE_PNM_LEN];
char datafile_path_name[DATAFILE_PNM_LEN];

extern char *dir      ;
extern char *datafile ;

/* TODO: return int for debug */
extern void 	create_pbook_directory(void);
extern char *   fs_house_keeping(void);
extern void  	set_filename(void);
#endif
