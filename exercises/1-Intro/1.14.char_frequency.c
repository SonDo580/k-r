#include <stdio.h>

#define ALPHABET_LEN 26

/* Print histogram of character frequencies in input. */
int main()
{
    int c, i, j;
    int char_freq[ALPHABET_LEN];

    for (i = 0; i < ALPHABET_LEN; ++i)
        char_freq[i] = 0;

    while ((c = getchar()) != EOF)
    {
        if (c >= 'a' && c <= 'z')
            ++char_freq[c - 'a'];
        else if (c >= 'A' && c <= 'Z')
            ++char_freq[c - 'A'];
    }

    // Print histogram (horizontally)
    printf("\n===== Character frequencies =====\n");
    for (i = 0; i < ALPHABET_LEN; ++i)
    {
        printf("%c", i + 'a');
        printf(" | ");
        for (j = 0; j < char_freq[i]; ++j)
            printf("#");
        printf("\n");
    }
    printf("\n");
}