# Valid pointer operations

- assignment of pointers of the same type
- adding or subtracting a pointer and an integer
- subtracting or comparing 2 pointers to member of the same array _(exception: the address of the first element past the end of the array can be used)_
- assigning and comparing to 0.

# 2-D array vs pointer

## 2-D array

```c
int a[10][20];
```

- `10*20` int-sized locations are set aside
- `20*row + col` is used to find `a[row][col]`

## array of pointers

```c
int *b[10];
```

- `b[3][4]` is syntactically legal reference to an int
- **initialization:** the definition only allocates 10 pointers but doesn't initialize them (must be done explicitly, either statically or with code)
- **take more space:** if each element of b is a 20-element array, then there will be 200 ints set aside, plus 10 cells for the pointers
- **advantage:** rows may be of different lengths
- **frequently used:** store character strings of diverse lengths

## memory layout

```c
char *name[] = { "Illegal month", "Jan"};
/*
name:
.---> [Illegal month\0]
.---> [Jan\0]
*/

char aname[][15] = { "Illegal month", "Jan" };
/*
[Illegal month\0 Jan\0           ]
 0               15
*/
```

# Generic pointer

- Any pointer can be cast to `void *` and back again without loss of information.

# Complicated declaration

```c
int *f();       // f: function returning pointer to int
int (*pf)();    // *pf: pointer to function returning int

int (*get_pf(int))(char); // get_pf: function accepting int and returning pointer to (function accepting char and retuning int)
```
