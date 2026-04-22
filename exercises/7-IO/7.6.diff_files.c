/* compare two files, printing the first line where they differ */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXLEN 1000 // max len of any line

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: ./7.6.diff_files.exe file1 file2");
        exit(1);
    }

    FILE *fp1, *fp2;
    char *prog = argv[0]; // program name for errors

    if ((fp1 = fopen(argv[1], "r")) == NULL)
    {
        fprintf(stderr, "%s: can't open %s\n", prog, argv[1]);
        exit(1);
    }
    if ((fp2 = fopen(argv[2], "r")) == NULL)
    {
        fprintf(stderr, "%s: can't open %s\n", prog, argv[2]);
        exit(1);
    }

    char s1[MAXLEN], s2[MAXLEN]; // current line in file1, file2
    char *r1, *r2;               // result of fgets on file1, file2
    do
    {
        r1 = fgets(s1, MAXLEN, fp1);
        r2 = fgets(s2, MAXLEN, fp2);
    } while (r1 != NULL && r2 != NULL && strcmp(s1, s2) == 0);

    if (r1 != NULL)
        printf("s1: %s", s1);
    if (r2 != NULL)
        printf("s2: %s", s2);

    exit(0);
}