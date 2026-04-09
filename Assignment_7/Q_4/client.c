#include <stdio.h>
#include "mystring.h"

int main()
{
    char str[100];
    int len = 0;

    printf("Enter a string : ");
    fgets(str,sizeof(str),stdin);

    len = MyStrlen(str);

    printf("Length of string is : %d\n",len);
    
    return 0;
}
