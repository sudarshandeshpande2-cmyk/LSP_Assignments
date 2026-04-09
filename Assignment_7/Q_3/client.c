#include <stdio.h>
#include "display.h"

int main()
{
    char str[100];

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    Display(str);

    return 0;
}
