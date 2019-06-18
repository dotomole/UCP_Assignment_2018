/***************************
* FILE: linked_list.h      *
* AUTHOR: Thomas Di Pietro *
* DATE: 21/10/2018         *      
***************************/
typedef struct LinkedListNode
{
    char command; /*First letter of command to differentiate later*/
    void* value; /*void* to be typecasted to appropriate type
                 and malloc'd*/
    struct LinkedListNode* next;
} LinkedListNode;

typedef struct 
{
    LinkedListNode* head;
    LinkedListNode* tail;
} LinkedList;

LinkedList* newList();
void insertLast(LinkedList* list, LinkedListNode* newNode);
void removeFirst(LinkedList* list);
LinkedListNode* getFirstElement(LinkedList* list);
