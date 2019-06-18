/***************************
* FILE: main.c            *
* AUTHOR: Thomas Di Pietro *
* DATE: 21/10/2018         *     
***************************/
#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"
#include "file_io.h"
#include "print.h"

int main(int argc, char* argv[])
{
	/*Must be 2 arguments, program and filename*/
	if (argc != 2)
	{
		printf("Error: command-line parameters wrong.\n");
		printf("	   e.g. ./TurtleGraphics filename\n");
	}
	else
	{
		LinkedList* list;
		list = readCommands(argv[1]);

		print(list);
	}
	return 0;	
}