/*
Rewrite 'readlines' to store lines in an array supplied by 'main',
rather than calling 'alloc' to maintain storage
*/

#include <stdio.h>
#include <string.h>

#define MAXLINES 5000 // max #lines to be sorted
#define MAXLEN 1000   // max length of any input line

char *lineptr[MAXLINES]; // pointers to text lines

int readlines(char *lineptr[], int nlines, char *p);
void writelines(char *lineptr[], int nlines);
void qsort(char *v[], int left, int right);

/* sort input lines */
int main()
{
    int nlines;                   // number of input lines read
    char buf[MAXLINES * MAXLEN]; // buffer to store all lines
    char *p = buf;                // pointer to the next free slot in 'buf'

    if ((nlines = readlines(lineptr, MAXLINES, p)) >= 0)
    {
        qsort(lineptr, 0, nlines - 1);
        writelines(lineptr, nlines);
        return 0;
    }
    else
    {
        printf("error: input too big to short\n");
        return 1;
    }
}

int my_getline(char *, int);

/* read input lines; returns number of lines read */
int readlines(char *lineptr[], int maxlines, char *p)
{
    int len, nlines;
    char line[MAXLEN]; // current line

    nlines = 0;
    while ((len = my_getline(line, MAXLEN)) > 0)
        if (nlines >= maxlines)
            return -1;
        else
        {
            line[len - 1] = '\0'; // delete '\n'
            strcpy(p, line);
            lineptr[nlines++] = p;
            p += len;
        }
    return nlines;
}

/* write output lines */
void writelines(char *lineptr[], int nlines)
{
    while (nlines-- > 0)
        printf("%s\n", *(lineptr++));
}

/* Read a line into s, return length */
int my_getline(char *s, int lim)
{
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;
    if (c == '\n')
    {
        s[i++] = c;
    }
    s[i] = '\0';
    return i;
}

/* helper: interchange v[i] and v[j] */
void swap(char *v[], int i, int j)
{
    char *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

/* sort v[] into increasing order */
void qsort(char *v[], int left, int right)
{
    int i, last;

    // do nothing if array has less than 2 elements
    if (left >= right)
        return;

    // move partition elem to v[left]
    swap(v, left, (left + right) / 2);
    last = left;

    // partition
    for (i = left + 1; i <= right; i++)
        if (strcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);

    // restore partition elem
    swap(v, left, last);

    // sort the 2 partitions
    qsort(v, left, last - 1);
    qsort(v, last + 1, right);
}
