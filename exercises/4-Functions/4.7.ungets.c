#include <stdio.h>

#define BUFSIZE 100

char buf[BUFSIZE]; // buffer for ungetch
int bufp = 0;      // next free position in buf

/* get a (possibly pushed-back) character */
int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* push character back on input */
void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

/* push an entire string back on input */
void ungets(char s[])
{
    // should push in reverse order since 'getch' get the top value first

    // find end of s
    int i, end;
    for (i = 0; s[i] != '\0'; i++)
        ;

    // (optional) check if there's enough room in buffer
    if (i > (BUFSIZE - bufp))
        printf("ungets: too many characters\n");

    end = i - 1;
    for (i = end; i >= 0; i--)
        ungetch(s[i]);
}