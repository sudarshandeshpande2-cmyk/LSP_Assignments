#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

/* Reads N bytes from a file and prints them on console */
int readNBytesFromFile(const char *fileName, int numberOfBytes)
{
    int fd;
    int bytesRead;
    char buffer[1024];

    fd = open(fileName, O_RDONLY);
    if (fd == -1)
    {
        perror("open failed");
        return -1;
    }

    /*
     * read() reads up to numberOfBytes.
     * It may return fewer bytes if file is smaller.
     */
    bytesRead = read(fd, buffer, numberOfBytes);
    if (bytesRead == -1)
    {
        perror("read failed");
        close(fd);
        return -1;
    }

    /* Write exactly the bytes that were read */
    read(STDOUT_FILENO, buffer, bytesRead);

    close(fd);
    return 0;
}

int main()
{
    char fileName[256];
    int numberOfBytes;

    printf("Enter file name: ");
    scanf("%255s", fileName);

    printf("Enter number of bytes to read: ");
    scanf("%d", &numberOfBytes);

    readNBytesFromFile(fileName, numberOfBytes);

    return 0;
}
