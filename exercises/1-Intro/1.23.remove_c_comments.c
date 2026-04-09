#include <stdio.h>

/* Remove all comments from a (valid) C program */
int main()
{
    int c;

    while ((c = getchar()) != EOF)
    {
        if (c == '/')
        {
            c = getchar();
            if (c == '/')
                // ignore inline comment
                while ((c = getchar()) != '\n' && c != EOF)
                    ;
            else if (c == '*')
            {
                // ignore block comment
                while (((c = getchar()) != '*' && c != EOF) ||
                       ((c = getchar()) != '/' && c != EOF))
                    ;
                if (c == EOF)
                    printf("\n !!! Block comment is not closed !!!\n");
            }
            else
            {
                putchar('/');
                putchar(c);
            }
        }
        else
            putchar(c);
    }
}
