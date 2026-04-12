#include <stdio.h>
#include <stdlib.h>
#include "calc.h"

#define MAXOP 100 // max size of operand or operator

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