#include <stdio.h>
#include "mystring.h"
#include "mymath.h"

int main()
{
    int choice;
    char str1[100], str2[100], ch;
    int a, b, n;

    do
    {
        printf("\n===== MENU =====");
        printf("\n1. MyStrlen");
        printf("\n2. MyStrcpy");
        printf("\n3. MyStrcat");
        printf("\n4. MyStrcmp");
        printf("\n5. MyStrrev");
        printf("\n6. MyPow");
        printf("\n7. MyFactorial");
        printf("\n8. MyGCD & MyLCM");
        printf("\n0. Exit");
        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter string: ");
            scanf("%s", str1);
            printf("Length = %d\n", MyStrlen(str1));
            break;

        case 2:
            printf("Enter source: ");
            scanf("%s", str1);
            MyStrcpy(str2, str1);
            printf("Copied string: %s\n", str2);
            break;

        case 3:
            printf("Enter string1: ");
            scanf("%s", str1);
            printf("Enter string2: ");
            scanf("%s", str2);
            MyStrcat(str1, str2);
            printf("Concatenated: %s\n", str1);
            break;

        case 4:
            printf("Enter string1: ");
            scanf("%s", str1);
            printf("Enter string2: ");
            scanf("%s", str2);
            printf("Result = %d\n", MyStrcmp(str1, str2));
            break;

        case 5:
            printf("Enter string: ");
            scanf("%s", str1);
            MyStrrev(str1);
            printf("Reversed: %s\n", str1);
            break;

        case 6:
            printf("Enter base & exponent: ");
            scanf("%d%d", &a, &b);
            printf("Power = %d\n", MyPow(a, b));
            break;

        case 7:
            printf("Enter number: ");
            scanf("%d", &n);
            printf("Factorial = %d\n", MyFactorial(n));
            break;

        case 8:
            printf("Enter two numbers: ");
            scanf("%d%d", &a, &b);
            printf("GCD = %d, LCM = %d\n", MyGCD(a, b), MyLCM(a, b));
            break;
        }
    } while (choice != 0);

    return 0;
}
