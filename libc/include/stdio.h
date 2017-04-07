#ifndef _STDIO_H
#define _STDIO_H
#include <stdarg.h>
#define EOF (-1)

int vprintf(const char*, va_list);
int printf(const char*, ...);
int putchar(int);
int puts(const char*);

#endif

