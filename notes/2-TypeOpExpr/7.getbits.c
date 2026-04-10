/* get n bits to the right from position p */
unsigned getbits(unsigned x, int p, int n)
{
    // x >> (p + 1 - n) moves the desired field to the right end
    // ~0 is all 1-bits
    // ~0 << n places zeros at the rightmost n bits
    // ~(~0 << n) makes a mask with ones in the rightmost n bits
    return (x >> (p + 1 - n)) & ~(~0 << n);
}