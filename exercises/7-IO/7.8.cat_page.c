/*
print contents of a set of files,
starting each new one on a new page,
with a title and running page count for each file.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXLEN 1000 // max length of any line
#define PAGESIZE 20 // number of lines in a page

char *get_header(char *header, int pagenum, char *filename);

int main(int argc, char *argv[])
{
    char *prog = argv[0]; // program name for errors
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <files...>\n", prog);
        exit(1);
    }
    if (PAGESIZE <= 1)
    {
        fprintf(stderr, "%s: invalid page size: %d\n", prog, PAGESIZE);
        exit(1);
    }

    FILE *fp;
    char line[MAXLEN];
    char header[MAXLEN]; // page header
    int pagenum;         // current page number
    int pageline;        // current line in current page
    pagenum = pageline = 1;

    while (--argc > 0)
        if ((fp = fopen(*++argv, "r")) == NULL)
        {
            fprintf(stderr, "%s: can't open %s\n", prog, *argv);
            exit(1);
        }
        else
        {
            while (fgets(line, MAXLEN, fp) != NULL)
            {
                if (pageline++ == 1)
                    fputs(get_header(header, pagenum, *argv), stdout);
                fputs(line, stdout);
                if (++pageline > PAGESIZE)
                {
                    pageline = 1;
                    pagenum++;
                }
            }
            fclose(fp);
        }

    if (ferror(stdout))
    {
        fprintf(stderr, "%s: error writing stdout\n", prog);
        exit(2);
    }

    exit(0);
}

char *get_header(char *header, int pagenum, char *filename)
{
    sprintf(header,
            "===== Page: %d (File: %s) =====\n",
            pagenum, filename);
    return header;
}