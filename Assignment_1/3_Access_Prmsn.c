#include <stdio.h>
#include <unistd.h>
#include <string.h> 

int main()
{
    char filename[256];
    char mode[10];
    int Access_Mode;

    printf("Enter file name: ");
    scanf("%255s", filename);

    printf("Enter mode of access (read/write/execute):");
    scanf("%9s", mode);

    if (strcmp(mode, "read") == 0)
    {
        Access_Mode = R_OK;
    }
    else if (strcmp(mode, "write") == 0)
    {
        Access_Mode = W_OK;
    }
    else if (strcmp(mode, "execute") == 0)
    {
        Access_Mode = X_OK;
    }
    else
    {
        printf("Invalid mode of access\n");
        return 1;
    }

    /*Access checks permissions
    returns 0 if success -1 if failure
    */
    if (access(filename, Access_Mode) == 0)
    {
        printf("Accessible\n");
    }
    else
    {
        printf("Not Accessible\n");
        perror("");
    }
    return 0;
}
