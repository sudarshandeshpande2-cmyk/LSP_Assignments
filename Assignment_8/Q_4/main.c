#include <stdio.h>
#include "helper.h"

int main()
{
    int A, B, result;

    printf("Enter two integers: ");
    scanf("%d %d", &A, &B);

    result = Add(A, B);
    
    printf("Addition = %d\n", result);

    return 0;
}
