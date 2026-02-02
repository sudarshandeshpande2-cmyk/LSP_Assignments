#include <stdio.h>
#include "display.h"

void Display(char * str)
{
    int iCount = 0;

    printf("String: %s\n",str);

    while(str[iCount] != '\0')
    {
        iCount++;
    }

    printf("Total characters: %d\n",iCount);
    
}
