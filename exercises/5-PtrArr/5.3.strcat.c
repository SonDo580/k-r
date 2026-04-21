#include <stdio.h>

/* pointer version: concatenate t to end of s; assume s is big enough */
void my_strcat(char *s, char *t)
{
    // find end of s
    while (*(s++))
        ;
    s--; // move back to '\0'

    // append t
    while (*(s++) = *(t++))
        ;
};

int main()
{
    char s[100] = "a";
    char *t = "bc";
    my_strcat(s, t);
    printf("s: %s\n", s);
}