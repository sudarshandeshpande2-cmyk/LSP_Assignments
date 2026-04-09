#include <stdio.h>

int Addition(int, int);
int Addition(int A, int B)
{
    return A + B;
}

int main()
{
    int A, B;
    printf("Enter two numbers:");
    scanf("%d", &A);
    scanf("%d", &B);

    printf("The sum of %d and %d is: %d\n", A, B, Addition(A, B));

    return 0;
}