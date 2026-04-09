#include "math.h"

int Add(int A, int B)
{
    return A + B;
}

int Sub(int A, int B)
{
    return A - B;
}

int Mul(int A, int B)
{
    return A * B;
}

int Div(int A, int B)
{
    if (B == 0)
        return 0;
    return A / B;
}
    