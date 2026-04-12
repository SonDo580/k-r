/*
refactor: use 'getline' instead of 'getch' and 'ungetch'
*/

#include <stdio.h>
#include <stdlib.h> // for atof
#include <ctype.h>

#define MAXOP 100    // max size of operand or operator
#define NUMBER '0'   // signal that a number was found
#define MAXLINE 1000 // max input line length

void push(double);
double pop(void);

char line[MAXLINE]; // input line
int pos;            // current position in line

int getop(char[]);
int my_getline(char[], int);

/* reverse Polish calculator */
int main()
{
    int type;
    double op2;    // operand 2
    char s[MAXOP]; // operand or operator string

    while (my_getline(line, MAXLINE) > 0)
    {
        while ((type = getop(s)) != '\n')
        {
            switch (type)
            {
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 == 0.0)
                    printf("error: zero divisor\n");
                else
                    push(pop() / op2);
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
            }
        }

        printf("\t%.8g\n", pop());
    }
    return 0;
}

#define MAXVAL 100 // maximum depth of val stack

int sp = 0;         // next free stack position
double val[MAXVAL]; // value stack

/* push f onto the stack */
void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

/* pop and return top value from stack */
double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else
    {
        printf("error: stack empty\n");
        return 0.0;
    }
}

/* get next character or numeric operand */
int getop(char s[])
{
    int i, c;

    // skip whitespaces
    while (pos < MAXLINE && ((s[0] = c = line[pos++]) == ' ' || c == '\t'))
        ;
    s[1] = '\0';

    if (!isdigit(c) && c != '.')
        return c; // not a number

    i = 0;
    if (isdigit(c)) // collect integer part
        while (pos < MAXLINE && isdigit(s[++i] = c = line[pos++]))
            ;
    if (c == '.') // collect fractional part
        while (pos < MAXLINE && isdigit(s[++i] = c = line[pos++]))
            ;
    s[i] = '\0';
    if (c != EOF)
        pos--;
    return NUMBER;
}

/* get line into s; return length */
int my_getline(char s[], int lim)
{
    int c, i;
    pos = i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}