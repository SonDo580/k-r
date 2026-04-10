#include <stdio.h>

/* Flip n bits of x begin at p. */
unsigned invert(unsigned x, int p, int n)
{
    // - flip bit a <-> a XOR 1
    //   -> we need a mask of form 0..01..10..0 where
    //      the run of 1's is from p to p-n+1
    // - produce mask:
    //   . ~0 creates a mask of all 1
    //   . ~0 << n places 0 at the rightmost n bits of the mask
    //   . ~(~0 << n) creates a mask with ones at the rightmost n bits
    //   . (~(~0 << n)) << (p-n+1) shift the mask to the desired position
    // - result: x ^ mask

    unsigned mask = (~(~0 << n)) << (p - n + 1);
    return x ^ mask;
}

/* helper to print result. */
void result(unsigned x, int p, int n, unsigned expected)
{
    printf("Expected: %d. Actual: %d\n",
           expected, invert(x, p, n));
}

int main()
{
    result(0b11110001, 3, 4, 0b11111110);
    result(0b1010, 7, 3, 0b11101010);
    // ... more cases
    return 0;
}