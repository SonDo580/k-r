#include <stdio.h>

#define MAXCOLS 10
#define TABSTOP 8

/* Fold long input lines into multiple shorted lines after
the last non-blank characters that occurs before the n-th column. */
int main()
{
    int c, i;
    int line_cols; // number of columns of current line
    int spaces_run_start;

    line_cols = 0;
    spaces_run_start = -1;

    while ((c = getchar()) != EOF)
    {
        if (c == '\t' || c == ' ')
        {
            if (spaces_run_start == -1)
                spaces_run_start = line_cols;

            if (c == '\t')
                line_cols = line_cols + (TABSTOP - line_cols % TABSTOP);
            else
                ++line_cols;
        }
        else if (c == '\n')
        {
            // ignore trailing spaces

            putchar('\n');
            line_cols = 0;
        }
        else
        {
            // print pending spaces if adding current character doesn't exceed limit
            if (spaces_run_start != -1 && line_cols < MAXCOLS)
                for (i = spaces_run_start; i < line_cols; ++i)
                    putchar(' ');
            spaces_run_start = -1; // reset

            // move to a new line if needed
            if (line_cols >= MAXCOLS)
            {
                putchar('\n');
                line_cols = 0;
            }

            // print current character
            putchar(c);
            ++line_cols;
        }
    }
}
