#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINES 5000 // max #lines to be sorted
char *lineptr[MAXLINES];
int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void my_qsort(void *lineptr[], int left, int right,
              int (*comp)(void *, void *),
              int reverse);
int numcmp(char *, char *);
int fold_strcmp(char *, char *);

/* sort input lines */
int main(int argc, char *argv[])
{
    int nlines;      // number of input lines read
    int numeric = 0; // 1 if numeric sort
    int reverse = 0; // 1 if sort in reverse
    int fold = 0;    // 1 if fold lower/upper case

    while (--argc > 0 && (*(++argv))[0] == '-')
        if (strcmp(*argv, "-n") == 0)
            numeric = 1;
        else if (strcmp(*argv, "-r") == 0)
            reverse = 1;
        else if (strcmp(*argv, "-f") == 0)
            fold = 1;
        else
        {
            printf("Invalid option: %s\n", *argv);
            return 1;
        }

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0)
    {
        my_qsort((void **)lineptr, 0, nlines - 1,
                 (int (*)(void *, void *))(numeric ? numcmp : (fold ? fold_strcmp : strcmp)),
                 reverse);
        writelines(lineptr, nlines);
        return 0;
    }
    else
    {
        printf("input too big to sort\n");
        return 1;
    }
}

void my_qsort(void *v[], int left, int right,
              int (*comp)(void *, void *),
              int reverse)
{
    int i, last;

    void swap(void *v[], int, int);

    // do nothing if array contains fewer than 2 elements
    if (left >= right)
        return;

    // move partition elem to left
    swap(v, left, (left + right) / 2);
    last = left;

    // partition
    for (i = left + 1; i <= right; i++)
    {
        int comp_result = (*comp)(v[i], v[left]);
        if (reverse)
            comp_result = -comp_result;
        if (comp_result < 0)
            swap(v, ++last, i);
    }

    // restore partition elem
    swap(v, left, last);

    // sort the 2 partitions
    my_qsort(v, left, last - 1, comp, reverse);
    my_qsort(v, last + 1, right, comp, reverse);
}

/* interchange 2 elements */
void swap(void *v[], int i, int j)
{
    void *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

/* compare s1 and s2 on a leading numeric value */
int numcmp(char *s1, char *s2)
{
    double v1, v2;
    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

/* compare s1 and s2 lexicographically, ignore case when comparing character */
int fold_strcmp(char *s1, char *s2)
{
    int i;
    for (i = 0; tolower(s1[i]) == tolower(s2[i]); i++)
        if (s1[i] == '\0')
            return 0;
    return tolower(s1[i]) - tolower(s2[i]);
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