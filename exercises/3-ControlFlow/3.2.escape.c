#include <stdio.h>

/*
copy t to s; convert \t and \n to visible escape sequences;
assume s is large enough;
*/
void escape(char t[], char s[])
{
    int i, j;
    j = 0;
    for (i = 0; t[i] != '\0'; i++)
    {
        switch (t[i])
        {
        case '\n':
            s[j++] = '\\';
            s[j++] = 'n';
            break;
        case '\t':
            s[j++] = '\\';
            s[j++] = 't';
            break;
        default:
            s[j++] = t[i];
            break;
        }
    }
    s[j] = '\0';
}

/*
copy t to s; convert to \t and \n from visible escape sequences;
assume s is large enough;
*/
void unescape(char t[], char s[])
{
    int i, j;
    j = 0;
    for (i = 0; t[i] != '\0'; i++)
    {
        switch (t[i])
        {
        case '\\':
            switch (t[i + 1])
            {
            case 'n':
                s[j++] = '\n';
                i++;
                break;
            case 't':
                s[j++] = '\t';
                i++;
                break;
            default:
                s[j++] = '\\';
                break;
            }
            break;
        default:
            s[j++] = t[i];
            break;
        }
    }
    s[j] = '\0';
}

int main()
{
    char t[] = "ab\tc\nd"; // length: 6 + 1
    char s[13];            // length: 6 * 2 + 1
    escape(t, s);
    printf("Expected: %s. Actual: %s\n",
           "ab\\tc\\nd", s);

    char t1[] = "ab\\tc\\nd"; // length: 8 + 1
    char s1[9];               // length: 8 + 1
    unescape(t, s);
    printf("Expected: %s. Actual: %s\n",
           "ab\tc\nd", s);

    return 0;
}