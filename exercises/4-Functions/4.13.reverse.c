#include <string.h>
#include <stdio.h>

#define MAXLEN 100 // max string length

/* helper: swap s[i] and s[j] */
void swap(char s[], int i, int j)
{
    char temp;
    temp = s[i];
    s[i] = s[j];
    s[j] = temp;
}

/* reverse s in place */
void reverse(char s[], int i)
{
    /* a pretty inefficient implementation
    - reverse s[i+1..end]
    - push s[i] to the end through swapping
    */

    if (s[i] == '\0')
        return;

    reverse(s, i + 1);

    while (s[i + 1] != '\0')
    {
        swap(s, i, i + 1);
        i++;
    }
}

/* helper to print result */
void result(char s[], char expected[])
{
    char input[MAXLEN];
    strcpy(input, s);
    reverse(s, 0);
    if (strcmp(expected, s) != 0)
        printf("Input: %s. Expected: %s. Actual: %s\n",
               input, expected, s);
}

int main()
{
    char s1[MAXLEN] = "abcd";
    result(s1, "dcba");

    char s2[MAXLEN] = "abcde";
    result(s2, "edcba");
}