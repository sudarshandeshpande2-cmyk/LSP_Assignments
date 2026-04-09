#include <stdio.h>

int iCount = 0;
void Increment(int);
void Display();
void Reset();

void Increment(int No)
{
    iCount+=No;
}

void Display()
{   
    printf("Current value of global variable is : %d\n",iCount);
}

void Reset()
{
    iCount = 0;
}

