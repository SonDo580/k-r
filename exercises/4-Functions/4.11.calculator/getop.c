#include <stdio.h>
#include <ctype.h>
#include "calc.h"

static int next = -1;

/* get next character or numeric operand */
int getop(char s[])
{
    int i, c;

    while ((s[0] = c = (next != -1) ? next : getchar()) == ' ' ||
           c == '\t')
        next = -1;
    s[1] = '\0';

    if (!isdigit(c) && c != '.')
        return c; // not a number

    i = 0;
    if (isdigit(c)) // collect integer part
        while (isdigit(s[++i] = c = getchar()))
            ;
    if (c == '.') // collect fractional part
        while (isdigit(s[++i] = c = getchar()))
            ;
    s[i] = '\0';
    if (c != EOF)
        next = c;
    return NUMBER;
}