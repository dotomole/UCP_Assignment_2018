/***************************
* FILE: file_io.h          *
* AUTHOR: Thomas Di Pietro *
* DATE: 21/10/2018         *     
***************************/
LinkedList* readCommands(char* filename);
void convUpCase(char* str);
void convDouble(char* string, LinkedListNode* node);
void convInt(char* string, LinkedListNode* node);
void convChar(char* string, LinkedListNode* node);
void appendLog(FILE* graphicsLog, char* command, double preX, double preY, double x, double y);