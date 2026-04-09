#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

/*
 * Function : OpenFile
 * -------------------
 * Opens a file and in read only mode,using open() system call
 * On Success file descriptor is printed
 * On Failure,error printed using perror().
 */

void openFile(const char *filename)
{
    int fd; // File Descriptor

    fd = open(filename, O_RDONLY); /*File is opened using open() system call in read only mode*/

    if (fd == -1)
    {
        /*error is printed using perror*/
        perror("Failed to open the file");
        return;
    }
    else
    {
        printf("File opened successfully\n");
        printf("File Descriptor : %d\n ", fd);
    }
}

int main()
{
    char filename[256]; /*character array to store file name entered by user */

    printf("Enter File Name:");
    scanf("%255s", filename); 

    openFile(filename);

    return 0;
}