#include <stdio.h>
#include "math.h"

int main()
{
    int A, B;

    printf("Enter two integers: ");
    scanf("%d %d", &A, &B);

    printf("Add = %d\n", Add(A, B));
    printf("Sub = %d\n", Sub(A, B));
    printf("Mul = %d\n", Mul(A, B));
    printf("Div = %d\n", Div(A, B));

    return 0;
}
