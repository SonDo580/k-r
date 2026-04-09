#include <stdio.h>

/* Convert celsius to fahr */
int main()
{
    float fahr, celsius;
    float lower, upper, step;

    lower = -20;
    upper = 150;
    step = 20;

    celsius = lower;
    while (celsius <= upper)
    {
        fahr = (9.0 / 5.0) * (celsius + 32.0);
        printf("%3.0f %6.1f\n", celsius, fahr);
        celsius += step;
    }
}
