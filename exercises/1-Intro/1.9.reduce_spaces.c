#include <stdio.h>

/*
Copy input to output,
replace string of one or multiple blanks by a single blank
*/
int main()
{
    int c, last_was_space;
    last_was_space = 0;
    while ((c = getchar()) != EOF)
    {
        if (c == ' ')
            if (last_was_space)
                continue;
            else
            {
                putchar(c);
                last_was_space = 1;
            }
        else
        {
            putchar(c);
            last_was_space = 0;
        }
    }
}