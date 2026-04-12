#include <stdio.h>
#include <limits.h>
#include <string.h>

/* convert int n to characters in s; return current i
*/
int itoa(int n0, char s[], int i)
{
    long n = (long)n0; // cast to 'long' to handle INT_MIN

    if (n < 0)
    {
        s[i++] = '-'; // record sign
        n = -n;       // make n positive
    }

    if (n / 10)
        i = itoa(n / 10, s, i);
    s[i++] = n % 10 + '0';
    s[i] = '\0';
    return i;
}

/* helper to print result */
void result(int n, char s[], char expected[])
{
    itoa(n, s, 0);
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