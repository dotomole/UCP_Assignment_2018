/***************************
* FILE: print.h            *
* AUTHOR: Thomas Di Pietro *
* DATE: 21/10/2018         *  
***************************/
typedef struct
{
	double x;
    double y;
    double angle;
    char pattern;
} CurrentInfo;

void print(LinkedList* list);
void move(double length, CurrentInfo* current, FILE* graphicsLog, char choice);
void draw(double length, CurrentInfo* current, FILE* graphicsLog);
void roundNum(double* num);
void setAngle(double angleChange, CurrentInfo* current);
void printPattern(void* inValue);
