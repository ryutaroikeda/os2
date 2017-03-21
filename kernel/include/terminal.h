#ifndef _KERNEL_TERMINAL_H
#define _KERNEL_TERMINAL_H

#include <stddef.h>

void terminal_initialize(void);
void terminal_putchar(char c);
void terminal_write(const char* data, size_t size);

#endif
