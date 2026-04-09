#include <stdio.h>

#define MAXLINE 1000 // maximum input line length

int get_line(char line[], int maxline);
void reverse(char s[], char reversed[]);

/* Reverse input a line at a time. */
int main()
{
    int len;                // current line length
    char line[MAXLINE];     // current input line
    char reversed[MAXLINE]; // current input line reversed
    while ((len = get_line(line, MAXLINE)) > 0)
    {
        reverse(line, reversed);
        printf("%s", reversed);
    }
    return 0;
}

/* Reverse s; assume 'reversed' is large enough */
void reverse(char s[], char reversed[])
{
    int i, j;

    // find end of s
    i = 0;
    while (s[i] != '\0')
        ++i;

    // fill 'reversed'
    reversed[i] = '\0';
    i = i - 1;
    if (s[i] == '\n')
    {
        reversed[i] = '\n';
        i = i - 1;
    }

    j = 0;
    while (i >= 0)
    {
        reversed[j] = s[i];
        ++j;
        --i;
    }
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
