#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define SIZE 1024

/* ===== FUNCTION PROTOTYPES ===== */

void mode_to_string(mode_t mode, char buf[]);
void build_full_path(char dir[], char name[], char fullpath[]);
char *dtype_to_string(unsigned char dt);
void get_mod_time(time_t mtime, char timestr[]);

/*
 * Function Name: mode_to_string
 * -----------------------------
 * Converts file mode to rwxr-xr-x format
 */
void mode_to_string(mode_t mode, char buf[])
{
    /* File type */
    if (S_ISREG(mode))
        buf[0] = '-';
    else if (S_ISDIR(mode))
        buf[0] = 'd';
    else if (S_ISLNK(mode))
        buf[0] = 'l';
    else
        buf[0] = '?';

    /* Owner permissions */
    buf[1] = (mode & S_IRUSR) ? 'r' : '-';
    buf[2] = (mode & S_IWUSR) ? 'w' : '-';
    buf[3] = (mode & S_IXUSR) ? 'x' : '-';

    /* Group permissions */
    buf[4] = (mode & S_IRGRP) ? 'r' : '-';
    buf[5] = (mode & S_IWGRP) ? 'w' : '-';
    buf[6] = (mode & S_IXGRP) ? 'x' : '-';

    /* Other permissions */
    buf[7] = (mode & S_IROTH) ? 'r' : '-';
    buf[8] = (mode & S_IWOTH) ? 'w' : '-';
    buf[9] = (mode & S_IXOTH) ? 'x' : '-';

    buf[10] = '\0';
}

/*
 * Function Name: build_full_path
 * ------------------------------
 * Builds full path using directory and entry name
 */
void build_full_path(char dir[], char name[], char fullpath[])
{
    size_t dir_len = strlen(dir);

    if (dir_len > 0 && dir[dir_len - 1] != '/')
        snprintf(fullpath, SIZE, "%s/%s", dir, name);
    else
        snprintf(fullpath, SIZE, "%s%s", dir, name);
}

/*
 * Function Name: dtype_to_string
 * ------------------------------
 * Converts d_type to readable string
 */
char *dtype_to_string(unsigned char dt)
{
    switch (dt)
    {
    case DT_REG:
        return "file";
    case DT_DIR:
        return "dir";
    case DT_LNK:
        return "link";
    default:
        return "other";
    }
}

/*
 * Function Name: get_mod_time
 * ---------------------------
 * Converts modification time to readable format
 */
void get_mod_time(time_t mtime, char timestr[])
{
    struct tm *tm_info = localtime(&mtime);
    strftime(timestr, 64, "%Y-%m-%d %H:%M:%S", tm_info);
}

int main(int argc, char *argv[])
{
    DIR *dp = NULL;
    struct dirent *ptr = NULL;

    if (argc != 2)
    {
        printf("Usage : %s <DirectoryPath>\n", argv[0]);
        exit(1);
    }

    /*
     * opendir() system call
     * Opens directory stream
     */
    dp = opendir(argv[1]);
    if (dp == NULL)
    {
        perror("opendir");
        return -1;
    }

    /*
     * readdir() system call
     * Reads directory entries
     */
    while ((ptr = readdir(dp)) != NULL)
    {
        /* Skip . and .. */
        if (strcmp(ptr->d_name, ".") == 0 ||
            strcmp(ptr->d_name, "..") == 0)
        {
            continue;
        }

        char fullpath[SIZE];
        struct stat st;
        char perm[11];
        char timestr[64];

        /* Build full path */
        build_full_path(argv[1], ptr->d_name, fullpath);

        /*
         * lstat() system call
         * Retrieves file information
         */
        if (lstat(fullpath, &st) == -1)
        {
            perror("lstat");
            continue;
        }

        /* Convert attributes */
        mode_to_string(st.st_mode, perm);
        get_mod_time(st.st_mtime, timestr);

        /* Print entry details */
        printf("%s  %s  %ld  %s  %s\n",
               ptr->d_name,
               dtype_to_string(ptr->d_type),
               (long)st.st_size,
               perm,
               timestr);
    }

    /*
     * closedir() system call
     * Closes directory stream
     */
    closedir(dp);

    return 0;
}
