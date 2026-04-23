# File descriptor

- Open file -> system checks existence and permission -> system returns a small non-negative integer to program
- When the command interpreter (the `shell`) runs a program, 3 files are opened, with file descriptors 0, 1, 2, called standard input, standard output, standard error.
- User of a program can redirect I/O with `<` and `>`. The shell changes default assignments for file descriptors 0 and 1 to the specified files. Normally file descriptor 2 (for errors) remains attached to the screen.

# Low level I/O

`read`, `write`

# Open, Creat, Close, Unlink

- `open`: similar to `fopen`
- `creat`
- `perms`:
  - 9 bits of permission information associated with a file that control read, write, execute access for owner, owner's group, other.
  - 3-digit octal number is usually used.
- `close`:
  - similar to `fclose`, except that there is no buffer to flush.
  - termination of program via `exit` or return from `main` closes all open files.
- `unlink`:
  - removes the file name from the file system.
  - correspond to standard library function `remove`.

# Random access

- `lseek`: standard library function `seek` is similar

# Examples

- `fopen`, `getc`
- listing directories
- storage allocator
