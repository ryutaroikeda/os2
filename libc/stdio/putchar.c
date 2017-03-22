#include <stdio.h>
#include <kernel/terminal.h>

int putchar(int c) {
    terminal_putchar((char) c);
    return c;
}

