#include <kernel/terminal.h>
#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static int print_unsigned_int(unsigned int u, size_t size) {
    char buf[32];
    if (32 < size) {
        size = 32;
    }
    size_t written = 0;
    if (0 == u) {
        buf[written++] = '0';
    }
    while (written < size && 0 < u) {
        buf[written++] = (char) ((u % 10) + '0');
        u /= 10;
    }
    if (0 < u) {
        return EOF;
    }
    for (size_t j = written; j > 0; j--) {
        terminal_putchar(buf[j - 1]);
    }
    return (int) written;
}

static int print_int(int i, size_t size) {
    size_t written = 0;
    bool negative = i < 0;
    unsigned int u;
    if (negative) {
        u = (unsigned int) (-1 * i);
        terminal_putchar('-');
    } else {
        u = (unsigned int) i;
    }
    print_unsigned_int(u, size);
    if (negative) {
        written++;
    }
    return (int) written;
}

int vprintf(const char* format, va_list args) {
    int written = 0;
    size_t i = 0;
    while (format[i]) {
        size_t remaining = (size_t) (INT_MAX - written);
        if (remaining < 1) {
            // @cleanup return overflow error
            return EOF;
        }
        if ('%' != format[i]) {
            terminal_putchar(format[i]);
            i++;
            written++;
            continue;
        }
        i++;
        if ('%' == format[i]) {
            terminal_putchar('%');
            written++;
        } else if ('c' == format[i]) {
            terminal_putchar((char)va_arg(args, int));
            written++;
        } else if ('s' == format[i]) {
            char* s = va_arg(args, char*);
            size_t len = strlen(s);
            if (remaining < len) {
                return EOF;
            }
            terminal_writestring(s);
            written += (int) len;
        } else if ('d' == format[i]) {
            int len = print_int(va_arg(args, int), remaining);
            if (len < 0) {
                return EOF;
            }
            written += len;
        } else if ('u' == format[i]) {
            int len = print_unsigned_int(va_arg(args, unsigned int),
                    remaining);
            if (len < 0) {
                return EOF;
            }
            written += len;
        } else {
            // this should not happen
            return EOF;
        }
        i++;
    }
    return written;
}
