#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

#define PATH_MAX_LEN PATH_MAX

/* ===== GLOBAL COUNTERS ===== */

long long total_files = 0;
long long total_dirs = 0;
long long total_size = 0;
char largest_file[PATH_MAX_LEN] = "";
long long largest_size = 0;

/* ===== FUNCTION PROTOTYPES ===== */

void update_largest_file(char filename[], long long size);
void process_file(char fullpath[], struct stat *st);
int is_traversable_dir(char fullpath[]);
void traverse_directory(char dirpath[]);

/*
 * Function Name: update_largest_file
 * ----------------------------------
 * Updates largest file name and size
 */
void update_largest_file(char filename[], long long size)
{
    if (size > largest_size)
    {
        largest_size = size;
        strncpy(largest_file, filename, PATH_MAX_LEN - 1);
        largest_file[PATH_MAX_LEN - 1] = '\0';
    }
}

/*
 * Function Name: process_file
 * ---------------------------
 * Processes only regular files for size calculation
 */
void process_file(char fullpath[], struct stat *st)
{
    /*
     * Only regular files contribute to size
     * Symlinks are treated as objects, not targets
     */
    if (S_ISREG(st->st_mode))
    {
        total_files++;
        total_size += st->st_size;
        update_largest_file(fullpath, st->st_size);
    }
}

/*
 * Function Name: is_traversable_dir
 * --------------------------------
 * Checks whether directory can be traversed
 * (real directory, not symbolic link)
 */
int is_traversable_dir(char fullpath[])
{
    struct stat st;

    /*
     * lstat() system call
     * Prevents following symbolic links
     */
    if (lstat(fullpath, &st) == -1)
        return 0;

    return S_ISDIR(st.st_mode) && !S_ISLNK(st.st_mode);
}

/*
 * Function Name: traverse_directory
 * ---------------------------------
 * Recursively traverses directory tree
 */
void traverse_directory(char dirpath[])
{
    DIR *dp = opendir(dirpath);
    if (dp == NULL)
        return;

    /*
     * Count directory when we enter it
     */
    total_dirs++;

    struct dirent *entry;

    while ((entry = readdir(dp)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0)
            continue;

        char fullpath[PATH_MAX_LEN];

        /*
         * Build full path using snprintf
         */
        snprintf(fullpath, sizeof(fullpath),
                 "%s/%s", dirpath, entry->d_name);

        struct stat st;

        /*
         * lstat() system call
         * Retrieves metadata without following symlinks
         */
        if (lstat(fullpath, &st) == -1)
            continue;

        /* Process files */
        process_file(fullpath, &st);

        /* Recurse only into real directories */
        if (is_traversable_dir(fullpath))
        {
            traverse_directory(fullpath);
        }
    }

    /*
     * closedir() system call
     */
    closedir(dp);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <directory>\n", argv[0]);
        exit(1);
    }

    char rootPath[PATH_MAX_LEN];

    /*
     * realpath() resolves absolute path
     */
    if (realpath(argv[1], rootPath) == NULL)
    {
        perror("realpath");
        exit(1);
    }

    /* Start recursive traversal */
    traverse_directory(rootPath);

    /* Final report */
    printf("Files: %lld\n", total_files);
    printf("Dirs : %lld\n", total_dirs);
    printf("Total Size: %lld bytes\n", total_size);
    printf("Largest: %s (%lld bytes)\n", largest_file, largest_size);

    return 0;
}
