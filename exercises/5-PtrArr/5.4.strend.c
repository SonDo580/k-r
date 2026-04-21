#include <stdio.h>

/* return 1 if t occurs at the end of s, 0 otherwise. */
int my_strend(char *s, char *t)
{
    // record start of s and t
    char *s_start = s;
    char *t_start = t;

    // find end of s and t
    while (*s)
        s++;
    while (*t)
        t++;

    // t is longer than s -> t cannot be at the end of s
    if (t - t_start > s - s_start)
        return 0;

    // go back to the first character of t
    // return 1 if all characters match, 0 otherwise
    while (t > t_start)
        if (*(t--) != *(s--))
            return 0;
    return *t == *s;
};

/* helper to print result */
void result(char *s, char *t, int expected)
{
    int result = my_strend(s, t);
    if (result != expected)
        printf("s: %s, t: %s. Expected: %d. Actual: %d\n",
               s, t, expected, result);
}

int main()
{
    result("abc", "bc", 1);
    result("abc", "abc", 1);
    result("abc", "b", 0);
    result("abc", "abcd", 0);
    result("", "a", 0);
    result("a", "", 1);
}