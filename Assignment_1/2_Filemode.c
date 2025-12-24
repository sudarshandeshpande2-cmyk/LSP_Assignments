#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

/*
 *Function : Open_File_Mode
 *-------------------------
 * Modes:
 *    R  -> Read Only
 *    W  -> Write Only (create if not present)
 *    WR -> Read and Write
 *    A  -> Append (create if not present)
 */

void Open_File_Mode(const char *fileName, const char *mode)
{
    int fd = 0, flags = 0;

    if (strcmp(mode, "R") == 0)
    {
        flags = O_RDONLY;
    }
    else if (strcmp(mode, "W") == 0)
    {
        flags = O_WRONLY | O_CREAT;
    }
    else if (strcmp(mode, "WR") == 0)
    {
        flags = O_RDWR;
    }
    else if (strcmp(mode, "A") == 0)
    {
        flags = O_WRONLY | O_APPEND | O_CREAT;
    }
    else
    {
        printf("Invalid Mode\n");
        return;
    }

    fd = open(fileName, flags, 0644); /*0644 is permission only if file is created*/

    if (fd == -1)
    {
        perror("Unable to open file\n");
        return;
    }
    else
    {
        printf("File Opened successfully\n");
        printf("File Descriptor:%d\n", fd);
    }
    close(fd);
}
int main()
{
    char fileName[256];
    char mode[4];

    printf("Enter file name:");
    scanf("%255s", fileName);

    printf("Enter mode (R / W / WR / A):");
    scanf("%3s", mode);

    Open_File_Mode(fileName, mode);
}
