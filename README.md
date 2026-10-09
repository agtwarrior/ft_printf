*This project has been created as part of the 42 curriculum by davguerr.*

# ft_printf

## Description

`ft_printf` is a reimplementation of the libc `printf()` function. The project
builds a static library, `libftprintf.a`, which exposes a single public
function:

```c
int	ft_printf(char const *str, ...);
```

The goal is to learn how to work with **variadic functions** in C
(`va_start`, `va_arg`, `va_end`) and to structure the code so that it is easy
to extend with new conversions.

Like the original `printf()`, the function writes to the standard output and
returns the number of characters printed. Unlike the original, it does not
implement buffer management: every character is written directly with `write`.

### Supported conversions

| Conversion | Prints |
|:----------:|--------|
| `%c` | A single character. |
| `%s` | A string. If it is `NULL`, prints `(null)`. |
| `%p` | A `void *` pointer in hexadecimal with the `0x` prefix. If it is `NULL`, prints `(nil)`. |
| `%d` | A decimal (base 10) number. |
| `%i` | An integer in base 10. |
| `%u` | An unsigned decimal (base 10) number. |
| `%x` | A hexadecimal (base 16) number in lowercase. |
| `%X` | A hexadecimal (base 16) number in uppercase. |
| `%%` | A percent sign. |

The bonus part (`-0.# +` flags and minimum field width) is not implemented.

### Project structure

| File | Contents |
|------|----------|
| `ft_printf.c` | `ft_printf()` and the conversion dispatcher `manage_print()`. |
| `ft_print_chars.c` | `%c` and `%s` conversions. |
| `ft_print_digits.c` | `%d`, `%i` and `%u` conversions. |
| `ft_print_hexa.c` | `%x`, `%X` and `%p` conversions. |
| `ft_printf.h` | Prototypes and required headers. |
| `Makefile` | Build rules for the library. |

## Instructions

### Compilation

You need `cc`, `make` and `ar`. From the root of the repository:

```sh
make
```

This compiles the sources with `-Wall -Wextra -Werror` and creates
`libftprintf.a` at the root of the repository.

| Rule | Action |
|------|--------|
| `make` / `make all` | Builds the `libftprintf.a` library. |
| `make clean` | Removes the object files (`.o`). |
| `make fclean` | Removes the object files and the library. |
| `make re` | Runs `fclean` and rebuilds everything. |

### Usage

Include the header in your code and link against the library:

```c
#include "ft_printf.h"

int	main(void)
{
	int	n;

	n = ft_printf("Hello %s, you are %d years old (%x in hex)\n", "David", 21, 21);
	ft_printf("Characters printed: %i\n", n);
	ft_printf("Pointer: %p | Percent: 100%%\n", &n);
	return (0);
}
```

```sh
cc -Wall -Wextra -Werror main.c -L. -lftprintf -o program
./program
```

Output:

```
Hello David, you are 21 years old (15 in hex)
Characters printed: 46
Pointer: 0x7ffd3c1a5b44 | Percent: 100%
```

## Algorithm and data structure

### Walking the format string

`ft_printf()` walks the format string **only once**, character by character,
from left to right:

- If the character is not `%`, it is written as is with `write` and added to
  the counter.
- If it is `%` and there is a character after it, that next character is
  treated as the specifier and handed to `manage_print()`, which returns how
  many characters it printed.

This linear scan was chosen because the mandatory part has no flags or widths:
every conversion takes exactly two characters (`%` + letter), so there is no
need for a state machine or for keeping anything between one conversion and
the next. The cost is O(n) on the length of the string and no extra memory is
needed.

Edge cases:

- A `%` at the very end of the string (with nothing after it) is printed as a
  regular `%`.
- An unknown specifier (for example `%k`) is printed literally (`%k`) instead
  of being discarded.
- If the format string is `NULL`, the function returns `0` without printing
  anything.

### Choosing the conversion

`manage_print()` is a chain of `if` statements that compares the specifier and
calls the matching function, fetching the argument with `va_arg` and the right
type (`int`, `unsigned int`, `char *` or `void *`). With only nine
conversions, an `if` chain is simpler and more readable than a table of
function pointers, and adding a new conversion only takes one more line plus
its printing function.

The `va_list` is passed to `manage_print()` **by pointer** (`va_list *`). This
way every `va_arg` advances the original list owned by `ft_printf()` and the
next specifier reads the correct argument; passing the `va_list` by value to
another function and using it again afterwards is indeterminate according to
the standard.

### Printing numbers: recursion

To write a number, its most significant digit has to be printed first, but the
`% base` operation yields the least significant one first. Instead of storing
the digits in a buffer and reversing them, the numeric functions are
**recursive**: they call themselves with `n / base` and, on the way back,
write the digit `n % base`. The call stack itself acts as the data structure
and the digits come out in the right order.

Advantages of this choice:

- **No `malloc`**: no heap memory is allocated, so there can be no leaks and
  no allocation failures to handle.
- **No fixed-size buffers**: there is no need to know in advance how many
  digits the number will have.
- **Bounded depth**: at most 10 calls for an `int` in base 10 and 16 for a
  64-bit pointer in base 16, so there is no risk of overflowing the stack.

Each call returns how many characters it wrote and adds them to those of the
recursive call, so the total count is built without global or static
variables.

### Details per type

- **Signed integers (`%d`, `%i`)**: the value is copied into a `long` before
  its sign is flipped. This lets `INT_MIN` (-2147483648) be turned positive
  without overflow, which is not possible inside an `int`.
- **Hexadecimal (`%x`, `%X`)**: the digit is obtained by indexing a base
  string (`"0123456789abcdef"` or `"0123456789ABCDEF"`) with `n % 16`. This
  string works as a lookup table and avoids character arithmetic to tell
  digits from letters.
- **Pointers (`%p`)**: the address is cast to `unsigned long` to cover all 64
  bits, `0x` is printed, and then the value in lowercase hexadecimal through a
  `static` helper function. For `NULL` it prints `(nil)`, like glibc's
  `printf()` on Linux.
- **Strings (`%s`)**: they are walked character by character. For `NULL` it
  prints `(null)`, like glibc.

### Data structure

The project does not need any data structure of its own: the only state is the
`va_list`, the index into the format string and the character counter, all of
them local variables of `ft_printf()`. The libft is not used either, since the
authorized functions (`write` and the `stdarg.h` macros) are enough.

## Resources

### References

- [`man 3 printf`](https://man7.org/linux/man-pages/man3/printf.3.html) —
  behaviour of the original function and of each conversion.
- [`man 3 stdarg`](https://man7.org/linux/man-pages/man3/stdarg.3.html) —
  `va_start`, `va_arg`, `va_copy` and `va_end`.
- [`man 2 write`](https://man7.org/linux/man-pages/man2/write.2.html) —
  system call used for all the output.
- [Variadic functions — cppreference](https://en.cppreference.com/w/c/variadic) —
  reference for variadic functions in C.
- [Variadic Functions — The GNU C Library](https://www.gnu.org/software/libc/manual/html_node/Variadic-Functions.html) —
  detailed explanation of how they work and their limitations.
- [`man 1 ar`](https://man7.org/linux/man-pages/man1/ar.1.html) — creating
  static libraries.
- [GNU Make Manual](https://www.gnu.org/software/make/manual/make.html) —
  rules, pattern rules and automatic variables used in the Makefile.
- The 42 Norm (*Norminette*) — mandatory coding style for the project.

### AI usage

AI (Claude Code, by Anthropic) was used to write this `README.md` from the
already finished source code and the requirements of the subject.
