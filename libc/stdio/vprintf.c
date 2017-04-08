#include <kernel/terminal.h>
#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static int print_int(int i, size_t size) {
    char buf[32];
    if (32 < size) {
        size = 32;
    }
    size_t written = 0;
    bool negative = i < 0;
    if (0 == i) {
        buf[written++] = '0';
    } else if (negative) {
        i *= -1;
        terminal_putchar('-');
    }
    while (written < size && 0 < i) {
        buf[written++] = (char) ((i % 10) + '0');
        i /= 10;
    }
    if (0 < i) {
        return EOF;
    }
    for (size_t j = written; j > 0; j--) {
        terminal_putchar(buf[j - 1]);
    }
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
        } else {
            // this should not happen
            return EOF;
        }
        i++;
    }
    return written;
}
