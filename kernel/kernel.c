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

static uintptr_t KERNEL_VIRTUAL_BASE = 0xc0000000;

static void* virtual_address(void* p) {
    return (void*) ((uintptr_t)p + KERNEL_VIRTUAL_BASE);
}

static void initialize_memory_map(multiboot_info_t* mbi) {
    if (! (mbi->flags & 0x20)) {
        panic("no memory map provided by grub");
    }
}

void kernel_main(multiboot_info_t* mbi, uint32_t magic);
void kernel_main(multiboot_info_t* mbi, uint32_t magic) {
    (void) magic;
    arch_initialize();
    printf("kernel virtual base: %x\n", KERNEL_VIRTUAL_BASE);
    printf("p addr of mbi: %x\nv addr of mbi: %x\n", mbi,
            virtual_address(mbi));
    initialize_memory_map((multiboot_info_t*) virtual_address(mbi));
    printf("testing %d %s\n", 234523, "hello world");
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
