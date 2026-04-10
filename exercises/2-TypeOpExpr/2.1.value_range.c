#include <limits.h>
#include <float.h>
#include <stdio.h>

/* determine the ranges of char, short, int, and long variables,
both signed and unsigned */
int main()
{
    printf("===== From standard headers ===== ");
    printf("unsigned char: %d -> %d\n\n", 0, UCHAR_MAX);
    printf("signed char: %d -> %d\n", CHAR_MIN, CHAR_MAX);
    printf("unsigned short: %d -> %d\n", 0, USHRT_MAX);
    printf("signed short: %d -> %d\n", SHRT_MIN, SHRT_MAX);
    printf("unsigned int: %u -> %u\n", 0, UINT_MAX);
    printf("signed int: %d -> %d\n", INT_MIN, INT_MAX);
    printf("unsigned long: %lu -> %lu\n", 0L, ULONG_MAX);
    printf("signed long: %ld -> %ld\n", LONG_MIN, LONG_MAX);
}
