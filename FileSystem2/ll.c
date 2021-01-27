#include <stdlib.h>
#include <stdio.h>
#include "ll.h"

Node* create_node(void* data){
    Node* n= (Node *) malloc (1 * sizeof(Node));
    n->data=data;
    return n;
}

LinkedList* create_list() {
    return (LinkedList *) malloc (1 * sizeof(LinkedList));
}

int is_empty(LinkedList* l){
    return !l->head;
}

void insert(LinkedList* l,void* data){
    Node* n = create_node(data);
    if(!n)
        return;
    if(is_empty(l)){
        l->head = n;
	l->current = n;
	l->head->previous = NULL;
    }
    else {
        Node* current = l->head;
        while (current->next != NULL)
            current = current->next;
        l->current = n; 
	current->next = n;
        n->previous = current;
    }
}


void search(LinkedList* l,void* data){
    Node* current = l->head;
    while(current){
        if(data == current->data)
            l->current = current;
        current = current->next;
    }
    return ;
}

void remove_node(LinkedList* l, Node* data) {
	if(!data || !l->current) return ;
	l->current = data;
	remove_curr(l);
}


void remove_curr(LinkedList* ll) {
	if(!ll->current)
		return ;
	Node* n = ll->current;
	if(n == ll->head)
		ll->current = ll->head = n->next;
	else {
		n->previous->next = n->next;
		ll->current = n->next;
		if(!ll->current)
			ll->current = ll->head;
		else
			ll->current->previous = n->previous;
	}
	/*free(n);*/
}

/* Find the next node of possible otherwise the head */
void find_next(LinkedList* ll) {
	if(!ll->current->next)
		ll->current = ll->head;
	else
		ll->current = ll->current->next;
}

/* More */   

int list_size(LinkedList* ll) {
	Node* p = ll->head;
	int i = 0;
	while(p) {
		i++;
		p = p->next;
	}
	return i;
}

Node* findLast(LinkedList*ll) {
    Node * a = ll->current;
    while(a->next)
    {
        a=a->next;
    }
    ll->current = a;
    return a;
}

void header(){
	printf(
"╔═══╦══╦╗  ╔═══╗╔═══╦╗──╔╦═══╦════╦═══╦═╗╔═╗ ╔═══╗\n"
"║╔══╩╣╠╣║  ║╔══╝║╔═╗║╚╗╔╝║╔═╗║╔╗╔╗║╔══╣║╚╝║║ ║╔═╗║\n"
"║╚══╗║║║║  ║╚══╗║╚══╬╗╚╝╔╣╚══╬╝║║╚╣╚══╣╔╗╔╗║ ╚╝╔╝║\n"
"║╔══╝║║║║ ╔╣╔══╝╚══╗║╚╗╔╝╚══╗║ ║║ ║╔══╣║║║║║ ╔═╝╔╝\n"
"║║  ╔╣╠╣╚═╝║╚══╗║╚═╝║ ║║ ║╚═╝║ ║║ ║╚══╣║║║║║ ║║╚═╗\n"
"╚╝  ╚══╩═══╩═══╝╚═══╝ ╚╝ ╚═══╝ ╚╝ ╚═══╩╝╚╝╚╝ ╚═══╝\n");
}

void help() {

	printf("This is \"File system 2\" project and you can use any function name in Dir and File class\n"
   " \n   create_file, touch, >                  :creat a file and it will ask for file's detail\n"
   "   create_dir, mkdir  [dir_name]           :create a directory with dir_name name in the current directoeey\n"
   "   cd [name]                               :change curr (current directory) and if the name is for file another current will point to this file\n"
   "   dir_tree, tree  [dir_name]              :print a tree for given directory name if found in current directory\n"
   "   ls                                      :list all the files and directories at the current directory(as index of)\n"
   "   get_name                                :return and print the current directory name\n"
   "   get_dirs                                :save all directories of the current in a precise size of array of pointers to directories\n"
   "   get_files                               :save all files of the current in a precise size of array of pointers to files\n"
   "   reName, rename [old_name] [new_name]    :change name of file having 'old_name' with 'new_name'\n"
   "   rm, remove [file_name]                  :remove the file_name file if possible\n"
   "   get_fname                               :retrun and print the file's name\n"
   "   get_size                                :return and print the file's size\n"
   "   get_date                                :return and print the fil's date\n"
   "   exit                                    :exit from this program\n\n");

} 





