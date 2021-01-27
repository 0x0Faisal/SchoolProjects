#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fs.h"

#define NAME 200
#define CMD 50

/* We will remove this */
void print_dirs(Dir**);
void print_files(File**);
void print_path();

int main() {
	
	printf("Linux terminal like file system\nBY GROUP #12 \"-h\" for help \n");
	Dir* dir = create_dir("~");
	if(!dir) {
		printf("couldn't create \"~\" directory \n");
		return 1;
	}
	
	Dir** dirs = NULL; File** files = NULL;
	
	
	while(1) {
		print_path();
		printf("Here # ");
		char* command = (char*) calloc (CMD, sizeof(char));
		char* name = (char*) calloc (NAME, sizeof(char));
		if(!command || !name) { printf("Memory error \n"); return 1; }
		scanf("%s", command);
		
		/* cd  */
		if(!strncmp("cd", command, 3)){
			scanf("%s", name);
			cd(name);
		}
		/* dir_tree printing current tree */
		else if(!strncmp("dir_tree", command, 12) ||!strncmp("tree", command, 5)) {
			scanf("%s", name);
			dir_tree(name);
		}
		/* Create directory */
		else if(!strncmp("create_dir", command, 10) || !strncmp("mkdir", command, 6)){
			scanf("%s", name);
			create_dir(name);
		}
		/* Create file */
		else if(!strncmp("create_file", command, 12) || !strncmp(">", command, 2) || !strncmp("touch", command, 6)) {
			int size; char date[15];
			printf("Enter file name, size and date > ");
			fscanf(stdin, "%s %d %s", name, &size, date);
		       	/*ungetc('\n', stdin);*/
			create_file(name, size, date);
		}
		/* rm removes a file*/
		else if(!strncmp("remove", command, 7) || !strncmp("rm", command, 3)){
			scanf("%s", name);
			rm(name);
		}
		/* reName to rename a file */
		else if(!strncmp("reName", command, 7) || !strncmp("rename", command, 7)){
			char old_name[NAME];
			fscanf(stdin, "%s %s", old_name, name);
			reName(old_name, name);
		}
        	/* get_fname to get current file name */
		else if(!strncmp("get_fname", command, 10))
			printf("The name of file is: %s \n", get_fname());
        	/* get_size to get current file size */
		else if(!strncmp("get_size", command, 10))
			printf("The size of \"%s\"> %d MB \n", get_fname(), get_size());
		/* get_date to get current file date */
		else if(!strncmp("get_date", command, 10))
			printf("The date of \"%s\": %s \n", get_fname(), get_date());
		/* ls  */
        	else if(!strncmp("ls", command, 3))
			ls();
		/* get_name name if current directory */
		else if(!strncmp("get_name", command, 9))
			printf("The name of current directory is: %s \n", get_name());
		/* get_dirs save all directories of the current in a precise array of pointers */
		else if(!strncmp("get_dirs", command, 9))
			dirs = get_dirs();
		else if(!strncmp("get_files", command, 10))
			files = get_files();
		/* -h for show all command */
		else if(!strncmp("-h", command, 3))
			help();
		/* exit for exit */
		else if(!strncmp("exit", command, 5))
			break;
		else
			printf("Command \"%s\" not found \n", command);
		free(command);
	}

	print_dirs(dirs);
	print_files(files);
	
	
	/* clean up */
	free(dirs); free(files); free(root); 
	
	return 0;
}

void print_path(){
	/* Printing path */
		Dir* p = curr;
		LinkedList* ll = create_list();
		if(!ll){ printf("Path issue \n"); return ;}
		insert(ll, "# ");
		while(p){
			insert(ll, p->name);
			printf("done insert \n");
			if(p->parent)
			    insert(ll, "/");
			p = p->parent;
		}
		Node* q = ll->head;
		while(q->next) q = q->next;
		   
		while(q){
			printf("%s", (char *)q->data);
			q = q->previous;
		}
		free(ll);
}

void print_dirs(Dir** dir){
	printf("Printing Directory ... \n");
	if(!dir){ printf("No Directory \n"); return ; }
	int i = 0;
	while(dir[i]) {
		printf("\t<DIR> %s \n", dir[i]->name);
		i++;
	}
	printf("\n");
}	

void print_files(File** files){
	printf("Printing files ... \n");
	if(!files) { printf("No files \n"); return ; }
	int i = 0;
	while(files[i]) {
		printf("\t%d  %s \n", files[i]->size, files[i]->name);
		i++;
	}
	printf("\n");
}	

