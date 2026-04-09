#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main()
{
    void *handle = NULL;
    char *error = NULL;
    int (*fp)(int, int);
    int iRet = 0;

    handle = dlopen("./sharedlib.so", RTLD_LAZY);

    if (handle == NULL)
    {
        error = dlerror();
        printf("%s\n", error);
        return -1;
    }

    printf("Library loaded succesfully\n");

    dlerror(); // Clearing old errors

    fp = (int (*)(int, int))dlsym(handle, "Addition");

    error = dlerror();

    if (error != NULL)
    {
        printf("%s\n", error);
        dlclose(handle);
        return -1;
    }

    iRet = fp(22, 16);

    printf("Addition is : %d\n", iRet);

    dlerror(); // Clearing old errors

    fp = (int (*)(int, int))dlsym(handle, "Substraction");

    error = dlerror();

    if (error != NULL)
    {
        printf("%s\n", error);
        dlclose(handle);
        return -1;
    }

    iRet = fp(22, 16);

    printf("Substraction is : %d\n", iRet);

    dlerror(); // Clearing old errors

    fp = (int (*)(int, int))dlsym(handle, "Multiplication");

    error = dlerror();

    if (error != NULL)
    {
        printf("%s\n", error);
        dlclose(handle);
        return -1;
    }

    iRet = fp(10, 10);

    printf("Multiplication is : %d\n", iRet);

    dlerror(); // Clearing old errors

    dlclose(handle);
    
    return 0;
    
}