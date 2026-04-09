#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

/*
 * Function Name: print_file_in_reverse
 * ------------------------------------
 * Reads and prints file content in reverse order
 *
 * fd = file descriptor of input file
 */

void print_in_reverse_order(int);

void print_in_reverse_order(int fd)
{
    off_t fileSize;
    char singleChar;
    ssize_t bytesRead;

    /*
     * lseek() system call
     * Move file offset to the end of file to get file size
     */
    fileSize = lseek(fd, 0, SEEK_END);
    if (fileSize == -1)
    {
        perror("Error:unable to get file size");
        exit(1);
    }
    /*
     * Read file byte-by-byte from end to beginning
     */
    while (fileSize > 0)
    {
        /*
         * Move file offset to previous byte
         */
        fileSize = lseek(fd, -1, SEEK_CUR);
        if (fileSize == -1)
        {
            perror("Failed to move file offset");
            exit(1);
        }
        bytesRead = read(fd, &singleChar, 1);
        if (bytesRead != 1)
        {
            perror("Failed to read file");
            exit(1);
        }
        write(STDOUT_FILENO, &singleChar, 1);

        lseek(fd, -1, SEEK_CUR);
    }
}

int main(int argc, char *argv[])
{
    int fd;

    /*Validate command line arguments*/
    if (argc != 2)
    {
        printf("Usage: %s <file_name>\n", argv[0]);
        return 1;
    }
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        perror("Error: Failed to open file");
        return 1;
    }

    print_in_reverse_order(fd);

    close(fd);

    return 0;
}