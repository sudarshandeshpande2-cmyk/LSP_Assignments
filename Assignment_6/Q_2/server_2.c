#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main()
{
    void *handle = NULL;
    int (*fp)(int, int);
    char *error;
    int iRet = 0;

    handle = dlopen("./libclient.so", RTLD_LAZY);
    if (handle == NULL)
    {
        error = dlerror();
        printf("Failed to load library : %s\n", error);
        return -1;
    }

    printf("Library loaded succesfully\n");

    dlerror();

    fp = (int (*)(int, int))dlsym(handle, "Multiplication");
    error = dlerror();
    if (error != NULL)
    {
        printf("Unable to get address of function : %s\n", error);
        dlclose(handle);
        return -1;
    }

    iRet = fp(10, 11);

    printf("Product is : %d\n", iRet);

    dlerror();

    fp = (int (*)(int, int))dlsym(handle, "Division");
    error = dlerror();
    if (error != NULL)
    {
        printf("Unable to get address of function : %s\n", error);
        dlclose(handle);
        return -1;
    }

    iRet = fp(15, 5);

    printf("Division is : %d\n", iRet);

    dlclose(handle);
    
    return 0;
}

/*
Explanation of Functions Used
dlopen()

    • Loads a shared library into memory at runtime.
    
    • Returns a handle to the loaded library.
    
    • Used to perform runtime dynamic linking.
    
dlsym()

    • Fetches the address of a function or symbol from the loaded library.
    
    • Returns a void * which is cast to a function pointer.
    
    • Enables calling functions whose addresses are known only at runtime.
    
dlerror()

    • Returns a human-readable error message for the last dynamic linking error.
    
    • Used to detect failures in dlopen() and dlsym().
    
    • Returns NULL if no error occurred.
    
dlclose()

    • Unloads the shared library from memory.
    
    • Releases resources associated with the library.
    
Ensures proper cleanup
*/