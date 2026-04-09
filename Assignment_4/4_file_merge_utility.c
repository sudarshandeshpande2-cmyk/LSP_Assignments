#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#define BUFFER_SIZE 4096

/*
 * Function Name: append_file_to_output
 * ------------------------------------
 * Reads contents of an input file and appends them
 * to the already opened output file
 *
 * inputFd : file descriptor of input file
 * outputFd : file descriptor of output file
 */

void append_file_to_output(int, int);

void append_file_to_output(int inputFd, int outputFd)
{
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead, bytesWritten;

    /*
     * read() system call
     * reads data from input file
     */
    while ((bytesRead = read(inputFd, buffer, BUFFER_SIZE)) > 0)
    {
        /*
         * write system call
         * writes read data into output file
         */
        bytesWritten = write(outputFd, buffer, bytesRead);
        if (bytesWritten != bytesRead)
        {
            perror("Failed to write data to output file");
            exit(1);
        }
    }
    if (bytesRead < 0)
    {
        perror("Failed to read the input file");
        exit(1);
    }
}

int main(int argc, char *argv[])
{
    int outputFd, inputFd;
    int fileIndex;

    /*Minimum arguments check*/

    if (argc < 3)
    {
        printf("Usage : %s <output_file> <input_file> <file1> <file2> ...\n", argv[0]);
        return 1;
    }

    outputFd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (outputFd == -1)
    {
        perror("Error: Failed to open output file");
        return 1;
    }
    /*
     * Loop through all input files
     * starting from argv[2]
     */
    for (fileIndex = 2; fileIndex < argc; fileIndex++)
    {
        /*
         * open in readonly mode
         */
        inputFd = open(argv[fileIndex], O_RDONLY);
        if (inputFd == -1)
        {
            perror("Error: Failed to open input file");
            close(outputFd);
            return 1;
        }
        /*Append current file content to output file*/
        append_file_to_output(inputFd,outputFd);

        close(inputFd);
    }
    close(outputFd);

    printf("Files merged successfully.\n");
    return 0;
}