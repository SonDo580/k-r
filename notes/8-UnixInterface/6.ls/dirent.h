#define NAME_MAX 14 // longest filename; system-dependent

/* portable directory entry */
typedef struct
{
    long ino;                // inode number
    char name[NAME_MAX + 1]; // name + '\0'
} Dirent;

/* minimal DIR (similar to FILE): no buffering, etc. */
typedef struct
{
    int fd;   // file descriptor for the directory
    Dirent d; // the directory entry
} DIR;

DIR *my_opendir(char *filename);
Dirent *my_readdir(DIR *dfd);
void my_closedir(DIR *dfd);