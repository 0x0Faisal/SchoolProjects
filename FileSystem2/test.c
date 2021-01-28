#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fs.h"

#define NAME 200
#define CMD 50


Dir* root;
Dir* curr;

int main() {
    curr = root = NULL;
    header();
    printf("Linux terminal like file system\nBY GROUP #12 \"-h\" for help \n");
    Dir* dir = create_dir("~");
    if(!dir) {
        printf("couldn't create \"~\" directory \n");
        return 1;
    }
    
    Dir** dirs = NULL; File** files = NULL;
    
    
    while(1) {
        /* Printing path */
        Dir* p = curr;
        LinkedList* ll = create_list();
        if(!ll){ printf("Path issue \n"); break;}
        insert(ll, "# ");
        while(p){
            insert(ll, p->name);
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
                
        char* command = (char*) calloc (CMD, sizeof(char));
        char* name = (char*) calloc (NAME, sizeof(char));
        if(!command || !name) { printf("Memory error \n"); return 1; }
        /*scanf("%s%c", command);*/
        /*fgets(command, 100, stdin);*/
        char* cmd = calloc(CMD, sizeof(char));
        fgets(cmd, 100, stdin);
        /* Skip if enter */
        /*if(!strncmp("\n", command, 3)) continue;
        */if(!strncmp("\n", cmd, 3)) continue;

        /*command[strcspn(command, "\n")] = 0;*/
        cmd[strcspn(cmd, "\n")] = 0;
        int clen = cmd_len(cmd);
        int alen = arg_len(cmd);

        command = get_cmd(cmd, clen);
        name    = get_args(cmd, alen);

        /* cd  */
        if(!strncmp("cd", command, 3)){
            /*scanf("%s", name);*/
            cd(name);
        }
        /* dir_tree printing current tree */
        else if(!strncmp("dir_tree", command, 12) ||!strncmp("tree", command, 5)) {
            scanf("%s", name);
            dir_tree(name);
        }
        /* Create directory */
        else if(!strncmp("create_dir", command, 10) || !strncmp("mkdir", command, 6)){
            /*scanf("%s", name);*/
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
            /*scanf("%s", name);*/
            rm(name);
        }
        /* reName to rename a file */
        else if(!strncmp("reName", command, 7) || !strncmp("rename", command, 7)){
            char old_name[NAME];
            fscanf(stdin, "%s %s", old_name, name);
            reName(old_name, name);
        }
        /* get_fname to get current file name */
        else if(!strncmp("get_fname", command, 10)){
            if(curr->files->head)
                printf("The name of file is: %s \n", get_fname());
        }
        /* get_size to get current file size */
        else if(!strncmp("get_size", command, 10)) {
            if(curr->files->head)
                printf("The size of \"%s\"> %d MB \n", get_fname(), get_size());
        }
        /* get_date to get current file date */
        else if(!strncmp("get_date", command, 10)) {
            if(curr->files->head)
                printf("The date of \"%s\": %s \n", get_fname(), get_date());
        }
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
        /* pwd for printing current directory */
        else if(!strncmp("pwd", command, 4))
            printf("Comming soon .. \n");
        else if(!strncmp("clear", command, 5))
            system("clear");
        /* -h for show all command */
        else if(!strncmp("-h", command, 3))
            help();
        /* exit for exit */
        else if(!strncmp("exit", command, 5))
            break;
        else
            printf("Command \"%s\" not found \n", command);
        free(cmd);
    }

    /* clean up */
    free(dirs); free(files); free(root); 
    /*system("make CLEAN");*/
    
    return 0;
}

