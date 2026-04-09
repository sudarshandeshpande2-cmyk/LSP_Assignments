#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main()
{
    char Buf[100];
    void *handle = NULL;
    char *error = NULL;
    int (*fp_Count_Lower)(char *);
    int (*fp_Count_Upper)(char *);
    int (*fp_Count_Digit)(char *);

    int iRet = 0;

    printf("Enter string to perform operations:\n");
    if ((fgets(Buf, sizeof(Buf), stdin)) == NULL)
    {
        printf("Input error\n");
        return -1;
    }

    handle = dlopen("./libstring.so", RTLD_LAZY);

    if (!handle)
    {
        error = dlerror();
        printf("dlopen failed : %s\n", error);
        return -1;
    }

    fp_Count_Lower = (int (*)(char *))dlsym(handle, "CountLower");
    iRet = fp_Count_Lower(Buf);
    printf("Lowercase count is : %d\n", iRet);

    fp_Count_Upper = (int (*)(char *))dlsym(handle, "CountUpper");
    iRet = fp_Count_Upper(Buf);
    printf("Uppercase count is : %d\n", iRet);

    fp_Count_Digit = (int (*)(char *))dlsym(handle, "CountDigit");
    iRet = fp_Count_Digit(Buf);
    printf("Digit count is : %d\n", iRet);

    dlerror();  // Clearing old errors

    dlclose(handle);

    return 0;
}