#include <stdio.h>
#include <ctype.h>

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

/* convert string s to double; handle scientific notation */
double atof(char s[])
{
    double val, power;
    int i, sign;

    // skip white space
    for (i = 0; isspace(s[i]); i++)
        ;

    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '-' || s[i] == '+')
        i++;
    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++)
    {
        val = 10.0 * val + (s[i] - '0');
        power *= 10;
    }
    double significand = sign * val / power;

    int exp_sign, exp_val;
    if (s[i] == 'e' || s[i] == 'E')
        i++;
    exp_sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '-' || s[i] == '+')
        i++;
    for (exp_val = 0; isdigit(s[i]); i++)
        exp_val = 10 * exp_val + (s[i] - '0');
    exp_val *= exp_sign;

    return significand * my_pow(10, exp_val);
}

/* helper to print result */
void result(char s[], double expected)
{
    double d = atof(s);
    if (d != expected)
        printf("Input = %s. Expected: %f. Actual: %f\n",
               s, expected, d);
}

int main()
{
    result("21", 21);
    result("-21", -21);
    result("21.", 21);
    result("-21.", -21);
    result("21.0", 21);
    result("-21.0", -21);
    result("21.12", 21.12);
    result("-21.12", -21.12);
    result(".12", 0.12);

    result("1.45e1", 14.5);
    result("-1.45e1", -14.5);
    result("145e-2", 1.45);
    result("-145e-2", -1.45);
    result("1.45E1", 14.5);
    result("-1.45E1", -14.5);
    result("145E-2", 1.45);
    result("-145E-2", -1.45);
}