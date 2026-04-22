#include <stdio.h>

#define MAXLEN 1000 // max length of any input line
char line[MAXLEN];

int my_getline(char *, int);

int main()
{
    int day, month, year;
    char monthname[20];

    while (my_getline(line, sizeof(line)) > 0)
    {
        if (sscanf(line, "%d %s %d", &day, monthname, &year) == 3)
            printf("valid: %s\n", line); // 25 Dec 1998 form
        else if (sscanf(line, "%d/%d/%d", &day, &month, &year) == 3)
            printf("valid: %s\n", line); // mm/dd/yy form
        else
            printf("invalid: %s\n", line);
    }
}

/* Read a line into s, return length */
int my_getline(char *s, int lim)
{
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}