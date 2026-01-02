#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096

/*
 * Function Name: copy_from_offset
 * -------------------------------
 * Copies file contents from a given offset of source file
 * into destination file
 *
 * sourceFd: file descriptor of source file
 * destinationFd: file descriptor of destination file
 * offset: byte offset from where copy starts
 */

void copy_from_offset(int, int, off_t);

void copy_from_offset(int sourceFd, int destinationFd, off_t offset)
{
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead, bytesWritten;
    /*
     * lseek() system call
     * Reads data from source file starting at offset
     */
    while ((bytesRead = read(sourceFd, buffer, BUFFER_SIZE)) > 0)
    {
        /*
         * write() system call
         * write data into destination file
         */
        bytesWritten = write(destinationFd, buffer, bytesRead);
        if (bytesWritten != bytesRead)
        {
            perror("Failed to write data to destination file");
            exit(1);
        }
    }
    if (bytesRead < 0)
    {
        perror("Error reading source file");
        exit(1);
    }
}

int main(int argc, char *argv[]){
    int sourceFd, destinationFd;
    off_t offset ;
    /*Validate commadn line arguments*/
    if(argc!=4){
        printf("Usage: %s <source_file> <destination_file> <offset>\n",argv[0]);
        return 1;
    }
    /*Convert offset argument to integer */
    offset = (off_t)atoi(argv[3]);

    sourceFd = open(argv[1],O_RDONLY);
    if(sourceFd == -1){
        perror("Error opening source file");
        return 1;
    }

    destinationFd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC,0644);
    if(destinationFd == -1){
        perror("Error opening destination file");
        close(sourceFd);
        return 1;
    }
    /*Copy file contents from given offset*/
    copy_from_offset(sourceFd,destinationFd,offset);

    close(sourceFd);
    close(destinationFd);

    printf("File copied successfully from offset %ld bytes.\n",offset);
    return 0;
}