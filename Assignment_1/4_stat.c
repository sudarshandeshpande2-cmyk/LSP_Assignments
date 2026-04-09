#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

/*
 * Displays metadata of a file using stat()
 */
int main()
{
    char fileName[256];
    struct stat fileInfo;

    printf("Enter file name: ");
    scanf("%255s", fileName);

    /*stat gives metadata to structure*/

    if (stat(fileName, &fileInfo) == -1)
    {
        perror("stat failed");
        return 1;
    }

    printf("\n--- File Information ---\n");

    printf("File size        : %ld bytes\n", fileInfo.st_size);
    printf("Inode number     : %ld\n", fileInfo.st_ino);
    printf("Hard links       : %ld\n", fileInfo.st_nlink);
    printf("Owner UID        : %d\n", fileInfo.st_uid);
    printf("Group GID        : %d\n", fileInfo.st_gid);

    /* File type */
    if (S_ISREG(fileInfo.st_mode))
        printf("File type        : Regular file\n");
    else if (S_ISDIR(fileInfo.st_mode))
        printf("File type        : Directory\n");
    else if (S_ISCHR(fileInfo.st_mode))
        printf("File type        : Character device\n");
    else if (S_ISBLK(fileInfo.st_mode))
        printf("File type        : Block device\n");
    else if (S_ISLNK(fileInfo.st_mode))
        printf("File type        : Symbolic link\n");
    else
        printf("File type        : Other\n");

    /* Permissions */
    printf("Permissions      : ");
    printf((fileInfo.st_mode & S_IRUSR) ? "r" : "-");
    printf((fileInfo.st_mode & S_IWUSR) ? "w" : "-");
    printf((fileInfo.st_mode & S_IXUSR) ? "x" : "-");
    printf((fileInfo.st_mode & S_IRGRP) ? "r" : "-");
    printf((fileInfo.st_mode & S_IWGRP) ? "w" : "-");
    printf((fileInfo.st_mode & S_IXGRP) ? "x" : "-");
    printf((fileInfo.st_mode & S_IROTH) ? "r" : "-");
    printf((fileInfo.st_mode & S_IWOTH) ? "w" : "-");
    printf((fileInfo.st_mode & S_IXOTH) ? "x\n" : "-\n");

    /* Time information */
    printf("Last access time : %s", ctime(&fileInfo.st_atime));
    printf("Last modify time : %s", ctime(&fileInfo.st_mtime));

    return 0;
}
