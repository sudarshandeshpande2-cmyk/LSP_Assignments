#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main()
{
    void *handle = NULL; // Empty reference
    int (*fp)(int, int);
    int iRet = 0;

    handle = dlopen("./libclient.so", RTLD_LAZY);

    if (handle == NULL)
    {
        char *error = dlerror();
        if (error != NULL)
        {
            printf("dlopen failed : %s\n", error);
        }

        return -1;
    }

    printf("Library gets loaded succesfully\n");

    fp = (int (*)(int, int))dlsym(handle, "Addition");
    if (fp == NULL)
    {
        char *error = dlerror();
        if (error != NULL)
        {
            printf("Unable to get address of function: %s\n", error);
        }
        dlclose(handle);
        return -1;
    }

    iRet = fp(22, 16);

    printf("Addition is : %d\n", iRet);

    fp = (int (*)(int, int))dlsym(handle, "Substraction");

    if (fp == NULL)
    {
        char *error = dlerror();
        if (error != NULL)
        {
            printf("Unable to get address of function: %s\n",error);
        }
        dlclose(handle);
        return -1;
    }

    iRet = fp(22,16);

    printf("Substraction is : %d\n",iRet);

    dlclose(handle);

    return 0;
}