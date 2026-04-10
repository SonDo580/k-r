#include <stdio.h>

/* Return x with n bits from p set to the rightmost n bits of y */
unsigned setbits(unsigned x, int p, int n, unsigned y)
{
    // - create a mask with the rightmost n bits of y
    //   from p to p-n+1, 0 everywhere else:
    //   . ~0 creates a mask of all 1
    //   . ~0 << n places 0 at the rightmost n bits of the mask
    //   . ~(~0 << n) creates a mask with ones at the rightmost n bits
    //   . ~(~0 << n) & y keeps the rightmost n bits of y
    //   . (~(~0 << n) & y) << (p-n+1) shifts the mask to desired position
    //
    // - clear bits p to p-n+1 of x
    //   . from ~(~0 << n): a mask with ones at the rightmost n bits
    //   . ~(~0 << n) << (p-n+1) shifts the mask to desired position
    //   . ~(~(~0 << n) << (p-n+1)) clear bits p to p-n+1, set other bits to 1
    //   . ~(~(~0 << n) << (p-n+1)) & x clear bits p to p-n+1 of x

    unsigned mask1 = (~(~0 << n) & y) << (p - n + 1);
    unsigned mask2 = ~(~(~0 << n) << (p - n + 1)) & x;
    return mask1 | mask2;
}

/* helper to print result. */
void result(unsigned x, int p, int n, unsigned y, int expected)
{
    printf("Expected: %d. Actual: %d\n",
           expected, setbits(x, p, n, y));
}

int main()
{
    result(0b11110001, 3, 4, 0b00001111, 0b11111111);
    result(0b1111, 7, 3, 0b10101010, 0b01001111);
    // ... more cases
    return 0;
}