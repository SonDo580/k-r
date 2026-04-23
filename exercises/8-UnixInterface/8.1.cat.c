#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

/* cat: concatenate file contents; use system calls */
int main(int argc, char *argv[])
{
    int fd;
    void filecopy(int in_fd, int out_fd, char *in_name, char *out_name, char *prog);
    char *prog = argv[0]; // program name for errors

    if (argc == 1) // no args; copy standard input
        filecopy(0, 1, "stdin", "stdout", prog);
    else
        while (--argc > 0)
            if ((fd = open(*++argv, O_RDONLY)) == -1)
            {
                fprintf(stderr, "%s: can't open %s\n",
                        prog, *argv);
                exit(1);
            }
            else
            {
                filecopy(fd, 1, *argv, "stdout", prog);
                close(fd);
            }

    return 0;
}

/* filecopy: copy file in_fd to file out_fd */
void filecopy(int in_fd, int out_fd, char *in_name, char *out_name, char *prog)
{
    int n;
    char buf[BUFSIZ];

    while ((n = read(in_fd, buf, BUFSIZ)) > 0)
        if (write(out_fd, buf, n) != n)
        {
            fprintf(stderr, "%s: write error on file %s\n",
                    prog, out_name);
            exit(1);
        }

    if (n < 0)
    {
        fprintf(stderr, "%s: read error on file %s\n",
                prog, in_name);
        exit(1);
    }
}