#include <stdio.h>

/*
convert a string of hexadecimal digits (including optional 0x and 0X)
to integer; allowable digits: 0-9, a-f, A-F
*/
int htoi(char s[])
{
    int n = 0;

    for (int i = 0; s[i] != '\0'; ++i)
    {
        // Skip 0x and 0X prefix
        if (s[i] == '0' && (s[i + 1] == 'x' || s[i + 1] == 'X'))
        {
            ++i;
            continue;
        }

        if (s[i] >= '0' && s[i] <= '9')
            n = 16 * n + s[i] - '0';
        else if (s[i] >= 'a' && s[i] <= 'f')
            n = 16 * n + s[i] - 'a' + 10;
        else if (s[i] >= 'A' && s[i] <= 'F')
            n = 16 * n + s[i] - 'A' + 10;
        else
            break;
    }
    return n;
}

/* helper to print conversion result. */
void result(char s[], int expected)
{
    printf("Expected: %d. Actual: %d\n",
           expected, htoi(s));
}

int main()
{
    result("0f", 15);
    result("0D", 13);
    result("1A", 26);
    result("1b", 27);
    result("0x1C", 28);
    result("0X1e", 30);
    // ... more cases
}