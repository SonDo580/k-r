/*
Usage: tail -n x: prints the last x lines of input
Optional arguments:
-n: default 10
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXLINES 5000 // max #lines to be read

char *lineptr[MAXLINES]; // pointers to text lines

int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines, int n);

int main(int argc, char *argv[])
{
    int c, n, nlines;

    while (--argc > 0 && (*(++argv))[0] == '-')
        while (c = *(++(argv[0])))
            switch (c)
            {
            case 'n':
                break;
            default:
                printf("tail: illegal option %c\n", c);
                argc = 0;
                break;
            }

    if (argc == 0)
        n = 10;
    else if (argc == 1)
    {
        n = atoi(*argv);
        if (n <= 0)
            printf("nlines must be > 0");
    }
    else
        printf("Usage: tail -n nlines\n");

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0)
    {
        writelines(lineptr, nlines, n);
        return 0;
    }
    else
    {
        printf("error: input too big\n");
        return 1;
    }
}

#define MAXLEN 1000 // max length of any input line

int my_getline(char *, int);
char *alloc(int);

/* read input lines; returns number of lines read. */
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN]; // current line and pointer to it

    nlines = 0;
    while ((len = my_getline(line, MAXLEN)) > 0)
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else
        {
            line[len - 1] = '\0'; // delete '\n'
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    return nlines;
}

/* write the last n lines */
void writelines(char *lineptr[], int nlines, int n)
{
    while (nlines > n)
    {
        nlines--;
        lineptr++;
    }
    while (n-- > 0)
        printf("%s\n", *(lineptr++));
}

/* read a line into s, return length */
int my_getline(char *s, int lim)
{
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF & c != '\n'; i++)
        s[i] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

#define ALLOCSIZE 10000 // available space

static char allocbuf[ALLOCSIZE]; // storage for alloc
static char *allocp = allocbuf;  // next free position

/* return pointer to n characters */
char *alloc(int n)
{
    if (allocbuf + ALLOCSIZE - allocp >= n)
    { // it fits (allocp would be at most one beyond the end of allocbuf)
        allocp += n;
        return allocp - n;
    }
    else
        // not enough room
        return 0; // NULL
}