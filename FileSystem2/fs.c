#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fs.h"

/* Allocate a file */
File* create_file(char* name, int size, char* date) {
	File* f = (File *) malloc (1 * sizeof(File));
	if(!f) return NULL;
	if(curr) 
		insert(curr->files, f);
	f->name = name;
	f->size = size;
	f->date = date;
	return f;
}

char* get_fname() {
    return ((File*)(curr->files->current->data))->name;
}

int get_size() {
    return ((File*)(curr->files->current->data))->size;
}

char* get_date() {
    return ((File*)(curr->files->current->data))->date;
}

void rm(const char* file_name) { 
    Node *p = curr->files->head;
    while(p) {
   	    if(!strcmp(((File*)(p->data))->name, file_name)) {
		    /*free(p->data);*/
		    remove_node(curr->files, p);
	   	    return ;
        }
        p = p->next;
    }
    printf("cannot remove '%s': No such file \n", file_name);
}

void reName(char* old_name, char* new_name) {
    Node* p = curr->files->head;
    while(p)
    {
        if(!strcmp(((File*)p->data)->name, old_name))
        {
            ((File*)p->data)->name = new_name;
            return;
        }
        p=p->next;
    }
    printf("\"%s\" not found to be renamed \n", old_name);
}

Dir* create_dir(char* name) { 
    Dir* dir = (Dir *) calloc (1, sizeof(Dir));
    if(!dir) return NULL;
    dir->name = name;
    dir->dirs = create_list();
    dir->files = create_list();
    if(!curr){
        dir->parent = NULL;
        curr = root = dir;
    }
    else {
        insert(curr->dirs, dir);
	if(curr == root)
		dir->parent = root;
	else
        	dir->parent = curr;
    }
    return dir;
}

char* get_name() { 
    return curr->name;
}

Dir** get_dirs() {
    LinkedList* ll = curr->dirs;
    int i = list_size(ll);
    if(!i) return NULL;
    Dir** dirs = (Dir**) calloc (i+1, sizeof(Dir*));
    if(dirs) {
        Node* p = ll->head;
        int i = 0;
        while(p) {
            dirs[i] = (Dir*)p->data;
            i++;
            p = p->next;
        }
    }
    return dirs;

}

File** get_files() {
    LinkedList* ll = curr->files;
    int i = list_size(ll);
    if(!i) return NULL;
    File** files = (File **) calloc (i+1, sizeof(File*));
    if(!files) return NULL;
    i = 0;
    Node* p = ll->head;
    while(p) {
        files[i] = (File *) p->data;
	i++;
        p = p->next;
    }
    return files;
}

void ls() { 
    /* Printing path */
    Dir* p = curr;
    LinkedList* ll = create_list();
    if(!ll){ printf("Can't create this list \n"); return ;}
    insert(ll, "#\n");
    while(p){
        insert(ll, p->name);
        if(p->parent)
            insert(ll, "/");
        p = p->parent;
    }
    Node* q = ll->head;
    while(q->next) q = q->next;
    
    printf("Index of: ");
    while(q){
        printf("%s", (char *)q->data);
        q = q->previous;
    }
    /* End of header */
    ll = NULL; q = NULL; 
    ll = curr->files;
    q = ll->head;
    while(q) {
	File* f = (File *) q->data;
        printf("\t  %d  %s \n", f->size, f->name);
        q = q->next;
    }
    ll = NULL; q = NULL;
    ll = curr->dirs;
    q = ll->head;
    if(curr != root)
	printf("\t<DIR>  .. \n");
    if(q) {
        while(q) {
            printf("\t<DIR>  %s \n", ((Dir *)(q->data))->name);
            q = q->next;
        }
    }
    /*free(ll);*/
    printf("\n");
}


void dir_tree(const char* dir_name) { 
    /* Searching for the given name directory at the current directory */
    Node* p = curr->dirs->head;
    Dir* q = NULL;
    if(!strcmp(dir_name, curr->name))
    	q = curr;
    else {
    	while(p) {
        	if(!strcmp(((Dir *)p->data)->name, dir_name)) {
           		q = ((Dir*)p->data);
            		break;
            	}
        	p = p->next;
    	}

    	if(!q) {
		printf("Directory is not found\n");
		return ;
    	}
    }
    /* Inserting the path of the directory into linked list */
    LinkedList* ll = create_list();
    if(!ll) { perror("error creating the list"); return ; }
    while(q) {
        insert(ll,q);
        q = q->parent;
    }

    /* Printing the tree */
    int i = 0;
    p = findLast(ll);
    while(p) {
	    q = (Dir*) p->data;
	    int j;
	    for(j = i; j > 0; j--)
		    printf("   ");
	    printf("|_ %s#\n", q->name);
	    p = p->previous;
	    i++;
	    Node* tmp = q->dirs->head;
	    while(tmp && p) {
		    if(tmp->data != p->data){
			    for(j = i; j > 0; j--)
				    printf("   ");
			    printf("|_ %s\n",((Dir*) tmp->data)->name);
		   }
		   tmp = tmp->next;
	    }
    }
    /*free(ll); */
}


void cd(const char* dir_name) {
    if(!strcmp(dir_name, "..")) {
        if(!curr || !curr->parent){
            printf("You are alrady at the root \n");
            return ;
        }
        curr = curr->parent;
    }
    else if(!strcmp(dir_name, "~"))
		    curr = root;

    else {
        Dir* dir = NULL, *tmp;
        Node* current = curr->dirs->head;
        while(current) {
            tmp =  (Dir *) current->data;
            if(!strcmp(tmp->name, dir_name)){
                dir = tmp;
                break;
            }
            current = current->next;
        }
        if(!dir) {
            File* ftmp, *file = NULL;
            current = curr->files->head;
            while(current) {
                ftmp = (File *) current->data;
                if(!strcmp(ftmp->name, dir_name)){
                    file = ftmp;
                    break;
                }
                current = current->next;
            }
            if(!file) {
                printf("No such file or directory \n");
                return ;
            }
	    curr->files->current = current;
            printf("The current file is \"%s\" \n", file->name);
            return ;
        }
        curr = dir;
    }
}







