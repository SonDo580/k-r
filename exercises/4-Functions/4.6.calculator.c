/*
extension: handle variables

implementation:
- use an array with 26 elements to track variables,
and an extra variable for the most recently printed value.
- use '=x' to assign top value on stack to variable x,
  where x is a character in a-z range
*/

#include <stdio.h>
#include <stdlib.h> // for atof
#include <ctype.h>

#define MAXOP 100  // max size of operand or operator
#define NUMBER '0' // signal that a number was found
#define ANS '_'    // denote the last printed value

enum Commands
{
    INVALID = -1,

    // outside ASCII range
    SET = 1000
};

void push(double);
double pop(void);

int getop(char[]);
int getch(void);
void ungetch(int);

double ans;     // last printed value
double var[26]; // values of a-z variables

/* reverse Polish calculator */
int main()
{
    int type, i;
    double op2;    // operand 2
    char s[MAXOP]; // operand or operator string

    ans = 0.0;
    for (i = 0; i < 26; i++)
        var[i] = 0.0;

    while ((type = getop(s)) != EOF)
    {
        switch (type)
        {
        case NUMBER:
            push(atof(s));
            break;
        case ANS:
            push(ans);
            break;
        case SET:
            var[s[1] - 'a'] = pop();
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
            ans = pop();
            printf("\t%.8g\n", ans);
            break;
        default:
            if (type >= 'a' && type <= 'z')
                push(var[type - 'a']);
            else
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
    {
        if (c != '=')
            return c;

        // handle variable assignment (=x where x in a-z)
        i = 0;
        while ((s[++i] = c = getch()) != ' ' && c != '\t' && c != '\n' && c != EOF)
            ;
        if (i != 2 || !(s[1] >= 'a' && s[1] <= 'z'))
            return INVALID;
        else
        {
            s[i] = '\0';
            if (c != EOF)
                ungetch(c);
            return SET;
        }
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
