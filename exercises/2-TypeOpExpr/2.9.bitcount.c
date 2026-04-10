#include <stdio.h>

/* count 1 bits from x (hamming distance)
. x &= (x - 1) deletes the right most 1 bit in x
  -> count number of "deletions" until x becomes 0.

Explanation:
. x bits pattern:           H 1 0 ... 0
. x-1 bits pattern:         H 0 1 ... 1
-> x&(x-1) bits pattern:    H 0 0 ... 0     (clear the rightmost 1 bit)
*/
int fast_bitcount(unsigned x)
{
    int b = 0;
    while (x > 0)
    {
        x &= x - 1;
        b++;
    }
    return b;
}

/* helper to print result. */
void result(unsigned x, int expected)
{
    printf("Expected: %d. Actual: %d\n",
           expected, fast_bitcount(x));
}

int main()
{
    result(0b11110001, 5);
    result(0b1010, 2);
    // ... more cases
    return 0;
}