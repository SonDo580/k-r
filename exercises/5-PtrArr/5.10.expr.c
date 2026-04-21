#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define NUMBER '0'  // signal that a number was found
#define INVALID '1' // invalid type

void push(double);
double pop(void);

int get_op(char *arg, double *val);

/* evaluate a reverse Polish notation expression from command-line

IMPORTANT!
- The shell treats '*' as wildcard, we must escape or quote it.
  For example: 2 3 4 + *
-> escape:  2 3 4 + \*
-> quote:   2 3 4 + '*' OR 2 3 4 + "*"

*/
int main(int argc, char *argv[])
{
    int type;
    double f, op2;

    while (--argc > 0)
    {
        type = get_op(*(++argv), &f);
        switch (type)
        {
        case NUMBER:
            push(f);
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
            printf("error: unknown command %s\n", *argv);
            break;
        }
    }
    printf("%g\n", pop());
}

/* get next operator or numeric operand */
int get_op(char *arg, double *f)
{
    if (strlen(arg) == 1 && (arg[0] == '+' || arg[0] == '-' || arg[0] == '*' || arg[0] == '/'))
        return arg[0];

    if (!isdigit(arg[0]) && arg[0] != '.')
        return INVALID;

    *f = atof(arg);
    return NUMBER;
}

#define MAXVAL 100 // maximum depth of the stack

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
