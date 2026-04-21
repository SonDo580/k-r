#include <stdio.h>
#include <string.h>

#define MAXLINES 5000 // max #lines to be sorted

char *lineptr[MAXLINES]; // pointers to text lines

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void qsort(char *v[], int left, int right);

/* sort input lines */
int main()
{
    int nlines; // number of input lines read
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0)
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

#define MAXLEN 1000 // max length of any input line

int my_getline(char *, int);
char *alloc(int);

/* read input lines; returns number of lines read */
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

#define ALLOCSIZE 10000 // available space

static char allocbuf[ALLOCSIZE]; // storage for alloc
static char *allocp = allocbuf;  // next free position

/* returns pointer to n characters */
char *alloc(int n)
{
    if (allocbuf + ALLOCSIZE - allocp >= n)
    { // it fits (allocp would be at most one beyond the end of allocbuf)
        allocp += n;
        return allocp - n; // old p
    }
    else
        // not enough room
        return NULL;
}