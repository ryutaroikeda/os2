#include <assert.h>
#include <kernel.h>
#include <kernel/arch.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(__linux__)
#error "You are not using a cross-compiler"
#endif

#if !defined(__i386__)
#error "You must use an ix86-elf compiler"
#endif

void kernel_main(void);
void kernel_main(void) {
    arch_initialize();
    assert(false);
    printf("testing %d %s\n", 234523, "hello world");
    int x = 0;
    int a = 1 / x;
    printf("%d", a);
    //idle();
    printf("exit kernel\n");
}

