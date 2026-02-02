/*
Difference between RTLD_LAZY and RTLD_NOW flags used with dlopen()
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                                       //
//    • RTLD_LAZY and RTLD_NOW are flags used with dlopen() to control how symbols from a shared library are resolved.   //
//                                                                                                                       //
//    • When RTLD_LAZY is used, symbol resolution is deferred until the symbol is actually referenced. This means the    //
//    shared library is loaded successfully even if some symbols are missing, and errors related to unresolved           //
//    symbols occur only when dlsym() is called or when the function is executed.                                        //
//                                                                                                                       //
//    • When RTLD_NOW is used, all symbols are resolved immediately at the time of loading the shared library. If any    //
//    symbol cannot be resolved, dlopen() fails and returns NULL. This helps in detecting errors early.                  //
//                                                                                                                       //
//    • In short, RTLD_LAZY delays symbol resolution and improves load time, whereas RTLD_NOW resolves all symbols       //
//    immediately and provides early error detection.                                                                    //
//                                                                                                                       //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main()
{
    void *handle = NULL;
    int (*fp)(int);
    char *error = NULL;
    int iRet = 0;
    int No = 0;

    /////////////////////////////////////////////////////////////////////
    //                                                                 //
    //                          RTLD_LAZY case                         //
    //                                                                 //
    /////////////////////////////////////////////////////////////////////

    handle = dlopen("./sharedlib.so", RTLD_LAZY);

    if (handle == NULL)
    {
        error = dlerror();
        printf("Failed to load library : %s\n", error);
        return -1;
    }

    printf("Library loaded succesfully\n");

    dlerror(); // Clearing old error

    fp = (int (*)(int))dlsym(handle, "IsEven");
    error = dlerror();

    if (error != NULL)
    {
        printf("Unable to get address of function: %s\n", error);
        dlclose(handle);
        return -1;
    }

    printf("Enter number to check:\n");
    scanf("%d", &No);

    iRet = fp(No);

    if (iRet == 1)
    {
        printf("The number %d is even\n", No);
    }
    else
    {
        printf("The number %d is odd\n",No);
    }

    dlerror(); // Clearing old erro

    fp = (int (*)(int))dlsym(handle, "IsPrime");
    error = dlerror();

    if (error != NULL)
    {
        printf("Unable to get address of function: %s\n", error);
        dlclose(handle);
        return -1;
    }

    printf("Enter number to check:\n");
    scanf("%d", &No);

    iRet = fp(No);

    if (iRet == 1)
    {
        printf("The entered number is even\n");
    }
    else
    {
        printf("The entered number is odd\n");
    }

    dlerror(); // Clearing old error

    dlclose(handle);

    dlerror();

    /////////////////////////////////////////////////////////////////////
    //                                                                 //
    //                          RTLD_NOW case                          //
    //                                                                 //
    /////////////////////////////////////////////////////////////////////

    handle = dlopen("./sharedlib.so", RTLD_NOW);

    if (handle == NULL)
    {
        error = dlerror();
        printf("Failed to load the library : %s\n", error);
        return -1;
    }

    printf("Library loaded succesfully\n");

    dlerror();

    fp = (int (*)(int))dlsym(handle, "IsEven");
    error = dlerror();

    if (error != NULL)
    {
        printf("Unable to get address of function: %s\n", error);
        dlclose(handle);
        return -1;
    }

    printf("Enter number to check:\n");
    scanf("%d", &No);
    iRet = fp(No);

    if (iRet == 1)
    {
        printf("The number %d is Even", No);
    }
    else
    {
        printf("The number %d is Odd", No);
    }

    dlerror();

    dlclose(handle);

    dlerror();
    
    return 0;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                                         //
//  In this experiment, both RTLD_LAZY and RTLD_NOW successfully load the shared library because the unresolved symbol     //
// is not required by the library at load time. The error is detected when dlsym() is used to access the missing symbol.   //
// This demonstrates that RTLD_NOW resolves only the symbols needed by the shared library itself, while symbols requested  //
// dynamically using dlsym() are checked at runtime.                                                                       //                                             
//                                                                                                                         //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


