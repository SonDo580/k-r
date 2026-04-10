#include <stdio.h>

/* helper:  check if character c is in string s */
int in(char s[], char c)
{
    for (int i = 0; s[i] != '\0'; i++)
        if (s[i] == c)
            return 1;
    return 0;
}

/* delete each character in s1 that matches any character in s2 */
void squeeze(char s1[], char s2[])
{
    int i, j;
    i = j = 0;
    while (s1[i] != '\0')
    {
        if (!in(s2, s1[i]))
            s1[j++] = s1[i];
        i++;
    }
    s1[j] = '\0';
}

/* helper to print result. */
void result(char s1[], char s2[], char expected[])
{
    squeeze(s1, s2);
    printf("Expected: %s. Actual: %s\n",
           expected, s1);
}

int main()
{
    // result("dabceab", "cde", "abab");
    // -> string literals are read-only,
    //    attempting to modify results in memory error

    char s1[] = "dabceab"; // writable
    result(s1, "cde", "abab");

    return 0;
}