/*
Print list of all words in a document.
For each word, print a list of line numbers on which it occurs.
Remove noise words like "the", "a", "an", "and", ...

(Note: currently skip handling malloc/realloc returning NULL)
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

char *noise_words[] = {
    "a", "about", "all", "am", "an", "and", "any", "are", "as", "at",
    "be", "been", "but", "by",
    "can", "could",
    "did", "do", "does",
    "for", "from",
    "had", "has", "have", "he", "her", "his",
    "i", "if", "in", "is", "it",
    "me", "my",
    "no", "not",
    "of", "on", "or",
    "she", "so",
    "the", "their", "them", "they", "this", "to",
    "up",
    "was", "we", "were", "what", "when", "which", "who", "will", "with",
    "you", "your"
    // ... and so on
}; // sorted in increasing order

#define N_NOISE (sizeof(noise_words) / sizeof(char *))
int is_noise(char *w);

struct DynamicIntArray
{
    int *container;
    int capacity;
    int size;
};
#define INITCAP 1 // initial capacity of a DynamicArray

struct DynamicIntArray *arr_init(void);
void arr_push(struct DynamicIntArray *, int);
void arr_print(struct DynamicIntArray *);

struct tnode
{
    char *word;                    // points to the text
    struct DynamicIntArray *lines; // the lines on which word occurs
    struct tnode *left;
    struct tnode *right;
};

struct tnode *addtree(struct tnode *p, char *w, int line);
void treeprint(struct tnode *p);

int line; // current line in input
#define MAXWORD 100
int getword(char *, int);

int main()
{
    extern int line;
    struct tnode *root;
    char word[MAXWORD];

    line = 1;
    root = NULL;
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]) && !is_noise(word))
            root = addtree(root, word, line);
    treeprint(root);
    return 0;
}

struct tnode *talloc(void);
char *my_strdup(char *);

/* add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w, int line)
{
    // Note: this implementation can create unbalanced tree, which degrades performance
    // (worst case: words are already in sorted order)

    int cond;
    if (p == NULL)
    {                 // a new word has arrived
        p = talloc(); // make a new node
        p->word = my_strdup(w);
        p->left = p->right = NULL;

        p->lines = arr_init();
        arr_push(p->lines, line);
    }
    else if ((cond = strcmp(w, p->word)) == 0)
    { // repeated word
        // skip if still on the same line
        if ((p->lines->size == 0) ||
            ((p->lines->container)[p->lines->size - 1] != line))
        {
            arr_push(p->lines, line);
        }
    }
    else if (cond < 0) // less than -> insert to left subtree
        p->left = addtree(p->left, w, line);
    else // greater than -> insert to right subtree
        p->right = addtree(p->right, w, line);
    return p;
}

void treeprint(struct tnode *p)
{
    if (p != NULL)
    {
        treeprint(p->left);

        printf("%s: ", p->word);
        arr_print(p->lines);
        printf("\n");

        treeprint(p->right);
    }
}

/* make a tnode */
struct tnode *talloc(void)
{
    return (struct tnode *)malloc(sizeof(struct tnode));
}

/* make a duplicate of s */
char *my_strdup(char *s)
{
    char *p;
    p = (char *)malloc(strlen(s) + 1); // +1 for '\0'
    if (p != NULL)
        strcpy(p, s);
    return p;
}

int binsearch(char *w, char *words[], int n);
int fold_strcmp(char *s1, char *s2);

/* return 1 if w is in noise_words, 0 otherwise */
int is_noise(char *w)
{
    return binsearch(w, noise_words, N_NOISE) >= 0;
}

/* find index of w in words, ignore case; return -1 if not found */
int binsearch(char *w, char *words[], int n)
{
    int cond;
    int low, mid, high;

    low = 0;
    high = n - 1;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if ((cond = fold_strcmp(w, words[mid])) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}

/* compare s1 and s2 lexicographically, ignore case */
int fold_strcmp(char *s1, char *s2)
{
    int i;
    for (i = 0; tolower(s1[i]) == tolower(s2[i]); i++)
        if (s1[i] == '\0')
            return 0;
    return tolower(s1[i]) - tolower(s2[i]);
}

struct DynamicIntArray *arr_init(void)
{
    struct DynamicIntArray *arr = malloc(sizeof(struct DynamicIntArray));
    arr->size = 0;
    arr->capacity = INITCAP;
    arr->container = malloc(sizeof(int) * arr->capacity);
    return arr;
}

void arr_push(struct DynamicIntArray *arr, int val)
{
    // allocate more memory if needed
    if (arr->size == arr->capacity)
    {
        arr->capacity *= 2;
        arr->container = realloc(arr->container, sizeof(int) * arr->capacity);
    }
    arr->container[(arr->size)++] = val;
}

void arr_print(struct DynamicIntArray *arr)
{
    printf("[");
    for (int i = 0; i < arr->size; i++)
        printf(i == arr->size - 1 ? "%d" : "%d ", (arr->container)[i]);
    printf("]");
}

/* get next word from input */
int getword(char *word, int lim)
{
    extern int line;
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()))
        if (c == '\n')
            line++;

    if (c != EOF)
        *w++ = c;
    if (!isalpha(c))
    {
        *w = '\0';
        return c;
    }
    for (; --lim > 0; w++)
        if (!isalnum(*w = getch()))
        {
            ungetch(*w);
            break;
        }
    *w = '\0';
    return word[0];
}

#define BUFSIZE 100

char buf[BUFSIZE]; // buffer for ungetch
int bufp = 0;      // next free position in buf

/* get a (possibly pushed-back) character */
int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* push character back on input */
void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
