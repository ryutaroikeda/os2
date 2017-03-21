#include <stddef.h>
#include <stdint.h>
#include <kernel/terminal.h>

#if defined(__linux__)
#error "You are not using a cross-compiler"
#endif

#if !defined(__i386__)
#error "You must use an ix86-elf compiler"
#endif

void kernel_main(void);
void kernel_main(void) {
    //uint8_t* video = (uint8_t*) 0xb8000;
    //video[0] = 'X';
    terminal_initialize();
}

