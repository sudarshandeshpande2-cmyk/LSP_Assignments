#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096

/*
 * Function Name: copy_file
 * ------------------------
 * Copy data from source to destination file descriptor
 *
 * src_Fd : File descriptor of source file
 * dest_Fd: File descriptor of destination file
 */

void copy_file(int, int);

void copy_file(int src_Fd, int dest_Fd)
{
    char buffer[BUFFER_SIZE];
    ssize_t bytes_Read, bytes_Written;

    /*
     * read() system call
     * Reads data from source file into buffer
     */
    while ((bytes_Read = read(src_Fd, buffer, BUFFER_SIZE)) > 0)
    {

        /*
         * write() system call
         * writes data from buffer into destination file
         */
        bytes_Written = write(dest_Fd, buffer, bytes_Read);
        if (bytes_Written != bytes_Read)
        {
            perror("Failed to write data to destination file");
            exit(1);
        }
    }
    if(bytes_Read < 0){
        perror("Failed to read source file");
        exit(1);
    }
} 

int main(int argc , char* argv[])
{
    int source_Fd ,dest_Fd;
    /*Check command line arguments*/
    if(argc!=3){
        printf("Usage: %s <source_file> <destination_file>\n",argv[0]);
        return 1;
    }
    /*
     * open() system call for destiantion file
     * 0644  -> File permissions (rw-r--r--)
     */
    dest_Fd = open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,0644);
    if (dest_Fd == -1)
    {
        perror("Failed to open destination file");
        close(source_Fd);
        return 1;
    }
    /*Copy contents*/
    copy_file(source_Fd,dest_Fd);
    close(source_Fd);
    close(dest_Fd);

    printf("File copied successfully.\n");
    return 0;
}