#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main()
{
    void *handle = NULL;
    char *error = NULL;
    int (*fp)(int, int);
    int iRet = 0;
    int A, B, choice;

    handle = dlopen("./arithlib.so", RTLD_LAZY);
    if (handle == NULL)
    {
        error = dlerror();
        printf("Failed to load the library : %s\n", error);
        return -1;
    }

    printf("Library gets loaded succesfully\n");

    printf("Enter two integers: ");
    scanf("%d %d", &A, &B);

    printf("\n Choose arithmetic operation to perform: \n");
    printf("1. Addition\n");
    printf("2. Substraction\n");
    printf("3. Multiplication\n");
    printf("4. Division\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    dlerror();

    switch (choice)
    {
    case 1:
        fp = (int(*)(int,int))dlsym(handle,"Addition");
        break;
    case 2:
        fp = (int(*)(int,int))dlsym(handle,"Substraction");
        break;
    case 3:
        fp = (int(*)(int,int))dlsym(handle,"Multiplication");
        break;
    case 4:
        fp = (int(*)(int,int))dlsym(handle,"Division");
        break;
    
    default:
        printf("Invalid choice\n");
        dlclose(handle);
        break;
    }
    error = dlerror();

    if(error!=NULL)
    {
        printf("Unable to get address of function: %s\n",error);
        dlclose(handle);
        return -1;
    }

    iRet = fp(A,B);
    printf("Result : %d\n",iRet);

    dlclose(handle);
    return 0;
}