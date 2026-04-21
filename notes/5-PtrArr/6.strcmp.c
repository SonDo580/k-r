/* return <0 if s<t, 0 if s==t, >0 if s>t */
int strcmp(char *s, char *t)
{
    // subtracting characters at the first position where s and t disagree
    int i;
    for (i = 0; s[i] == t[i]; i++)
        if (s[i] == '\0')
            return 0;
    return s[i] - t[i];
}

/* pointer version */
int strcmp(char *s, char *t)
{
    for (; *s == *t; s++, t++)
        if (*s == '\0')
            return 0;
    return *s - *t;
}