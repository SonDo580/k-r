/*
Print the distinct words in input sorted into decreasing order of frequency.
Precede each word by its count.
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

struct tnode
{
    char *word; // points to the text
    int count;  // number of occurrences
    int nwords; // number of nodes (distinct words) in the subtree
    struct tnode *left;
    struct tnode *right;
};

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);

#define MAXWORD 100
int getword(char *, int);

struct tnode_arr
{
    struct tnode **a; // array of pointers to 'struct tnode'
    int capacity;
    int size;
};

struct tnode_arr *flatten_tree(struct tnode *root);
void tnode_arr_print(struct tnode_arr *);

void my_qsort(void *v[], int left, int right,
              int (*comp)(void *, void *));
int tnode_cmp(struct tnode *p, struct tnode *q);

int main()
{
    struct tnode *root;
    char word[MAXWORD];

    root = NULL;
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            root = addtree(root, word);

    struct tnode_arr *arr = flatten_tree(root);
    my_qsort((void **)arr->a, 0, arr->size - 1, (int (*)(void *, void *))tnode_cmp);
    tnode_arr_print(arr);

    return 0;
}

struct tnode *talloc(void);
char *my_strdup(char *);

/* add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w)
{
    // Note: this implementation can create unbalanced tree, which degrades performance
    // (worst case: words are already in sorted order)

    int cond;
    if (p == NULL)
    {                 // a new word has arrived
        p = talloc(); // make a new node
        p->word = my_strdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    }
    else if ((cond = strcmp(w, p->word)) == 0)
        (p->count)++;  // repeated word
    else if (cond < 0) // less than -> insert to left subtree
        p->left = addtree(p->left, w);
    else // greater than -> insert to right subtree
        p->right = addtree(p->right, w);

    // update number of distinct words
    p->nwords = p->count;
    if (p->left != NULL)
        p->nwords += p->left->nwords;
    if (p->right != NULL)
        p->nwords += p->right->nwords;

    return p;
}

/* in-order print of tree p */
void treeprint(struct tnode *p)
{
    if (p != NULL)
    {
        treeprint(p->left);
        printf("%4d %s\n", p->count, p->word);
        treeprint(p->right);
    }
}

/* flatten the tree into an array of pointers to 'struct tnode' */
struct tnode_arr *flatten_tree(struct tnode *root)
{
    if (root == NULL)
        return NULL;

    struct tnode_arr *arr = malloc(sizeof(struct tnode_arr));
    arr->capacity = root->nwords;
    arr->a = malloc(sizeof(struct tnode *) * arr->capacity);
    arr->size = 0;

    // Use preorder traversal to add nodes to array
    void preorder(struct tnode_arr *, struct tnode *);
    preorder(arr, root);

    return arr;
}

void preorder(struct tnode_arr *arr, struct tnode *p)
{
    if (p == NULL)
        return;
    (arr->a)[(arr->size)++] = p;
    preorder(arr, p->left);
    preorder(arr, p->right);
}

/* print array of tnodes */
void tnode_arr_print(struct tnode_arr *arr)
{
    if (arr != NULL)
        for (int i = 0; i < arr->size; i++)
            printf("%4d %s\n", (arr->a)[i]->count, (arr->a)[i]->word);
}

/* return -1 if p->count > q->count; 1 if p->count < q->count, 0 otherwise
(to sort in decreasing order of word frequency) */
int tnode_cmp(struct tnode *p, struct tnode *q)
{
    if (p->count > q->count)
        return -1;
    else if (p->count < q->count)
        return 1;
    else
        return 0;
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

/* get next word from input */
int getword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()))
        ;
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

/* quicksort with compare function 'comp' */
void my_qsort(void *v[], int left, int right,
              int (*comp)(void *, void *))
{
    int i, last;
    void swap(void *v[], int, int);

    // do nothing if array contains fewer than 2 elements
    if (left >= right)
        return;

    // move partition elem to left
    swap(v, left, (left + right) / 2);
    last = left;

    // partition
    for (i = left + 1; i <= right; i++)
        if ((*comp)(v[i], v[left]) < 0)
            swap(v, ++last, i);

    // restore partition elem
    swap(v, left, last);

    // sort the 2 partitions
    my_qsort(v, left, last - 1, comp);
    my_qsort(v, last + 1, right, comp);
}

/* interchange 2 elements */
void swap(void *v[], int i, int j)
{
    void *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
