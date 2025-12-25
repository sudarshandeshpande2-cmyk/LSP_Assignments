#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define BUF 1024

int readNBytes(const char *fileName, int n)
{
    int fd;
    ssize_t bytesRead;
    int totalRead = 0;
    char buffer[BUF];

    fd = open(fileName, O_RDONLY);
    if (fd == -1)
    {
        perror("open failed");
        return -1;
    }

    while (totalRead < n)
    {
        int toRead = n - totalRead;
        if (toRead > BUF)
            toRead = BUF;

        bytesRead = read(fd, buffer, toRead);
        if (bytesRead == -1)
        {
            perror("read failed");
            close(fd);
            return -1;
        }

        if (bytesRead == 0)
            break;   /* EOF */

        write(STDOUT_FILENO, buffer, bytesRead);
        totalRead += bytesRead;
    }

    close(fd);
    return 0;
}

int main()
{
    char fileName[256];
    int n;

    printf("Enter file name: ");
    scanf("%255s", fileName);

    printf("Enter number of bytes to read: ");
    scanf("%d", &n);

    readNBytes(fileName, n);
    return 0;
}
