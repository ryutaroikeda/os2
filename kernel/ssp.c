#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uintptr_t __stack_chk_guard = 0xdeadbeef;

__attribute__((__noreturn__)) void __stack_chk_fail(void);
__attribute__((__noreturn__)) void __stack_chk_fail(void) {
    printf("stack smash detected\n");
    abort();
}

