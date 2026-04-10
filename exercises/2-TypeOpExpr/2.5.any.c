#include <stdio.h>

/* helper: check if character c is in string s */
int in(char s[], char c)
{
    for (int i = 0; s[i] != '\0'; i++)
        if (s[i] == c)
            return 1;
    return 0;
}

/* Return the first location in s1 where any character in s2 occurs,
or -1 if s1 contains no characters from s2 */
int any(char s1[], char s2[])
{
    for (int i = 0; s1[i] != '\0'; i++)
        if (in(s2, s1[i]))
            return i;
    return -1;
}

/* helper to print result. */
void result(char s1[], char s2[], int expected)
{
    printf("Expected: %d. Actual: %d\n",
           expected, any(s1, s2));
}

int main()
{
    result("abc", "bef", 1);
    result("abc", "lab", 0);
    result("abc", "cow", 2);
    result("abc", "def", -1);
    // ... more cases
    return 0;
}