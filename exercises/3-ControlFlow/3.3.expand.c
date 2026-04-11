#include <stdio.h>
#include <string.h>

/* expand shorthand notation in s1 to complete list in s2;
assume s2 is large enough
. example: a-z -> abc...xyz
. allow letters of either case and digits
*/
void expand(char s1[], char s2[])
{
    int i, j;
    i = j = 0;
    while (s1[i] != '\0')
    {
        if (s1[i] != '-' || i == 0)
        {
            s2[j++] = s1[i++];
            continue;
        }

        if (!(s1[i + 1] >= s1[i - 1] &&
              ((s1[i - 1] >= '0' && s1[i + 1] <= '9') ||
               (s1[i - 1] >= 'a' && s1[i + 1] <= 'z') ||
               (s1[i - 1] >= 'A' && s1[i + 1] <= 'Z'))))
        {
            s2[j++] = s1[i++];
            continue;
        }

        // . example: "...a-a..." -> skip "-a" entirely
        // . example: "...1-4..." -> expand to 1234
        for (int k = s1[i - 1] + 1; k <= s1[i + 1]; k++)
        {
            s2[j++] = k;
        }
        i += 2; // move pass the -<end> part
    }

    s2[j] = '\0';
}

/* helper to print result */
void result(char s1[], char s2[], char expected[])
{
    expand(s1, s2);
    if (strcmp(expected, s2) != 0)
    {
        printf("Input: %s. Expected: %s. Actual: %s\n",
               s1, expected, s2);
    }
}

int main()
{
    char s2[1000];

    result("_a-f_", s2, "_abcdef_");
    result("-a-f_", s2, "-abcdef_");
    result("_a-f-", s2, "_abcdef-");
    result("a-b-d", s2, "abcd");
    result("a--c-e", s2, "a--cde");
    result("a-a", s2, "a");
    result("z-a", s2, "z-a");
    result("b-D", s2, "b-D");
    result("B-D", s2, "BCD");
    result("B-BA", s2, "BA");
    result("Z-A", s2, "Z-A");
    result("0-9", s2, "0123456789");
    result("a-0-4", s2, "a-01234");
    result("a-d0-3", s2, "abcd0123");
    result("a-d0-35-7", s2, "abcd0123567");
    result("a-d0-3-7", s2, "abcd01234567");
    result("10-3-3", s2, "10123");
    result("9-3-3", s2, "9-3");
    result("_-+", s2, "_-+");

    return 0;
}