#include <stdio.h>

#define IN 1       // inside word
#define OUT 0      // outside word
#define MAX_LEN 10 // max word length

/* Print histogram of lengths of words in input. */
int main()
{
    int c, state, capacity, curr_len, has_word;
    int i, j;

    // length_freq[MAX_LEN+1] is for length > MAX_LEN
    // length_freq[0] is not used
    int length_freq[MAX_LEN + 2];

    state = OUT;
    has_word = 0;
    curr_len = 0;
    for (i = 0; i < MAX_LEN + 2; ++i)
        length_freq[i] = 0;

    while ((c = getchar()) != EOF)
    {
        if (c == ' ' || c == '\t' || c == '\n')
        {
            state = OUT;
            if (curr_len > MAX_LEN)
                ++length_freq[MAX_LEN + 1];
            else if (curr_len > 0)
                ++length_freq[curr_len];
            curr_len = 0;
        }
        else if (state == OUT)
        {
            state = IN;
            ++curr_len;
            if (has_word == 0)
                has_word = 1;
        }
        else
            ++curr_len;
    }

    if (has_word == 0)
    {
        printf("No words detected\n");
        return 0;
    }

    // Print histogram (horizontally)
    printf("\n===== Word length histogram =====\n");
    for (i = 0; i < MAX_LEN + 2; ++i)
    {
        if (length_freq[i] == 0)
            continue;

        if (i == MAX_LEN + 1)
            printf(">%2d", MAX_LEN);
        else
            printf("%3d", i);

        printf(" | ");
        for (j = 0; j < length_freq[i]; ++j)
            printf("#");
        printf("\n");
    }
    printf("\n");
}