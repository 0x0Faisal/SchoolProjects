#ifndef LL
#define LL

/* Node class */
typedef struct Node Node;

struct Node {
    void* data;
    Node* previous;
    Node* next;
};

/* LinkedList calss */
typedef struct LinkedList LinkedList;

struct LinkedList{
    Node* head;
    Node* current;
};

/* Creating node */
Node* create_node(void*);

/* Creating linked list */
LinkedList* create_list(void);

/* Insert to the given linked list */
void insert(LinkedList*, void*);

/* Return the size of the given list */
int list_size(LinkedList*);

/* Removing */
void remove_node(LinkedList*, Node*);
void remove_curr(LinkedList*);

/* Moving linked list current */
void find_next(LinkedList*);
Node* findLast(LinkedList*);

/* Search set the current for node having same data if possible */
void search(LinkedList*,void*);

void help(void);
void header(void);


#endif
