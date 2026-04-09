#include "mymath.h"

int MyAbs(int x)
{
    return (x < 0) ? -x : x;
}

int MyMax(int a, int b)
{
    return (a > b) ? a : b;
}

int MyMin(int a, int b)
{
    return (a < b) ? a : b;
}

int MyPow(int base, int exp)
{
    int res = 1;
    while (exp--)
        res *= base;
    return res;
}

int MyFactorial(int n)
{
    int fact = 1;
    while (n > 0)
        fact *= n--;
    return fact;
}

int MyGCD(int a, int b)
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int MyLCM(int a, int b)
{
    return (a * b) / MyGCD(a, b);
}

double MySqrt(double n)
{
    double x = n, y = 1;
    double e = 0.00001;

    while (x - y > e)
    {
        x = (x + y) / 2;
        y = n / x;
    }
    return x;
}
