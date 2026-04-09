#include <stdio.h>

#define TAB_STOP 8

/* Replace blanks with the minimum number of tabs and blanks */
int main()
{
    int c, i;
    int line_len;         // current line length
    int spaces_run_start; // start index of current spaces run

    line_len = 0;
    spaces_run_start = -1;

    while ((c = getchar()) != EOF)
    {
        if (c == ' ')
        {
            if (spaces_run_start == -1)
                spaces_run_start = line_len;
            ++line_len;
        }
        else
        {
            // print normalized spaces
            // (don't increase length, already done above)
            if (spaces_run_start != -1)
            {
                // use as much tabs as possible, use spaces for the remaining
                int remaining_spaces = line_len % TAB_STOP;
                int tabs_end_idx = line_len - line_len % TAB_STOP - 1;
                int spaces_to_convert = tabs_end_idx - spaces_run_start + 1;
                int tabs = spaces_to_convert / TAB_STOP + (spaces_to_convert % TAB_STOP > 0);

                for (i = 0; i < tabs; ++i)
                    putchar('\t');
                for (i = 0; i < remaining_spaces; ++i)
                    putchar(' ');
            }
            spaces_run_start = -1; // reset

            // print current character
            putchar(c);
            if (c == '\n')
                line_len = 0;
            else if (c == '\t')
                line_len = line_len + (TAB_STOP - line_len % TAB_STOP);
            else
                ++line_len;
        }
    }

    return 0;
}