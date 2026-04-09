// 

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main()
{
    void *handle = NULL;
    int (*fp1)(int, int);
    int (*fp2)(int);
    char *error = NULL;
    int iRet = 0;

    handle = dlopen("sharedlib.so", RTLD_LAZY);

    if (handle == NULL)
    {
        error = dlerror();
        printf("Failed to load library: %s\n", error);
        return -1;
    }

    printf("Library loaded succesfully\n");

    fp1 = (int (*)(int, int))dlsym(handle,"Addition");
    
    error = dlerror();

    if(error!=NULL)
    {
        printf("Unable to get address of function: %s\n",error);
        dlclose(handle);
        return -1;
    }

    iRet = fp1(10,10);
    
    printf("The Addition is : %d\n",iRet);

    dlerror();

    fp2 = (int (*)(int))dlsym(handle,"Square");
    
    error = dlerror();

    if(error!=NULL)
    {
        printf("Unable to get address of function: %s\n",error);
        dlclose(handle);
        return -1;
    }

    iRet = fp2(22);
    
    printf("The square is : %d\n",iRet);

    dlclose(handle);

    return 0;

}



////////////////////////////////////////////////////////////////////////////
//                                                                        //          
//                                                                        //  
//                                                                        //
//                                                                        //          
////////////////////////////////////////////////////////////////////////////