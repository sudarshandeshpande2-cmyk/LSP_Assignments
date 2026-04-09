#include "helper.h"

int SumOfFactors(int No)
{
    int i = 0;
    int sum = 0;

    for (i = 1; i <= No / 2; i++)
    {
        if (No % i == 0)
        {
            sum = sum + i;
        }
    }

    return sum;
}
