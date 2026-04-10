/* count 1 bits from x */
int bitcount(unsigned x)
{
    // declare x as unsigned for logical right shift
    int b;
    for (b = 0; x != 0; x >>= 1)
        if (x & 01)
            b++;
    return b;
}