/*
add commands to:
- print the top element of the stack without popping.
- duplicate the top element of the stack.
- swap the top 2 elements.
- clear the stack.
*/

#include <stdio.h>
#include <stdlib.h> // for atof
#include <ctype.h>
#include <string.h>

#define MAXOP 100  // max size of operand or operator
#define NUMBER '0' // signal that a number was found

enum Commands
{
    INVALID = -1,

    // start outside ASCII range
    PEEK = 1000, // print the top element of the stack without popping.
    DUP,         // duplicate the top element of the stack.
    SWAP,        // swap the top 2 elements.
    CLEAR        // clear the stack.
};

void push(double);
double pop(void);
double peek(void);
void clear(void);
void dup(void);
void swap(void);

int getop(char[]);
int getcmd(char[]);
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
        case CLEAR:
            clear();
            break;
        case PEEK:
            printf("%f", peek());
            break;
        case DUP:
            dup();
            break;
        case SWAP:
            swap();
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
            printf("\t%.8g\n", peek());
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

/* return top value of stack without popping */
double peek(void)
{
    if (sp > 0)
        return val[sp - 1];
    else
    {
        printf("error: stack empty\n");
        return 0.0;
    }
}

/* clear the stack */
void clear(void)
{
    sp = 0;
}

/* duplicate the top element of the stack */
void dup(void)
{
    if (sp > 0)
    {
        push(val[sp - 1]);
    }
}

/* swap the top 2 elements */
void swap(void)
{
    if (sp > 1)
    {
        double tmp = val[sp - 1];
        val[sp - 1] = val[sp - 2];
        val[sp - 2] = tmp;
    }
    else
        printf("error: not enough values to swap\n");
}

/* get next character or numeric operand */
int getop(char s[])
{
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';

    if (!isdigit(c) && c != '.')
    {
        if (c == '\n')
            return c;

        // collect operator or command
        i = 0;
        while (isalpha(s[++i] = getch()))
            ;
        if (s[i] != EOF)
            ungetch(s[i]);
        s[i] = '\0';
        return i == 1 ? c : getcmd(s);
    }

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

/* get corresponding command */
int getcmd(char s[])
{
    if (strcmp(s, "clear") == 0)
        return CLEAR;
    if (strcmp(s, "peek") == 0)
        return PEEK;
    if (strcmp(s, "dup") == 0)
        return DUP;
    if (strcmp(s, "swap") == 0)
        return SWAP;
    return INVALID;
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
