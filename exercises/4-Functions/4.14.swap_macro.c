#include <stdio.h>

#define swap(t, a, b) \
    {                 \
        t temp = a;   \
        a = b;        \
        b = temp;     \
    }

int main()
{
    int i1 = 1, i2 = 2;
    printf("Before swap: i1 = %d, i2 = %d\n", i1, i2);
    swap(int, i1, i2);
    printf("After swap: i1 = %d, i2 = %d\n", i1, i2);

    double d1 = 1.0, d2 = 2.0;
    printf("Before swap: d1 = %f, d2 = %f\n", d1, d2);
    swap(double, d1, d2);
    printf("After swap: d1 = %f, d2 = %f\n", d1, d2);
}