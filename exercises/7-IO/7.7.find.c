#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLEN 1000 // max length of a line

int find_in_file(char *line, int maxlen, FILE *fp, char *filename, char *pattern);

/* print lines that match pattern from 1st arg;
find in the specified files, or stdin if files not specified */
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: ./7.7.find.exe pattern [optional files]\n");
        exit(1);
    }

    char line[MAXLEN];
    int found = 0;

    char *prog = argv[0]; // program name for errors
    char *pattern = argv[1];

    if (argc == 2) // no files specified, find in stdin
        return find_in_file(line, MAXLEN, stdin, "stdin", pattern);

    FILE *fp;
    argc -= 1; // skip program name
    argv += 1; // skip program name
    while (--argc > 0) // find in each file
        if ((fp = fopen(*(++argv), "r")) == NULL)
        {
            fprintf(stderr, "%s: can't open %s\n", prog, *argv);
            exit(1);
        }
        else
        {
            found += find_in_file(line, MAXLEN, fp, *argv, pattern);
            fclose(fp);
        }

    return found;
}

/* print lines that match pattern in a file; return number of matching lines */
int find_in_file(char *line, int maxlen, FILE *fp, char *filename, char *pattern)
{
    int found = 0;
    while (fgets(line, maxlen, fp) != NULL)
        if (strstr(line, pattern) != NULL)
        {
            printf("%s: %s", filename, line);
            found++;
        }
    return found;
}