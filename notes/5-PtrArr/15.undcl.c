/* Convert word description to C declaration

EXAMPLE:
- description: "x is function returning pointer to array of pointers to functions returning char"
- abbreviated: "x () * [] * () char"
  . allow us to use the same 'gettoken' function
- output: char (*(*x())[])()

GRAMMAR: see 'dcl.c'
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum
{
    NAME,
    PARENS,
    BRACKETS
};

int gettoken(void);
char token[MAXTOKEN]; // last token string
char name[MAXTOKEN];  // identifier name
char out[1000];

int main()
{
    int type; // type of last token
    char temp[MAXTOKEN];

    while (gettoken() != EOF)
    {
        strcpy(out, token); // first token is identifier name
        while ((type = gettoken()) != '\n')
            if (type == PARENS || type == BRACKETS)
                strcat(out, token);
            else if (type == '*')
            {
                sprintf(temp, "(*%s)", out);
                strcpy(out, temp);
            }
            else if (type == NAME)
            { // data type
                sprintf(temp, "%s %s", token, out);
                strcpy(out, temp);
            }
            else
                printf("invalid input at %s\n", token);
    }
    return 0;
}

/* return next token
- skip blanks and tabs.
- a token can be:
  . a name
  . a pair of parentheses.
  . a pair of brackets perhaps including a number.
  . any other single character.
*/
int gettoken(void)
{
    int c, getch(void);
    void ungetch(int);
    char *p = token;

    // skip blanks and tabs
    while ((c = getch()) == ' ' || c == '\t')
        ;

    if (c == '(')
    {
        if ((c = getch()) == ')')
        {
            strcpy(token, "()");
            return PARENS;
        }
        else
        {
            ungetch(c);
            return '(';
        }
    }
    else if (c == '[')
    {
        for (*(p++) = c; (*(p++) = getch()) != ']';)
            ;
        *p = '\0';
        return BRACKETS;
    }
    else if (isalpha(c))
    {
        for (*(p++) = c; isalnum(c = getch());)
            *(p++) = c;
        *p = '\0';
        ungetch(c);
        return NAME;
    }
    else
        return c;
}

#define BUFSIZE 100

static char buf[BUFSIZE]; // buffer for ungetch
static int bufp = 0;      // next free position in buf

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