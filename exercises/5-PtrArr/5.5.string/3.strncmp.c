#include <stdio.h>

/*
compare at most n characters of s and t;
return <0 if s<t, 0 if s==t, >0 if s>t
 */
int my_strncmp(char *s, char *t, int n)
{
    for (; n > 0 && *s == *t; n--, s++, t++)
        if (*s == '\0')
            return 0;
    return (n == 0) ? 0 : (*s - *t);
}

/* helper to print result */
void result(char *s, char *t, int n, int expected)
{
    int result = my_strncmp(s, t, n);
    int normalized = (result == 0) ? 0 : ((result > 0) ? 1 : -1);
    if (normalized != expected)
        printf("s=%s, t=%s, n=%d. Expected: %d. Actual: %d\n",
               s, t, n, expected, normalized);
}

int main()
{
    result("abc", "ab", 2, 0);
    result("abc", "ab", 3, 1);
    result("ab", "abc", 1, 0);
    result("ab", "abc", 3, -1);
    result("abc", "def", 0, 0);
    // ...
}