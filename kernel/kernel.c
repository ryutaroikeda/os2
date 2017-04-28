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

void kernel_main(void* mbi, uint32_t magic);
void kernel_main(void* mbi, uint32_t magic) {
    (void) mbi;
    (void) magic;
    arch_initialize();
    printf("testing %d %s\n", 234523, "hello world");

    /*
    int x = 0;
    int a = 1 / x;
    printf("%d", a);
    printf("%d", x);
    */
    printf("exit kernel\n");
}

