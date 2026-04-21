#include <ctype.h>
#include <stdio.h>

int getch(void);
void ungetch(int);


/* helper: raise base to n-th power */
double my_pow(int base, int n0)
{
    int sign;
    double result;

    long n = (long)n0;  // cast to type to handle INT_MIN
    if ((sign = n) < 0) // record sign
        n = -n;         // make n positive

    for (result = 1; n > 0; n--)
        result *= base;

    return sign < 0 ? 1 / result : result;
}

/* get next float from input into *pn; returns:
- EOF for end of file
- 0 if input is not a number
- positive value if input contains a valid number
*/
int getfloat(float *pn)
{
    int c, sign, power;

    // skip whitespaces
    while (isspace(c = getch()))
        ;

    if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.')
    {
        // not a number
        ungetch(c);
        return 0;
    }

    // handle significand
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-')
        c = getch();
    for (*pn = 0.0; isdigit(c); c = getch())
        *pn = 10.0 * (*pn) + (c - '0');
    if (c == '.')
        c = getch();
    for (power = 1.0; isdigit(c); c = getch())
    {
        *pn = 10.0 * (*pn) + (c - '0');
        power *= 10;
    }
    *pn = sign * (*pn) / power;

    // handle exponent
    int exp_val, exp_sign;
    exp_val = 0;
    if (c == 'e' || c == 'E') {
        c = getch();
        exp_sign = (c == '-') ? -1 : 1;
        if (c == '-' || c == '+')
            c = getch();
        for (;isdigit(c); c = getch())
            exp_val = 10 * exp_val + (c - '0');
        exp_val *= exp_sign;
    }
    *pn *= my_pow(10, exp_val);

    if (c != EOF)
        ungetch(c);
    return c;
}

#define SIZE 10

int main()
{
    int n;
    float array[SIZE];
    for (n = 0; n < SIZE && getfloat(&array[n]) != EOF; n++)
        ;
    for (n = 0; n < SIZE; n++)
        printf(" %f", array[n]);
    printf("\n");
    // sample: . .1 1. 1.2 -. -.1 -1. -1.2 1.45e2 145e-2
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
