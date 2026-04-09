#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

/* Reads N bytes from a file and prints whatever is available */
int main()
{
    char fileName[256];
    int n;
    int fd;
    int bytesRead;
    int totalRead = 0;
    char buffer[128];

    printf("Enter file name: ");
    scanf("%255s", fileName);

    printf("Enter number of bytes to read: ");
    scanf("%d", &n);

    fd = open(fileName, O_RDONLY);
    if (fd == -1)
    {
        perror("open failed");
        return 1;
    }

    while (totalRead < n)
    {
        int toRead = n - totalRead;
        if (toRead > sizeof(buffer))
            toRead = sizeof(buffer);

        bytesRead = read(fd, buffer, toRead);
        if (bytesRead == -1)
        {
            perror("read failed");
            close(fd);
            return 1;
        }

        if (bytesRead == 0)
            break;   /* EOF */

        write(STDOUT_FILENO, buffer, bytesRead);
        totalRead += bytesRead;
    }

    close(fd);
    return 0;
}
