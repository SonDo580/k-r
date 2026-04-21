#include <stdio.h>

/*
concatenate at most n characters of t to end of s;
terminate s with '\0'
*/
void my_strncat(char *s, char *t, int n)
{
    // find end of s ('\0')
    while (*s)
        s++;

    // append t
    while (n-- > 0 && (*(s++) = *(t++)) != '\0')
        ;

    // end s with '\0' (redundant if t has been "exhausted")
    *s = '\0';
};

int main()
{
    char *t = "bc";              // size = 3
    for (int i = 0; i <= 4; i++) // try exceeding t size
    {
        char s[100] = "a";
        my_strncat(s, t, i);
        printf("s: %s\n", s);
    }
}