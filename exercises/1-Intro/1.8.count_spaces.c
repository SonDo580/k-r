#include <stdio.h>

int main()
{
    int c, n;
    n = 0;
    while ((c = getchar()) != EOF)
        if (c == ' ' || c == '\t' || c == '\n')
            ++n;
    printf("%d\n", n);
}