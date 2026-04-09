#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main(int argc, char *argv[])
{
    void *handle = NULL;
    void *symbol_addr = NULL;
    char *error = NULL;

    // User should give atleast one Command-line argument
    if (argc != 3)
    {
        printf("Usage : %s <library_path> <symbol_name>\n", argv[0]);
        return -1;
    }

    // Accepting arguments from command line
    handle = dlopen(argv[1], RTLD_LAZY);

    if (!handle)
    {
        printf("Failed to load the library : %s\n", (error = dlerror()));
        return -1;
    }

    symbol_addr = dlsym(handle, argv[2]);

    error = dlerror();

    if (error != NULL)
    {
        printf("Unable to get address of function : %s\n", error);
    }
    else
    {
        printf("Symbol '%s' found at address :%p\n", argv[2], symbol_addr);
    }

    dlclose(handle);

    return 0;
}