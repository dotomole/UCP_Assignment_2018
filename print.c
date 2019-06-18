/***************************
* FILE: print.c            *
* AUTHOR: Thomas Di Pietro *
* DATE: 21/10/2018         *
*                          *
* PURPOSE: Loops through   *
* Linked List and stores   *
* appropriate current val  *
* in CurrentInfo struct    *
*                          *
* Uses effects.c's line()  *
* to print patterns to     *
* terminal based on current*
* location (x,y) and angle *      
***************************/

#define DEFAULTX 0.0
#define DEFAULTY 0.0
#define DEFAULTANGLE 0.0
#define DEFAULTPATTERN 43 /*Ascii '+' = 43*/
#define DEFAULTFG 7
#define DEFAULTBG 0
#define PI 3.1415926535

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "linked_list.h"
#include "effects.h"
#include "print.h"
#include "file_io.h"

void print(LinkedList* list)
{
    LinkedListNode* node;
    FILE* graphicsLog;
    CurrentInfo* current;
    double angleChange, length;

    current = malloc(sizeof(CurrentInfo));

    current->x = DEFAULTX;
    current->y = DEFAULTY;
    current->angle = DEFAULTANGLE;
    current->pattern = DEFAULTPATTERN;

    setFgColour(DEFAULTFG);
    setBgColour(DEFAULTBG);
    clearScreen();

    node = getFirstElement(list);

    /*For debug compile, open new terminal and 
    redirect stderr to new terminal*/
    #ifdef DEBUG
    stderr = freopen("/dev/pts/1", "w", stderr);
    #endif

    graphicsLog = fopen("graphics.log", "a"); /*"a" for append*/
    fprintf(graphicsLog, "%s", "---\n"); /*prints the divider between each run*/

    /*Loop through list till null*/
    while (node != NULL)
    {
        switch(node->command)
        {
            case 'R':
                angleChange = *(double*)node->value;
                setAngle(angleChange, current);
                break;
            case 'M':
                length = (*(double*)node->value);
                move(length, current, graphicsLog, 'Y');
                break;              
            case 'D':
                /*Decrease distance by 1 (part of blackboard fix)*/
                length = (*(double*)node->value);
                draw(length-1, current, graphicsLog);
                break;              
            case 'F':
                #ifndef SIMPLE
                setFgColour(*(int*)node->value);
                #endif   
                break;              
            case 'B':
                #ifndef SIMPLE
                setBgColour(*(int*)node->value);
                #endif     
                break;              
            case 'P':
                current->pattern = *((char*)node->value);     
                break;              
            default:
                /* Do nothing/skip */
                break;              
        }
        /*remove element from list when done, which sets next as new head
        for then to use getFirstElement again.*/
        removeFirst(list); /*removes and also frees node and node->value mallocs*/
        node = getFirstElement(list);
    }

    if (ferror(graphicsLog)) /*If any errors occurred*/
    {
        perror("Error reading from file");
    }
    fclose(graphicsLog);
    free(current);
    free(list);

    /*clean up terminal*/
    setFgColour(DEFAULTFG);
    setBgColour(DEFAULTBG);
    penDown();   
}

/*'moves' cursor by updating current coordinates (x,y)*/
void move(double length, CurrentInfo* current, FILE* graphicsLog, char choice)
{
    double preX, preY, radian;

    preX = current->x;
    preY = current->y; /*before change (x1, y1)*/

    radian = current->angle * (PI / 180);
 
    current->x += length * (cos(radian)); 
    current->y -= length * (sin(radian));/*found it was going negative so reversed "-=" to make positive*/
    /*"must round coordinates to nearest integer"*/ 
    roundNum(&current->x);
    roundNum(&current->y);

    if (choice == 'Y')
    {
        appendLog(graphicsLog, "MOVE", preX, preY, current->x, current->y);
    }    
}

/*gets temp last pos, then updates, then uses both to draw with line() from effects.c*/
void draw(double length, CurrentInfo* current, FILE* graphicsLog)
{
    PlotFunc plotter = NULL;
    double preX, preY, radian;

    preX = current->x;
    preY = current->y; /*before change (x1, y1)*/

    radian = current->angle * (PI / 180);

    current->x += length * (cos(radian)); 
    current->y -= length * (sin(radian));/*found it was going negative so took away to make positive*/
 
    /*"must round coordinates to nearest integer"*/
    roundNum(&current->x);
    roundNum(&current->y);

    plotter = &printPattern; /*point func ptr to printPattern, for use in effects.c*/
    line((int)preX, (int)preY, (int)current->x, (int)current->y, plotter, (void*) &(current->pattern));
    
    /*Move cursor by 1 (part of blackboard fix)*/
    move(1, current, graphicsLog, 'N');

    appendLog(graphicsLog, "DRAW", preX, preY, current->x, current->y);
}

void roundNum(double* num)
{
    int numTrunc, finNum;
    double diff;

    numTrunc = (int)*num;
    diff = *num - (double)numTrunc;

    if (diff >= 0.5)
    {
        finNum = numTrunc + 1;
    }
    else
    {
        finNum = numTrunc;
    }

    *num = (double) finNum;
}

/*Keeps angle between valid values of 0 and 360*/
void setAngle(double angleChange, CurrentInfo* current)
{
    current->angle += angleChange;

    if (current->angle > 360.0)
    {
        current->angle -= 360.0;
    }
    else if (current->angle < 0.0)
    {
        current->angle += 360.0;
    }
}

void printPattern(void* inValue)
{
    printf("%c", *((char*)inValue));
}

