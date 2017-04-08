#include <kernel.h>
#include <stdarg.h>
#include <stdio.h>

void panic(const char* format, ...) {
    va_list args;
    va_start(args, format);
    printf("kernel:panic:");
    vprintf(format, args);
    printf("\n");
    va_end(args);
    while (1) {
        idle();
    }
}

