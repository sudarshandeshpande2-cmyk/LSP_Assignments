#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main()
{
    void *handle = NULL;
    int iRet = 0;
    int (*fp[])(int, int) = {NULL, NULL, NULL};

    handle = dlopen("./sharedlib_9.so", RTLD_LAZY);
                                        
    if (!handle)
    {
        printf("dlopen failed : %s\n", dlerror());
        return -1;
    }
    fp[0] = (int (*)(int, int))dlsym(handle, "Sum");
    iRet = fp[0](11, 10);
    printf("Sum is %d\n", iRet);
    printf("Address of sum is : %p\n", (void*)fp[0]);

    fp[1] = (int (*)(int, int))dlsym(handle, "Dif");
    iRet = fp[1](11, 10);
    printf("Difference is %d\n", iRet);
    printf("Address of difference is : %p\n", (void*)fp[1]);

    dlerror(); // Clearing old errors

    dlclose(handle);

    return 0;
}