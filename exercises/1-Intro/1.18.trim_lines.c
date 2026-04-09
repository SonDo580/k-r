#include <stdio.h>

#define MAXLINE 1000 // maximum input line length

int get_line(char line[], int maxline);
int trim_line(char s[], char trimmed[]);

/* Remove trailing blanks and tabs from each line of input.
Delete entirely blank lines. */
int main()
{
    int len;            // current line length
    char line[MAXLINE]; // current input line
    char trimmed[MAXLINE];
    while ((len = get_line(line, MAXLINE)) > 0)
    {
        len = trim_line(line, trimmed);
        if (len > 0)
            printf("%s", trimmed);
    }
    return 0;
}

/* Remove trailing blanks and tabs from s;
assume 'trimmed' is large enough; return final length */
int trim_line(char s[], char trimmed[])
{
    int trimmed_len, i;
    int last_is_spaces;    // previous chars is a run of spaces
    int last_spaces_start; // start index of previous run of spaces

    last_is_spaces = 0;
    last_spaces_start = -1;

    // skip spaces at the start
    i = 0;
    while (s[i] == ' ' || s[i] == '\t')
        ++i;

    trimmed_len = 0;
    while (s[i] != '\n' && s[i] != '\0')
    {
        if (s[i] == ' ' || s[i] == '\t')
        {
            last_is_spaces = 1;
            if (last_spaces_start == -1)
                last_spaces_start = i;
        }
        else
        {
            last_is_spaces = 0;
            last_spaces_start = -1;
        }

        trimmed[trimmed_len] = s[i];
        ++trimmed_len;
        ++i;
    }

    // remove spaces at the end
    if (last_is_spaces == 1)
        trimmed_len = last_spaces_start;

    // append '\n' (if exists) and '\0'
    if (s[i] == '\n')
    {
        trimmed[trimmed_len] = s[i];
        ++trimmed_len;
    }
    trimmed[trimmed_len] = '\0';
    return trimmed_len;
}

/* Read a line into s, return length */
int get_line(char s[], int lim)
{
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n')
    {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}
