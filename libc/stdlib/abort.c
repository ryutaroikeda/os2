#include <stdio.h>
#include <stdlib.h>

#if defined(__is_libk)
#include <kernel.h>
#endif

__attribute__((__noreturn__))
void abort(void) {
#if defined(__is_libk)
    panic("abort()\n");
#else
    printf("abort()\n");
#endif
    while (1) {}
    __builtin_unreachable();
}

