#include <kernel.h>
#include <kernel/arch.h>
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
    char buf[] = "hello world\n";
    char* s = &buf[1];
    //memcpy(buf, "holaa", 5);

    memmove(s, buf, 2);
    //memset(s, 'h', 500);
    /*
    printf("%s", buf);
    if (0 == memcmp(buf, buf, 2)) {
        printf("eq\n");
    }
    */
    printf("testing %d %s\n", 234523, "hello world");
    panic("woops");
    printf("exit kernel\n");
}

