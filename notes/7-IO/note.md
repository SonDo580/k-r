# Standard input and output

```bash
# standard input: keyboard by default
# input redirection: read characters from infile
prog <infile

# standard output: screen by default
# output redirection: write standard output of prog to outfile
prog >outfile

# pipe: put standard output of prog into standard input of next_prog
prog | next_prog
```

# Formatted output

`printf`

# Variable argument list

See `minprintf.c`

# Formatted output

`scanf`, `sscanf`

# File access

- `FILE`, `fopen`, `getc`, `putc`
- When a C program is started, the OS environment opens 3 files and provides pointers to them: `stdin`, `stdout`, `stderr`
- `getchar`, `putchar`:

```c
#define getchar() getc(stdin)
#define putchar(c) putc((c), stdout)
```

- `fprintf`, `fscanf`
- `fclose`:
  - free the file pointer for another file
  - flush the buffer in which `putc` is collecting input
  - called automatically for each open file when program terminates normally.
  - good practice to free the file pointer when no longer needed, since OS limits the number of files that a program can open simultaneously.

# Error handling

- `stderr`
- `exit`:
  - terminate program execution.
  - call `fclose` for each open output file, to flush any buffered output.
  - argument of `exit` is available to whatever process called current one.
- `ferror(fp)`: return non-zero if an error occurred on the file
- `feof(fp)`: return non-zero if end of file occurred on the file

# Line input and output

- `fgets`, `fputs`
- `gets`, `puts`: similar, but operate on `stdin` and `stdout`

# Miscellaneous

- `system(char *s)`: execute the command contained in s, then resume execution of the current program.
