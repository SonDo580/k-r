#include <stdio.h>

/* print n in decimal */
void printd(int n)
{
    // this function can fail on Tmin

    if (n < 0)
    {
        putchar('-');
        n = -n;
    }
    if (n / 10)
        printd(n / 10); // recurse
    putchar(n % 10 + '0');
}