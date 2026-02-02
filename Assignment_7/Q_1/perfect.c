#include <stdio.h>
#include "perfect.h"

int IsPerfect(int)
{
    int No = 0;
    int ret = 0;

    printf("Enter number: ");
    scanf("%d", &No);

    ret = IsPerfect(No);

    if (ret == 1)
    {
        printf("%d is a Perfect Number\n", No);
    }
    else
    {
        printf("%d is not a Perfect Number\n", No);
    }

    return 0;
}
