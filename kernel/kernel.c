#include <kernel/terminal.h>
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
    terminal_initialize();
    char buf[] = "hello world\n";
    char* s = &buf[1];
    //memcpy(buf, "holaa", 5);
    memmove(s, buf, 2);
    memset(s, 'h', 5);
    printf("%s", buf);
}

