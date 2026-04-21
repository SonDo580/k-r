int strlen(char *s)
{
    int n;
    for (n = 0; *s != '\0'; s++)
        n++;
    return n;
    /*
    - s++ has no effect on the string, just increment strlen's private copy of the pointer
    - these all work:
    strlen("hello, world"); // string constant
    strlen(array); // char array[100];
    strlen(ptr); // char *ptr;
    */
}

/* another version */
int strlen(char *s)
{
    char *p = s;
    while (*p != '\0')
        p++;
    return p - s;
}