/***************************
* FILE: file_io.c          *
* AUTHOR: Thomas Di Pietro *
* DATE: 21/10/2018         *
*                          *
* PURPOSE: Creates linked  *
* list and reads in each   *
* command from file, and   *
* prints to log            *      
***************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"
#include "file_io.h"

LinkedList* readCommands(char* filename)
{
    LinkedList* list = NULL;
    LinkedListNode* newNode = NULL;
    FILE* input = fopen(filename, "r");

    char line[20]; /*buffer of 20*/
    char tempCmd[10]; /*Command buffer*/
    char tempVal[10]; /*Value buffer*/

    if (input == NULL) /*if file doesn't exist*/
    {
        perror("Error opening file");
    }
    else
    {
        list = newList(); /*create LinkedList*/
        while(fgets(line, 20, input) != NULL)
        {
            /*Is calloc instead of malloc as 
            valgrind stated uninitialized value here, 
            and calloc initializes...*/
            newNode = calloc(1, sizeof(LinkedListNode));

            /*only sscanf's if there are 2 'strings'*/
            if (sscanf(line, "%s %s", tempCmd, tempVal) == 2)
            {
                /*converts command str to uppercase
                in case of e.g. "mOvE", "pattern"
                as findCmd strcmp's with uppercase only*/
                convUpCase(tempCmd);

                /*compares first char in array to 
                first char of each command (can do as chars are ints), 
                then stores in struct*/
                if (tempCmd[0] == 'R')
                {    
                    convDouble(tempVal, newNode);
                    newNode->command = tempCmd[0];
                }
                else if(tempCmd[0] == 'M')
                {
                    convDouble(tempVal, newNode);       
                    newNode->command = tempCmd[0]; 
                }
                else if(tempCmd[0] == 'D')
                {    
                    convDouble(tempVal, newNode);       
                    newNode->command = tempCmd[0]; 
                }

                else if(tempCmd[0] == 'F')
                {    
                    convInt(tempVal, newNode);      
                    newNode->command = tempCmd[0];
                }

                else if(tempCmd[0] == 'B')
                {    
                    convInt(tempVal, newNode);      
                    newNode->command = tempCmd[0]; 
                }

                else if(tempCmd[0] == 'P')
                {    
                    convChar(tempVal, newNode);
                    newNode->command = tempCmd[0]; 
                }

                else
                {                    
                    /*Do nothing/skip*/
                }
            }
            else
            {
                /*Do nothing/skip*/
            }   
            /*inserts new node into list*/
            insertLast(list, newNode); 
        }

    }

    if (ferror(input)) /*If file read errors*/
    {
        perror("Error reading from file");
    }
    fclose(input);
    return list;
}

/*From my Prac 4 - if ASCII int value is lowercase,
convert to uppercase*/
void convUpCase(char* str)
{
    int i;
    for (i = 0; i <=strlen(str); i++)
    {
        if (str[i] > 96 && str[i] < 123)
        {
            str[i] = str[i] - 32;
        }
    }
}

/*All these funcs only look at first parameter after command,
thus avoiding any errors if further params are in line 
e.g. MOVE 28 16 - the 16 will be ignored as sscanf is only converting one value*/
void convDouble(char* string, LinkedListNode* node)
{
    /*mallocs the void pointer to size of double, changes value of what it points to from str.*/
    node->value = malloc(sizeof(double));
    sscanf(string, "%lf", (double*) node->value);
}

void convInt(char* string, LinkedListNode* node)
{
    node->value = malloc(sizeof(int));
    sscanf(string, "%d", (int*) node->value);
}

void convChar(char* string, LinkedListNode* node)
{
    node->value = malloc(sizeof(char));
    /*can just get first element of array as 
    pattern from file is just a char*/
    *(char*)node->value = string[0]; 
}

/*LOGFILE FUNCTION*/
void appendLog(FILE* graphicsLog, char* commandStr, double preX, double preY, double x, double y)
{
    /*7.3 = Up to 7 spaces for float, 3 decimal place*/
    fprintf(graphicsLog, "%s (%7.3f,%7.3f)-(%7.3f,%7.3f)\n", commandStr, preX, preY, x, y);
 
    /*DEBUG is for TurtleGraphicsDebug, which prints the 
    logfile to (redirected) stderr)*/
    #ifdef DEBUG
    fprintf(stderr, "%s (%7.3f,%7.3f)-(%7.3f,%7.3f)\n", commandStr, preX, preY, x, y);
    #endif
}