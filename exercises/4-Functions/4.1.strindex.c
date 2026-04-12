#include <stdio.h>

/* return the rightmost index of t in s, -1 if none */
int strindex(char s[], char t[])
{
    // probably not an efficient implementation

    int i, j, k, idx;
    idx = -1;
    for (i = 0; s[i] != '\0'; i++)
    {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
            ;
        if (k > 0 && t[k] == '\0')
            idx = i;
    }
    return idx;
}

/* helper to print result */
void result(char s[], char t[], int expected)
{
    int idx = strindex(s, t);
    if (idx != expected)
        printf("s = %s. t = %s. Expected: %d. Actual: %d\n",
               s, t, expected, idx);
}

int main()
{
    result("abcdcd", "", -1);
    result("abcdcd", "de", -1);
    result("abcdcd", "cd", 4);
}