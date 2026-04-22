# Alignment

- Don't assume the size of the structure is the sum of the sizes of its members. Because of alignment requirements, there may be "holes" in a structure. Example:

```c
struct {
    char c; // 1 byte
    int i; // 4 byte
}
// the struct might require 8 bytes, not 5.
```

# Typedef

```c
typedef char *String;
int strcmp(String, String);

typedef int (*PFI)(char*, char*);
PFI strcmp;

typedef struct tnode *Treeptr;
typedef struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *left;
} Treenode;

Treeptr talloc(void) {
    return (Treeptr)malloc(sizeof(Treenode));
}
```

# Union

- Is a variable that can hold objects of different types.
- Large enough to hold the largest type.

```c
union u_tag {
    int ival;
    float fval;
    char *sval;
} u;
```

- Member access (same as `structure`):

```c
u.member
u->member
```

- Keep track of current type with extra variable:

```c
if (utype == INT)
    printf("%d\n", u.ival);
if (utype == FLOAT)
    printf("%f\n", u.fval);
if (utype == STRING)
    printf("%s\n", u.sval);
else
    printf("bad type %d in utype\n", utype);
```

- Nested:

```c
struct {
    char *name;
    int flags;
    int utype;
    union {
        int ival;
        float fval;
        char *sval;
    } u;
} symtab[NSYM];

// member ival
symtab[i].u.ival;

// first character of sval
*symtab[i].u.sval;
symtab[i].u.sval[0];
```

- Can only be initialized with a value of the type of its first member

```c
union u_tag {
    int ival;
    float fval;
    char *sval;
} u;
// => u can only be initialized with integer
```

# Bit-mask and Bit-field

## Bit-mask

- Use a set of 1-bit flags to encode information in a single `char` or `int`

```c
enum {
    KEYWORD = 01,   // 0001
    EXTERNAL = 02,  // 0010
    STATIC = 04     // 0100
}; // the masks must be powers of 2

flags |= EXTERNAL | STATIC; // turn on EXTERNAL and STATIC bits
flags &= ~(EXTERNAL | STATIC); // turn off EXTERNAL and STATIC bits
flags & (EXTERNAL | STATIC) == 0; // true if both bits are off
```

## Bit-field

- Is a set of adjacent bits within a single storage unit called a `word`

```c
struct {
    unsigned int is_keyword : 1;
    unsigned int is_extern  : 1;
    unsigned int is_static  : 1;
} flags;

/*
. flags is a variable that contains 1-bit fields
. number following the colon represents the field width in bits
. fields are declared 'unsigned int'
*/
```

- Fields are referenced as structure members, behave like small integers (participate in arithmetic expressions)

```c
flag.is_extern = flag.is_static = 1; // turn the bits on
flag.is_extern = flag.is_static = 0; // turn the bits off
flag.is_extern == 0 && flag.is_static == 0; // test
```
