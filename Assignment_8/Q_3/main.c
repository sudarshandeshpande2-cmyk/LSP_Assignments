#include <stdio.h>

int Addition(int, int);
int Addition(int x, int y)
{
    return x + y;
}

int main()
{
    int x, y;
    printf("Enter two numbers :");

    scanf("%d", &x);
    scanf("%d", &y);

    printf("Addition of %d and %d is : %d\n", x, y, Addition(x, y));

    return 0;
}