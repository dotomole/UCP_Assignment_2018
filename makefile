#UCP Assignment Makefile
#Thomas Di Pietro

CC = gcc
CFLAGS = -Werror -Wall -pedantic -ansi
OBJ1 = main.o print.o file_io.o linked_list.o effects.o
OBJ2 = main.o simple_print.o file_io.o linked_list.o effects.o
OBJ3 = main.o debug_print.o debug_file_io.o linked_list.o effects.o
EXEC1 = TurtleGraphics
EXEC2 = TurtleGraphicsSimple
EXEC3 = TurtleGraphicsDebug

default : clean $(EXEC1) $(EXEC2) $(EXEC3)

TurtleGraphics : $(OBJ1)
	$(CC) $(OBJ1) -o $(EXEC1) -lm 

TurtleGraphicsSimple : $(OBJ2)
	$(CC) $(OBJ2) -o $(EXEC2) -lm 

TurtleGraphicsDebug : $(OBJ3)
	$(CC) $(OBJ3) -o $(EXEC3) -lm

main.o : main.c
	$(CC) -c main.c $(CFLAGS)

print.o : print.c print.h 
	$(CC) -c print.c $(CFLAGS)

#Need "-o simple_print.o" to specify custom .o file name for EXEC2
#this applies for other 'custom' .o files.
simple_print.o : print.c print.h 
	$(CC) -o simple_print.o -c print.c $(CFLAGS) -DSIMPLE

debug_print.o : print.c print.h 
	$(CC) -o debug_print.o -c print.c $(CFLAGS) -DDEBUG

file_io.o : file_io.c file_io.h
	$(CC) -c file_io.c $(CFLAGS) 

debug_file_io.o : file_io.c file_io.h
	$(CC) -o debug_file_io.o -c file_io.c $(CFLAGS) -DDEBUG 

linked_list.o : linked_list.c linked_list.h
	$(CC) -c linked_list.c $(CFLAGS)

effects.o : effects.c effects.h
	$(CC) -c effects.c $(CFLAGS)

clean:
	rm -f $(EXEC1) $(EXEC2) $(EXEC3) $(OBJ1) $(OBJ2) $(OBJ3)
