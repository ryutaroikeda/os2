#include <kernel/terminal.h>
#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

int printf(const char* format, ...) {
    va_list args;
    va_start(args, format);
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
        } else {
            // this should not happen
            return EOF;
        }
        i++;
    }
    va_end(args);
    return written;
}

