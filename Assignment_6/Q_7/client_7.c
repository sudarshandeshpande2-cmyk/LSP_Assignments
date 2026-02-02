#include <stdio.h>
#include <dlfcn.h>

int main()
{
    void *handle;
    char *error;

    void (*increment)(int);
    void (*display)();
    void (*reset)();

    handle = dlopen("./global_lib_7.so", RTLD_LAZY);
    if (!handle)
    {
        printf("dlopen error: %s\n", dlerror());
        return -1;
    }

    increment = (void (*)(int))dlsym(handle, "Increment");
    display   = (void (*)())dlsym(handle, "Display");
    reset     = (void (*)())dlsym(handle, "Reset");

    if ((error = dlerror()) != NULL)
    {
        printf("dlsym error: %s\n", error);
        dlclose(handle);
        return -1;
    }

    printf("Initial value:\n");
    display();

    increment(10);
    display();

    increment(20);
    display();

    reset();
    display();

    dlclose(handle);
    return 0;
}
