#include <stdio.h>

int CountLower(char *str);
int CountUpper(char *str);
int CountDigit(char *str);

int CountLower(char *str)
{
    int iCount = 0;

    while (*str != '\0')
    {
        if (*str >= 'a' && *str <= 'z')
        {
            iCount++;
        }
        str++;
    }
    return iCount;
}
int CountUpper(char *str)
{
    int iCount = 0;
    while (*str != '\0')
    {
        if (*str >= 'A' && *str <= 'Z')
        {
            iCount++;
        }
        str++;
    }
    return iCount;
}
int CountDigit(char *str)
{
    int iCount = 0;
    while (*str != '\0')
    {
        if (*str >= '0' && *str <= '9')
        {
            iCount++;
        }
        str++;
    }
    return iCount;
}
