#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096

/*
 * Function Name: copy_using_pread_pwrite
 * --------------------------------------
 * copies contents of source file to destination file
 * using pread() and pwrite() without changing file offsets.
 *
 * sourceFd: file descriptor of source file
 * destinationFd: file descriptor of destination file
 */

void copy_using_pread_pwrite(int, int);

void copy_using_pread_pwrite(int sourceFd, int destinationFd)
{

    char buffer[BUFFER_SIZE];
    ssize_t bytesRead, bytesWritten;
    off_t currOffset = 0;

    /*
     * pread() system call
     * Writes data to destination file at a specific offset
     * without modifying the file pointer
     */
    while ((bytesRead = pread(sourceFd, buffer, BUFFER_SIZE, currOffset)) > 0)
    {
        /*
         * pwrite() system call
         * writes data to destination at a specific offset
         * without modifying the file pointer
         */
        bytesWritten = pwrite(destinationFd, buffer, bytesRead, currOffset);
        if (bytesWritten != bytesRead)
        {
            perror("Error: Failed to write data using pwrite");
            exit(1);
        }
        /*Move offset manually*/
        currOffset = currOffset + bytesRead;
    }
    if (bytesRead < 0)
    {
        perror("Error:Failed to read using pread");
        exit(1);
    }
}

int main(int argc, char *argv[])
{
    int sourceFd, destinationFd;

    /*Validate command line arguments*/
    if (argc != 3)
    {
        printf("Usage: %s <source_file> <destination_file>\n", argv[0]);
        return -1;
    }

    sourceFd = open(argv[1], O_RDONLY);
    if (sourceFd == -1)
    {
        perror("Failed to open source file");
        return -1;
    }

    destinationFd = open(argv[2], O_RDONLY | O_CREAT | O_TRUNC, 0644);
    if (destinationFd == -1)
    {
        perror("Failed to open destination file");
        close(sourceFd);
        return -1;
    }

    /*copy file contents pread() pwrite() */
    copy_using_pread_pwrite(sourceFd, destinationFd);

    close(sourceFd);
    close(destinationFd);

    printf("File copied successfully using pread() and pwrite .\n");
    return 0; 
}
