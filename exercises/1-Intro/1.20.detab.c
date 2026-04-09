#include <stdio.h>

#define TAB_STOP 8

/* Replace tab with spaces to the next tab stop */
int main()
{
    int c, i;
    int len; // current line length
    len = 0;

    while ((c = getchar()) != EOF)
    {
        if (c == '\n')
        {
            putchar(c);
            len = 0;
        }
        else if (c == '\t')
        {
            int spaces_required = TAB_STOP - len % TAB_STOP;
            for (i = 0; i < spaces_required; ++i)
                putchar(' ');
            len = len + spaces_required;
        }
        else
        {
            putchar(c);
            ++len;
        }
    }

    return 0;
}