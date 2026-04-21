/*
A rudimentary storage allocator with 2 routines:
- alloc(n) returns a pointer to n consecutive character positions.
- afree(p) releases the storage thus acquired.

Limitations:
- The calls to 'afree' must be made in opposite order to the calls to 'alloc'
  (the storage managed is a stack).
*/

#define ALLOCSIZE 10000 // available space

static char allocbuf[ALLOCSIZE]; // storage for alloc
static char *allocp = allocbuf;  // next free position

/* returns pointer to n characters */
char *alloc(int n)
{
    if (allocbuf + ALLOCSIZE - allocp >= n)
    { // it fits (allocp would be at most one beyond the end of allocbuf)
        allocp += n;
        return allocp - n; // old p
    }
    else
        // not enough room
        return 0; // C guarantees that 0 is never a valid address for data
                  // use NULL (from <stdio.h>) for better clarity
}

/* free storage pointed to by p */
void afree(char *p)
{
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
        allocp = p;
}
