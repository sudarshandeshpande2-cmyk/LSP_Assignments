#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

#define PATH_MAX_LEN PATH_MAX

/* ===== FUNCTION PROTOTYPES ===== */

char get_type_marker(struct dirent *entry);
int is_real_directory(const char fullpath[]);
void print_indent(int depth);
void print_branch(int depth, int is_last);
void print_entry(int depth, int is_last, const char name[], char type);
int traverse_directory(const char dirpath[], int depth);

/*
 * Function Name: get_type_marker
 * ------------------------------
 * Returns type marker based on d_type
 */
char get_type_marker(struct dirent *entry)
{
    if (entry->d_type == DT_DIR)
        return 'D';
    if (entry->d_type == DT_REG)
        return 'F';
    if (entry->d_type == DT_LNK)
        return 'L';
    return '?';
}

/*
 * Function Name: is_real_directory
 * --------------------------------
 * Checks whether path is a real directory (not symlink)
 */
int is_real_directory(const char fullpath[])
{
    struct stat st;

    /*
     * lstat() system call
     * Used to avoid following symbolic links
     */
    if (lstat(fullpath, &st) == -1)
        return 0;

    return S_ISDIR(st.st_mode) && !S_ISLNK(st.st_mode);
}

/*
 * Function Name: print_indent
 * ---------------------------
 * Prints indentation based on recursion depth
 */
void print_indent(int depth)
{
    for (int i = 0; i < depth; i++)
        printf("│   ");
}

/*
 * Function Name: print_branch
 * ---------------------------
 * Prints tree branch symbols
 */
void print_branch(int depth, int is_last)
{
    print_indent(depth);
    if (is_last)
        printf("└── ");
    else
        printf("├── ");
}

/*
 * Function Name: print_entry
 * --------------------------
 * Prints a single tree entry with type marker
 */
void print_entry(int depth, int is_last, const char name[], char type)
{
    print_branch(depth, is_last);
    printf("[%c] %s\n", type, name);
}

/*
 * Function Name: traverse_directory
 * ---------------------------------
 * Recursively traverses directory and prints tree structure
 */
int traverse_directory(const char dirpath[], int depth)
{
    DIR *dp = opendir(dirpath);
    if (dp == NULL)
    {
        print_indent(depth);
        printf("[?] Cannot open: %s\n", dirpath);
        return -1;
    }

    struct dirent *entry;
    int total_entries = 0;

    /* First pass: count valid entries */
    while ((entry = readdir(dp)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0)
            continue;

        total_entries++;
    }

    rewinddir(dp);

    int current = 0;

    /* Second pass: process entries */
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

        char type = get_type_marker(entry);
        int is_last = (++current == total_entries);

        print_entry(depth, is_last, entry->d_name, type);

        /* Recurse only for real directories */
        if (type == 'D' && is_real_directory(fullpath))
        {
            traverse_directory(fullpath, depth + 1);
        }
    }

    /*
     * closedir() system call
     */
    closedir(dp);
    return 0;
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

    printf("[D] %s\n", rootPath);

    traverse_directory(rootPath, 0);
    return 0;
}
