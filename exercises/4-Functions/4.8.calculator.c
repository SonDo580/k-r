/*
simplification: there will never be more than one character of pushback
-> modify 'getch' and 'ungetch'
*/

#include <stdio.h>
#include <stdlib.h> // for atof
#include <ctype.h>

#define MAXOP 100  // max size of operand or operator
#define NUMBER '0' // signal that a number was found

void push(double);
double pop(void);

int getop(char[]);
int getch(void);
void ungetch(int);

/* reverse Polish calculator */
int main()
{
    int type;
    double op2;    // operand 2
    char s[MAXOP]; // operand or operator string

    while ((type = getop(s)) != EOF)
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
        case '\n':
            printf("\t%.8g\n", pop());
            break;
        default:
            printf("error: unknown command %s\n", s);
            break;
        }
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

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';

    if (!isdigit(c) && c != '.')
        return c; // not a number

    i = 0;
    if (isdigit(c)) // collect integer part
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.') // collect fractional part
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
}

int pushed_back = -1; // pushed-back character

/* get a (possibly pushed-back) character */
int getch(void)
{
    return (pushed_back != -1) ? pushed_back : getchar();
}

/* push character back on input */
void ungetch(int c)
{
    pushed_back = c;
}
