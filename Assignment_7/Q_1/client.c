#include <stdio.h>
#include "perfect.h"

int main()
{
    int No = 0;
    int iRet = 0;

    printf("Enter number:");
    scanf("%d", &No);

   iRet = IsPerfect(No);

    if (iRet == 1)
    {
        printf("%d is a perfect number\n",No);
    }
    else
    {
        printf("%d is not a perfect number\n",No);
    }

    return 0;
}