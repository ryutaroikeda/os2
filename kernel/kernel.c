#include <assert.h>
#include <kernel.h>
#include <kernel/arch.h>
#include <kernel/multiboot.h>
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

void kernel_main(multiboot_info_t* mbi, uint32_t magic);
void kernel_main(multiboot_info_t* mbi, uint32_t magic) {
    (void) magic;
    arch_initialize(mbi);
    printf("%s\n", "hello world");
    /*
    int x = 0;
    int a = 1 / x;
    printf("%d", a);
    printf("%d", x);
    */
    while (true) {
        idle();
    }
    printf("exit kernel\n");
}
