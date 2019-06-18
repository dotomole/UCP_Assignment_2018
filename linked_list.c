/***************************
* FILE: linked_list.c      *
* AUTHOR: Thomas Di Pietro *
* DATE: 17/10/2018         *
*                          *
* PURPOSE: Linked List data*
* structure, with the      *
* appropriate methods      *
* needed for program       *      
***************************/
#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

/*Creates new LinkedList*/
LinkedList* newList()
{
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

/*inserts at tail and pushes current tail up*/
void insertLast(LinkedList* list, LinkedListNode* newNode)
{
    if (list->head == NULL)
    {
        list->head = newNode;
        list->tail = newNode;
    }
    else
    {
        LinkedListNode* temp = list->tail;
        list->tail = newNode;
        temp->next = list->tail;
    }
}

/*removes first element of imported LinkedList*/
void removeFirst(LinkedList* list)
{
    LinkedListNode* temp = list->head;
    if (temp != NULL)
    {
        list->head = temp->next; /*sets head to next element*/
        free(temp->value); /*free old malloc'd node and its malloc'd value*/
        free(temp);
    }
    else
    {
        printf("Error: No head in Linked List.");
    }
}

/*Could have had removeFirst return first element
but need first element before print.c begins
removing elements...*/
LinkedListNode* getFirstElement(LinkedList* list)
{
    LinkedListNode* node;
    if (list->head == NULL)
    {
        node = NULL;
    }
    else
    {
        node = list->head;
    }

    return node;
}
