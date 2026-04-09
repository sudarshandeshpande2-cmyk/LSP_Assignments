#include <stddef.h>
#include "mystring.h"

int MyStrlen(const char *str)
{
    int count = 0;

    if (str == NULL)
    {
        return 0;
    }

    while (str[count] != '\0')
    {
        count++;
    }

    return count;
}
