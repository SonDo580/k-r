#include <stdio.h>
#include <string.h>

/* get a line or at most n chars from iop */
char *my_fgets(char *s, int n, FILE *iop)
{
    register int c;
    register char *cs;

    cs = s;
    while (--n > 0 && (c = getc(iop)) != EOF)
        if ((*(cs++) = c) == '\n') // include '\n'
            break;
    *cs = '\0';
    return (c == EOF && cs == s) ? NULL : s;
}

/* put string s on file iop */
int my_fputs(char *s, FILE *iop)
{
    int c;
    while (c = *(s++))
        putc(c, iop);
    return ferror(iop) ? EOF : 0;
}

/* read a line, return length */
int my_getline(char *line, int max)
{
    if (fgets(line, max, stdin) == NULL)
        return 0;
    else
        return strlen(line);
}