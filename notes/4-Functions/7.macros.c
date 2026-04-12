#define forever for (;;) // infinite loop

#define max(A, B) ((A) > (B) ? (A) : (B))
// x = max(p+q, r+s);
// -> x = ((p+q) > (r+s) ? (p+q) : (r+s));
// - serve any data type, unlike function

/* Pitfalls:
- argument is evaluated twice:
  . #define max(A, B) ((A) > (B) ? (A) : (B))
    max(i++, j++) -> WRONG

- parentheses to preserve evaluation order:
  . #define square(x) x * x
    square(z + 1) -> WRONG
*/

#undef getchar
int getchar(void);

// #param_name -> "param_name"
#define dprint(expr) printf(#expr " = %g\n", expr)
// dprint(x/y)
// -> printf("x/y" " = %g\n", x/y)
// <-> printf("x/y = %g\n", x/y)

// ## param_name -> actual_argument
#define paste(front, back) front ## back
// paste(name, 1) -> name1 (token)
