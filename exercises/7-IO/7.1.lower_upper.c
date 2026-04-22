/*
Converts upper case to lower or lower case to upper,
depending on the name it is invoked with (argv[0]).

=> How: compile to 2 executables (lower / upper)
*/

#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 1)
    {
        printf("Usage: ./7.1.lower.exe OR ./7.1.upper.exe");
        return 1;
    }

    int need_upper; // 0 if convert upper to lower, 1 if convert lower to upper
    if (strstr(*argv, "lower") != NULL)
        need_upper = 0;
    else if (strstr(*argv, "upper") != NULL)
        need_upper = 1;
    else
    {
        printf("Unexpected program name: %s\n", *argv);
        return 1;
    }

    int c;
    while ((c = getchar()) != EOF)
        printf("%c", need_upper ? toupper(c) : tolower(c));

    return 0;
}
