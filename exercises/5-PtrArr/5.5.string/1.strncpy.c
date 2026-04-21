#include <stdio.h>

/*
copy at most n characters from t to s, including '\0';
pad with '\0' if t has fewer than n characters
*/
void *my_strncpy(char *s, char *t, int n)
{
    while (n-- > 0 && (*(s++) = *(t++)) != '\0')
        ;
    while (n-- > 0 && ((*(s++) = '\0')))
        ;
}

int main()
{
    char *t = "bc";              // size = 3
    for (int i = 0; i <= 4; i++) // try exceeding t size
    {
        char s[100] = "a";
        my_strncpy(s, t, i);

        printf("n=%d, s: ", i);
        for (int j = 0; j <= i; j++)
            if (s[j] == '\0')
                printf("\\0 ");
            else
                printf("%c ", s[j]);
        printf("\n");
    }
}