#include <kernel/terminal.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

int printf(const char* format, ...) {
    va_list args;
    va_start(args, format);
    int bytes_written = 0;
    size_t i = 0;
    while (format[i]) {
        if ('%' != format[i]) {
            putchar(format[i]);
            i++;
            bytes_written++;
            continue;
        } 
        i++;
        if ('%' == format[i]) {
            terminal_putchar('%');
            bytes_written++;
        } else if ('c' == format[i]) {
            terminal_putchar((char)va_arg(args, int));
            bytes_written++;
        } else {
            // this should not happen
            return EOF;
        }
        i++;
    }
    va_end(args);
    return bytes_written;
}

