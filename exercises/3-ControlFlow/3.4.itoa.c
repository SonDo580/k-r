#include <stdio.h>
#include <limits.h>
#include <string.h>

/* helper: reverse s in place */
void reverse(char s[])
{
    int c, i, j;
    for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
    {
        c = s[i], s[i] = s[j], s[j] = c;
    }
}

/* (BUGGY version) convert int n to characters in s */
void buggy_itoa(int n, char s[])
{
    int i, sign;

    if ((sign = n) < 0) // record sign
        n = -n;         // make n positive
    /*
    BUG (-Tmin = Tmin)
    */

    // generate digits in reverse order
    i = 0;
    do
    {
        s[i++] = n % 10 + '0'; // get next digit
    } while ((n /= 10) > 0); // delete it

    // assign sign
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';

    reverse(s);
}

/* convert int n to characters in s */
void itoa(int n0, char s[])
{
    int i, sign;

    /* BUG FIX: Cast n to long type */
    long n = (long)n0;

    if ((sign = n) < 0) // record sign
        n = -n;         // make n positive

    // generate digits in reverse order
    i = 0;
    do
    {
        s[i++] = n % 10 + '0'; // get next digit
    } while ((n /= 10) > 0); // delete it

    // assign sign
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';

    reverse(s);
}

/* helper to print result */
void result(int n, char s[], char expected[])
{
    itoa(n, s);
    if (strcmp(expected, s) != 0)
        printf("Input: %d. Expected: %s. Actual: %s\n",
               n, expected, s);
}

int main()
{
    int n[] = {0, 2, -1, INT_MAX, INT_MIN};
    char *expected[] = {"0", "2", "-1", "2147483647", "-2147483648"};

    char s[100];
    for (int i = 0; i < 5; i++)
        result(n[i], s, expected[i]);
}