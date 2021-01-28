#include "ll.h"
#ifndef FS
#define FS


/* File class */
typedef struct File File;

struct File {
	char* name;
	int size;
	char* date;
};

/* Create File */
File* create_file(char*, int, char*);

/* Dir class */
typedef struct Dir Dir;

struct Dir {
	char* name;        /* Name of the directory */
	LinkedList* dirs;  /* List of directories */
	Dir* parent;       /* Pointer to the parent directory */
	LinkedList* files; /* List of directory files */
};

/* Main pointers */
extern Dir* root;
extern Dir* curr;


/* Create Dir */
Dir* create_dir(char*);

/* File functions */
char* get_fname();  /* conflicting types for ‘get_name’ in Dir class */
int get_size();
char* get_date();
void rm(const char*);
void reName(char*, char*);  /* conflicting types for ‘rename’ from <stdio.h> */

/* Dir functions */
char* get_name(void);
Dir** get_dirs(void);
File** get_files(void);
void ls(void);
void dir_tree(const char*);
void cd(const char*);

/* Extra */
char* get_args(char*, int);
char* get_cmd(char*, int);
int cmd_len(char*);
int arg_len(char*);

#endif
