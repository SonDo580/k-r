#include <ctype.h>
#include <stdio.h>

int getch(void);
void ungetch(int);

/* get next integer from input into *pn; returns:
- EOF for end of file
- 0 if input is not a number
- positive value if input contains a valid number
*/
int getint(int *pn)
{
    int c, sign;

    // skip whitespaces
    while (isspace(c = getch()))
        ;

    if (!isdigit(c) && c != EOF && c != '+' && c != '-')
    {
        // not a number
        ungetch(c);
        return 0;
    }

    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-')
        c = getch();

    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * (*pn) + (c - '0');
    *pn *= sign;

    if (c != EOF)
        ungetch(c);
    return c;
}

#define SIZE 10

int main()
{
    int n, array[SIZE];
    for (n = 0; n < SIZE && getint(&array[n]) != EOF; n++)
        ;
    for (n = 0; n < SIZE; n++)
        printf(" %d", array[n]);
    printf("\n");
}

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
