#if defined(__is_libk)
#include <kernel/terminal.h>
#endif

#include <stdio.h>

int putchar(int c) {
#if defined(__is_libk)
    terminal_putchar((char) c);
#else
    // todo
#endif
    return c;
}

