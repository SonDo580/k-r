/*
Write a function 'undef' that will remove a name and definition
from the table maintained by 'lookup' and 'install'
*/

#include <stdlib.h>

/* table entry */
struct nlist
{
    struct nlist *next; // next entry in the chain
    char *name;         // defined name
    char *defn;         // replacement text
};

#define HASHSIZE 101 // number of buckets: use prime number

static struct nlist *hashtab[HASHSIZE]; // hash table

/* form hash value for string s */
unsigned hash(char *s)
{
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

/* look for s in hashtab */
struct nlist *lookup(char *s)
{
    struct nlist *np;
    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np; // found
    return NULL;       // not found
}

char *strdup(char *);

/* put (name, defn) in hash tab */
struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL)
    { // not found
        np = (struct nlist *)malloc(sizeof *np);
        if (np == NULL || (np->name = strdup(name) == NULL))
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    }
    else // already there
    {
        free(np->defn); // free previous defn
        if ((np->defn = strdup(defn)) == NULL)
            return NULL;
    }
    return np;
}

/* make a duplicate of s */
char *strdup(char *s)
{
    char *p;
    p = (char *)malloc(strlen(s) + 1); // +1 for '\0'
    if (p != NULL)
        strcpy(p, s);
    return p;
}

/* remove a name and definition from symbol table */
void undef(char *name)
{
    struct nlist *np, *prev_np;
    unsigned hashval;

    prev_np = np = NULL;
    hashval = hash(name);
    for (np = hashtab[hashval]; np != NULL; prev_np = np, np = np->next)
        if (strcmp(name, np->name) == 0)
            break;

    if (np == NULL) // not found
        return;

    if (prev_np == NULL) // np is head of linked-list
        hashtab[hashval] = np->next;
    else // skip over np
        prev_np->next = np->next;

    free(np);
}